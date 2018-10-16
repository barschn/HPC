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
#define BLOCKSIZE 2000

// values are 3d and between -10 and 10 (-1000 and 1000)
// therefore the maximal distance between two points is 20 * sqrt(3) = 34.64
// (2000 * sqrt(3) = 3464)
// + 1 such that bouth extreme values are counted;
#define MAXBINS 3465

// define precision
#define PRECISION 0.01

// frequency vector
int *frequencies;

// thread number;
int n_threads;

// functions
void read_block(FILE *fp, float **block, long int *size);
void get_distance_within(float **block, long int *size);
void get_distance_across(float **block1, long int *size1, float **block2, long int *size2);


// main function
int main(int argc, char *argv[]) {
    
    // read input
    if (argc != 2) {
        return 0;
    }
    else {
        n_threads = (int) strtol(argv[1] + 2, NULL, 10);
        omp_set_num_threads(n_threads);
    }
    
    // intialize point matrix
    // note that we consider only integers
    // 01.56 -> 156 and so on ... for PRECISION 0.01
    float *block1entries = (float*) malloc(sizeof(float) * BLOCKSIZE * DIMENSION);
    float **block1 = (float**) malloc(sizeof(float*) * BLOCKSIZE);
    float *block2entries = (float*) malloc(sizeof(float) * BLOCKSIZE * DIMENSION);
    float **block2 = (float**) malloc(sizeof(float*) * BLOCKSIZE);
    for (size_t ix = 0, jx = 0; ix < BLOCKSIZE; ++ix, jx += DIMENSION) {
        block1[ix] = block1entries + jx;
        block2[ix] = block2entries + jx;
    }
    
    // initalize output matrix
    frequencies = (int*) malloc(sizeof(int) * MAXBINS);
    for (size_t ix = 0; ix < MAXBINS; ++ix) {
        frequencies[ix] = 0;
    }
    
    
    // open to read file
    char *filename = "cell_e5";
    FILE *fp;
    fp = fopen(filename, "r");
    
    long int *blocksize1 = malloc(sizeof(long int));
    long int *blocksize2 = malloc(sizeof(long int));
    long int startlineBlock1 = 1;
    
    // go through
    while (true) {
        
        // read the first row block of interest
        fseek(fp, 24 * (startlineBlock1 - 1), SEEK_SET);
        read_block(fp, block1, blocksize1);
        
        // break if there is no data left
        if (*blocksize1 == 0) {
            break;
        }
        
        // calculate the distances within the first row block
        get_distance_within(block1, blocksize1);
        
        // calculate the distances to all other column blocks successively
        while (true) {
            
            // read column block
            read_block(fp, block2, blocksize2);
            
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
        
    }
    
    // print out the nonzero frequencies
    for (size_t ix = 0; ix < MAXBINS; ++ ix) {
        if (frequencies[ix] > 0) {
            printf("%.2f %i\n", (double) ix * PRECISION, \
                   frequencies[ix]);
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
    free(frequencies);

    return 0;
    
}



// read block from datafile
// one line has 24 characters
void read_block(FILE *fp, float **block, long int *size) {
    
    int ix = 0;
    char line[24];
    char* end;
    
    // go to start row and read in values from block
    while (ix < BLOCKSIZE && fread(&line, sizeof(char), 24, fp)) {
        block[ix][0] = strtof(line, &end);
        block[ix][1] = strtof(end, &end);
        block[ix][2] = strtof(end, NULL);
        ++ ix;
    }
    *size = ix;
    
    return;
    
}


// calculate all differences between points in the block
// using get_eucledian_distance
void get_distance_within(float **block, long int *size){
    
    float r, d;
    int f;
    
    #pragma omp parallel for collapse(2) reduction(+:frequencies[:MAXBINS]) private(r,d,f)
    for (size_t ix = 0; ix < *size; ++ix) {
        for (size_t jx = 0; jx < *size; ++jx) {
            
            if (ix < jx) {
                
                r = (block[ix][0] - block[jx][0]) * (block[ix][0] - block[jx][0]) + \
                    (block[ix][1] - block[jx][1]) * (block[ix][1] - block[jx][1]) + \
                    (block[ix][2] - block[jx][2]) * (block[ix][2] - block[jx][2]);
                
                d = sqrt(r);
                
                f = (int) (d / PRECISION);
                if (d - f < 0.5) {
                    frequencies[f] += 1;
                }
                else {
                    frequencies[f + 1] += 1;
                }
            }
            
        }
    }
    
    return;
}


// calculate all differences between points in one block
// to points in the other block
void get_distance_across(float **block1, long int *size1, float **block2, long int *size2) {

    float r, d;
    int f;
    
    #pragma omp parallel for collapse(2) reduction(+:frequencies[:MAXBINS]) private(r,d,f)
    for (size_t ix = 0; ix < *size1; ++ix) {
        for (size_t jx = 0; jx < *size2; ++jx) {
            
            r = (block1[ix][0] - block2[jx][0]) * (block1[ix][0] - block2[jx][0]) + \
                (block1[ix][1] - block2[jx][1]) * (block1[ix][1] - block2[jx][1]) + \
                (block1[ix][2] - block2[jx][2]) * (block1[ix][2] - block2[jx][2]);
            
            d = sqrt(r);
        
            f = (int) (d / PRECISION);
            if (d - f < 0.5) {
                frequencies[f] += 1;
            }
            else {
                frequencies[f + 1] += 1;
            }
        }
    }
    
    return;
}
