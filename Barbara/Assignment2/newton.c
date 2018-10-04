#include <pthread.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <complex.h>
#include <time.h>

// define size of plane
#define SIZE 2.0

// maximal value of f to conclude no convergence
#define MAX 10000000000

// threshold distance to conclude convergence
// or being too close to 0
#define EPSILON 0.001

// define value for extra root when it doesn't converge
#define EXTRAROOT 100

// global variables
int n_threads, gridsize, d;
int **rootIds, **iterations;
double complex *roots;
bool *finished;
pthread_mutex_t mutex;

// functions
void* root_runner(void *restrict arg);
void* write_runner(void *restrict arg);
void find_root(int* it, int* rootId, double complex x0);
void mul_cpx(double *a_re, double *a_im, double *b_re, \
             double *b_im, double *c_re, double *c_im);

// main function
int main(int argc, char *argv[]) {

	// read input
	if (argc != 4) {
		printf("Wrong input format.\n");
		return 0;
	}
	else {
		n_threads = (int) strtol(argv[1] + 2, NULL, 10);
		gridsize = (int) strtol(argv[2] + 2, NULL, 10);
		d = (int) strtol(argv[3], NULL, 10);
	}

	// initialize matrices
    int *identries = (int*) malloc(sizeof(int) * gridsize * gridsize);
    rootIds = (int**) malloc(sizeof(int*) * gridsize);
    int *itentries = (int*) malloc(sizeof(int) * gridsize * gridsize);
    iterations = (int**) malloc(sizeof(int*) * gridsize);
    finished = (bool*) malloc(sizeof(bool) * gridsize);
    for (size_t ix = 0, jx = 0; ix < gridsize; ++ix, jx += gridsize) {
        rootIds[ix] = identries + jx;
        iterations[ix] = itentries + jx;
        finished[ix] = false;
    }
    
    // precalculate the roots
    roots = (double complex*) malloc(sizeof(double complex) \
                                                     * (d+1));
    for (size_t ix = 0; ix < d; ++ ix) {
        roots[ix] = cos(2.0 * M_PI * (double) ix / (double) d) + \
                    I * sin(2.0 * M_PI * (double) ix / (double) d);
    }
    roots[d] = EXTRAROOT;

    // initialize threads
    pthread_t computing[n_threads];
    pthread_t writing;
    pthread_mutex_init(&mutex, NULL);
    int ret;

    // get the writing thread to work
    if (ret = pthread_create(&writing, NULL, write_runner, NULL)) {
        printf("Error creating thread: %\n", ret);
        exit(1);
    }

    // distribute the computing
    for (size_t tx = 0; tx < n_threads; ++ tx) {

        // pass start row index as an argument and let thread run
        int *arg = malloc(sizeof(int));
        *arg = tx;
        if (ret = pthread_create(computing + tx, NULL, root_runner, (void*) arg)) {
            printf("Error creating thread: %\n", ret);
            exit(1);
        }

    }
    
    // join everything again and quit
    for (size_t tx = 0; tx < n_threads; ++ tx) {
        if (ret = pthread_join(computing[tx], NULL)) {
            printf("Error joining thread: %d\n", ret);
            exit(1);
        }
    }
    if (ret = pthread_join(writing, NULL)) {
        printf("Error joining thread: %d\n", ret);
        exit(1);
    }
    pthread_mutex_destroy(&mutex);


    free(identries);
    free(rootIds);
    free(itentries);
    free(iterations);
    free(finished);
    free(roots);
    
	return 0;
}



// function for a thread to get roots for values defined in arg
void* root_runner(void *restrict arg) {
    
    // initialization
    int startrow = * ((int*) arg);
    free(arg);
    double complex x0;
    int *loc_it = (int*) malloc(sizeof(int) * gridsize);
    int *loc_rootId = (int*) malloc(sizeof(int) * gridsize);
    
    // pick rows and calculate the roots for whole row
    for (size_t ix = startrow; ix < gridsize; ix += n_threads) {
        for (size_t jx = 0; jx < gridsize; ++ jx) {
            x0 = (-SIZE + (double) (jx * 2*SIZE) / (double) (gridsize-1)) + \
                I * (SIZE - (double) (ix * 2*SIZE) / (double) (gridsize-1));
            find_root(loc_it + jx, loc_rootId + jx, x0);
        }
        
        // copy calculated file in output
        memcpy(iterations[ix], loc_it, gridsize * sizeof(int));
        memcpy(rootIds[ix], loc_rootId, gridsize * sizeof(int));
        
        // mark row as done so that it can be written in the file
        pthread_mutex_lock(&mutex);
        finished[ix] = true;
        pthread_mutex_unlock(&mutex);
    }

    free(loc_it);
    free(loc_rootId);
    
    pthread_exit(NULL);
    
}



