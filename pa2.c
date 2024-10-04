//Authors: Gleidson De Sousa - desousag@bc.edu, Andrew Bevington - bevingta@bc.edu
#include <stdio.h>
#include <stdlib.h>
//used for DBL_MAX and DBL_MIN
#include <float.h>
#include <time.h>

// Number of random samples to take
#define SAMPLES 10
// Number of times to run the experiment
#define RUNS 50

void create_histogram(double values[], int counts[]) {
    printf("Creating histogram...\n");
}

double get_mean_squared_error(double values[], double mean) {
    double error;
    double sum = 0.0;

    for (int i = 0; i < RUNS; i++) {
        error = values[i] - mean;
        error = error * error;
        sum += error;
        error = 0.0;
    }

    return sum / RUNS;
}

double get_mean_of_uniform_random_samples() {
    double sum = 0;
    for (int i = 0; i < SAMPLES; i++) {
        double random = (double) rand() / RAND_MAX;
        // Normalize the random number to be between -1 and 1
        double normalized = random * 2.0 - 1.0;
        sum += normalized;
        // printf("Random number: %f\n", normalized);
    }
    return sum / SAMPLES;
}

double populate_values_and_get_mean(double values[], int n) {
    double sum = 0.0;

    for (int i = 0; i < RUNS; i++) {
        values[i] = get_mean_of_uniform_random_samples();
        // TESTING: do the means tend toward 0?
        printf("mean %d is: %f\n", i+1, values[i]);
        sum += values[i];
        //PROOF that we're executing unintended runs
        //printf("A run has been completed.");
    }
    
    return sum / RUNS;
}

int main() {
    srand(time(NULL));
    // Allocate memory for the values array using calloc
    double *values = (double *)calloc(RUNS, sizeof(double));
  
    if (values == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
  
    double minimum = DBL_MAX;
    double maximum = -DBL_MIN;
    
    //TO REVIEW: I believe this for loop may be unnecessary. 
    // The instructions are not very clear but it seems 
    // that we may be executing RUNS^RUNS number of runs 
    // rather than just RUNS number of runs.
    
    
    // Call populate_values_and_get_mean
    double mean = populate_values_and_get_mean(values, RUNS);
        
    // Call get_mean_squared_error
    double mse = get_mean_squared_error(values, mean);    

    printf("mean squared error is: %f\n", mse);

    // Free the allocated memory
    free(values);

    return 0;
}
