#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#include <omp.h>

// define size of plane
#define SIZE 10.0

// define points
#define DIMENSION 3
int n_points;
double *pointentries;
double **points;

// define precision
#define PRECISION 0.01

// define maximal number of data points
#define MAX 1000000

// functions
void read_data(char *filename);
void free_variables();

// main function
int main(int argc, char *argv[]) {

    
    // read input
    int n_threads;
    if (argc != 2) {
        printf("Wrong input format.\n");
        return 0;
    }
    else {
        n_threads = (int) strtol(argv[1] + 2, NULL, 10);
    }
    
    
    // read input and save it in global variable points
    char *filename = "data.txt";
    read_data(filename);
    
    
    // calculate distances and sort them
    
    
    
    // free variables and quit
    free_variables();
    return 0;
    
}



// read datafile
void read_data(char *filename) {
    
    //initialize matrices
    double *tmp_pointentries = (double*) malloc(sizeof(double) * MAX * DIMENSION);
    double **tmp_points = (double**) malloc(sizeof(double*) * MAX);
    for (size_t ix = 0, jx = 0; ix < MAX; ++ix, jx += DIMENSION) {
        tmp_points[ix] = tmp_pointentries + jx;
    }
    
    // read data points from file
    FILE *fp;
    fp = fopen(filename, "r");
    
    double x, y, z;
    n_points = 0;
    while (fscanf(fp, "%lf %lf %lf", &x, &y, &z) == DIMENSION) {
        tmp_points[n_points][0] = x;
        tmp_points[n_points][1] = y;
        tmp_points[n_points][2] = z;
        n_points += 1;
    }
    fclose(fp);
    
    // copy read data to smaller matrix and free memory
    pointentries = (double*) malloc(sizeof(double) * n_points * DIMENSION);
    points = (double**) malloc(sizeof(double*) * n_points);
    for (size_t ix = 0, jx = 0; ix < n_points; ++ix, jx += DIMENSION) {
        points[ix] = pointentries + jx;
    }
    for (size_t ix = 0; ix < n_points; ++ ix) {
        for (size_t jx = 0; jx < DIMENSION; ++ jx) {
            points[ix][jx] = tmp_points[ix][jx];
        }
    }
    
    // free tmp matrices
    free(tmp_pointentries);
    free(tmp_points);
    
    return;
    
}



// free created variables
void free_variables() {
    
    free(pointentries);
    free(points);
    
    return;
}