// function for the writing thread
void* write_runner(void *restrict arg) {
    
    // initialize
    char colors[8][12] = {"0 0 255", "255 0 0", "0 255 0", "255 255 0", \
        "255 0 255", "0 255 255", "255 255 255"};
    int ix = 0;
    bool *done = malloc(sizeof(bool));
    int *loc_it = (int*) malloc(sizeof(int) * gridsize);
    int *loc_rootId = (int*) malloc(sizeof(int) * gridsize);
    
    // open files
    FILE *convergence, *attractors;
    convergence = fopen("newton_convergence_xd.ppm", "w");
    attractors = fopen("newton_attractors_xd.ppm", "w");
    
    // write beginning for ppm file
    fprintf(convergence, "P3\n%i %i\n%i\n", gridsize, gridsize, 150);
    fprintf(attractors, "P3\n%i %i\n%i\n", gridsize, gridsize, 255);
    
    // write matrices
    while (ix < gridsize) {

        // check if computation thread has finished row ix
        pthread_mutex_lock(&mutex);
        finished[ix] = *done;
        pthread_mutex_unlock(&mutex);

        // if yes write row in files
        if (*done == true) {
            
            // copy row to write in local array
            memcpy(loc_it, iterations[ix], gridsize * sizeof(int));
            memcpy(loc_rootId, rootIds[ix], gridsize * sizeof(int));
            
            for (size_t jx = 0; jx < gridsize; ++jx) {
                fprintf(attractors, "%s ", colors[loc_rootId[jx]]);
                fprintf(convergence, "%i %i %i ", loc_it[jx], \
                        loc_it[jx], loc_it[jx]);
            }
            fprintf(attractors, "\n");
            fprintf(convergence, "\n");
            ++ ix;
        }
        // if not wait a bit and try again
        else {
            nanosleep((const struct timespec[]){{0, 1000000L}}, NULL);
            continue;
        }
    }
    
    // close files
    fclose(convergence);
    fclose(attractors);
    
    // free variables
    free(done);
    free(loc_it);
    free(loc_rootId);
    
    pthread_exit(NULL);
}



// find the root starting from x0 and save which root in rootId
// and the number of iterations in it
void find_root(int* it, int* rootId, double complex x0) {
    
    // initialization
    bool abort = false, done = false;
    int i = -1;
    double x_re, x_im, xNext_re, xNext_im, pow_re, pow_im, r2_pow;
    double powRes_re, powRes_im, diff_re, diff_im;
    xNext_re = creal(x0);
    xNext_im = cimag(x0);
    
    // run iterations
    while (done == false && abort == false) {
        
        // update
        x_re = xNext_re;
        x_im = xNext_im;

        pow_re = x_re;
        pow_im = x_im;
        
        
        // calculate new value
        // rewrite x - f/f' to x/d * (d-1+1/x^d)
        // and then x -> x_re + i*x_im and (x^d) = (x^d)_re + i*(x^d)_im
        // use: 1/(a+ib) = a/(a^2+b^2) - b/(a^2+b^2) and simplify
        for (size_t p = 2; p <= d; ++ p) {
            mul_cpx(&powRes_re, &powRes_im, &pow_re, &pow_im, &x_re, &x_im);
            pow_re = powRes_re;
            pow_im = powRes_im;
        }
        
        r2_pow = pow_re * pow_re + pow_im * pow_im;
        xNext_re = 1.0 / (d * r2_pow) * (x_re * d * r2_pow - \
                                         x_re * r2_pow + \
                                         x_re * pow_re + x_im * pow_im);
        xNext_im = 1.0 / (d * r2_pow) * (x_im * d * r2_pow - x_im * r2_pow + \
                                         x_im * pow_re - x_re * pow_im);
        
        // check abortion
        // (1) f = x^d - 1 is close to a root
        if ((pow_re-1) * (pow_re-1) + pow_im * pow_im < EPSILON*EPSILON) {
            done = true;
        }
        // (2) x has too big real or imaginary part
        else if (x_re > MAX || x_im > MAX) {
            abort = true;
        }
        // (3) x is too close to zero
        else if (x_re * x_re + x_im * x_im < EPSILON*EPSILON) {
            abort = true;
        }
        // otherwise continue
        else {
            abort = false;
            done = false;
        }
        
        // add to counter
        ++ i;
    }
    
    // get iteration counter
    *it =  i;
    
    // get root id
    if (done == true) {
        for (size_t ix = 0; ix < d + 1; ++ ix) {
            diff_re = creal(roots[ix]) - x_re;
            diff_im = cimag(roots[ix]) - x_im;
            if (diff_re * diff_re + diff_im * diff_im < EPSILON*EPSILON) {
                *rootId = ix;
                break;
            }
        }
    }
    else if (abort == true) {
        *rootId = d;
    }

    return;
}



// multiplication of two complex numbers b and c
// output is saved in a
void mul_cpx(double *a_re, double *a_im, double *b_re, double *b_im, \
                      double *c_re, double *c_im) {
    *a_re = *b_re * *c_re - *b_im * *c_im;
    *a_im = *b_re * *c_im + *b_im * *c_re;
    
    return;
}
