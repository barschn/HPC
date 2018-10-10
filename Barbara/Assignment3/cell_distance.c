#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#include <omp.h>

// define points
#define DIMENSION 3
#define BLOCKSIZE 1000

// define precision
#define PRECISION 0.01

// frequency matrix
int **frequencies;

// thread number;
int n_threads;

// functions
void read_block(FILE *fp, int **block, long int *size, long int startrowBlock1);
void get_distance_within(int **block, long int *size);
void get_distance_across(int **block1, long int *size1, int **block2, long int *size2);


// main function
int main(int argc, char *argv[]) {
    
    // read input
    if (argc != 2) {
        printf("Wrong input format.\n");
        return 0;
    }
    else {
        n_threads = (int) strtol(argv[1] + 2, NULL, 10);
        omp_set_num_threads(n_threads);
    }
    
    // intialize point matrix
    // note that we consider only integers
    // 01.56 -> 156 and so on ... for PRECISION 0.01
    int *block1entries = (int*) malloc(sizeof(int) * BLOCKSIZE * DIMENSION);
    int **block1 = (int**) malloc(sizeof(int*) * BLOCKSIZE);
    int *block2entries = (int*) malloc(sizeof(int) * BLOCKSIZE * DIMENSION);
    int **block2 = (int**) malloc(sizeof(int*) * BLOCKSIZE);
    for (size_t ix = 0, jx = 0; ix < BLOCKSIZE; ++ix, jx += DIMENSION) {
        block1[ix] = block1entries + jx;
        block2[ix] = block2entries + jx;
    }
    
    // initalize output matrix
    // values are 3d between -10 and 10 (-1000 and 1000)
    // therefore the maximal distance between two points is 20 * sqrt(3) = 34.64
    // (2000 * sqrt(3) = 3464)
    // + 1 such that bouth extreme values are counted
    int max_bins = 3464 + 1;
    int *frequencyentries = (int*) malloc(sizeof(int) * max_bins * 2);
    frequencies = (int**) malloc(sizeof(int*) * max_bins);
    for (size_t ix = 0, jx = 0; ix < max_bins; ++ix, jx += 2) {
        frequencies[ix] = frequencyentries + jx;
        frequencies[ix][0] = ix;
        frequencies[ix][1] = 0;
    }
    
    
    // open to read file
    char *filename = "cell_e5";
    FILE *fp;
    fp = fopen(filename, "r");
    
    long int *blocksize1 = malloc(sizeof(long int));
    long int *blocksize2 = malloc(sizeof(long int));
    long int startlineBlock1 = 1, startlineBlock2 = 1;
    
    // go through
    while (true) {
        
        // read the first row block of interest
        read_block(fp, block1, blocksize1, startlineBlock1);
        
        // break if there is no data left
        if (*blocksize1 == 0) {
            break;
        }
        
        // calculate the distances within the first row block
        get_distance_within(block1, blocksize1);
        
        // calculate the distances to all other column blocks successively
        while (true) {
            
            // go to next block
            startlineBlock2 += *blocksize1;
            
            // read column block
            read_block(fp, block2, blocksize2, startlineBlock2);
            
            // go to next block row if no data left in that column
            if (*blocksize2 == 0) {
                break;
            }
            
            // calculate the distances between the current row and column block
            get_distance_across(block1, blocksize1, block2, blocksize2);
        
        }
        
        
        // update start values
        // note that we only calculate the upper triangle of the distance matix
        startlineBlock1 += *blocksize1;
        startlineBlock2 = startlineBlock1;
        
    }
    
    // print out the nonzero frequencies
    for (size_t ix = 0; ix < max_bins; ++ ix) {
        if (frequencies[ix][1] > 0) {
            printf("%.2f\t%i\n", (double) frequencies[ix][0] * PRECISION, \
                   frequencies[ix][1]);
        }
    }
    
    // free variables and quit
    fclose(fp);
    free(blocksize1);
    free(block1);
    free(block1entries);
    free(blocksize2);
    free(block2);
    free(block2entries);
    free(frequencyentries);
    free(frequencies);
    
    return 0;
    
}



// read block from datafile
// one line has 24 characters
void read_block(FILE *fp, int **block, long int *size, long int startrow) {
    
    int ix = 0;
    char line[24];
    char* end;
    
    // go to start row and read in values from block
    fseek(fp, 24 * (startrow - 1), SEEK_SET);
    while (ix < BLOCKSIZE && fread(&line, sizeof(char), 24, fp)) {
        block[ix][0] = round(strtod(line, &end) / PRECISION);
        block[ix][1] = round(strtod(end, &end) / PRECISION);
        block[ix][2] = round(strtod(end, NULL) / PRECISION);
        ++ ix;
    }
    *size = ix;
    
    return;
    
}


// calculate all differences between points in the block
// using get_eucledian_distance
void get_distance_within(int **block, long int *size){
    
    #pragma omp parallel for collapse(2)
    for (size_t ix = 0; ix < *size; ++ix) {
        for (size_t jx = 0; jx < *size; ++jx) {
            
            if (ix < jx) {
                int d = round(sqrt((block[ix][0] - block[jx][0]) * (block[ix][0] - block[jx][0]) + \
                               (block[ix][1] - block[jx][1]) * (block[ix][1] - block[jx][1]) + \
                               (block[ix][2] - block[jx][2]) * (block[ix][2] - block[jx][2])));
            
                #pragma omp atomic
                ++ frequencies[d][1];
            }
            
        }
    }
    
    return;
}


// calculate all differences between points in one block
// to points in the other block
void get_distance_across(int **block1, long int *size1, int **block2, long int *size2) {
    
    #pragma omp parallel for collapse(2)
    for (size_t ix = 0; ix < *size1; ++ix) {
        for (size_t jx = 0; jx < *size2; ++jx) {
            
            int d = round(sqrt((block1[ix][0] - block2[jx][0]) * (block1[ix][0] - block2[jx][0]) + \
                           (block1[ix][1] - block2[jx][1]) * (block1[ix][1] - block2[jx][1]) + \
                           (block1[ix][2] - block2[jx][2]) * (block1[ix][2] - block2[jx][2])));
        
            #pragma omp atomic
            ++ frequencies[d][1];
            
        }
    }
    
    return;
}
