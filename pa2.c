//Authors: Gleidson De Sousa - desousag@bc.edu, Andrew Bevington - bevingta@bc.edu

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//SYMBOLIC CONSTANTS
#define SAMPLES 10000
#define RUNS 50000
#define BINS 64
#define HISTOGRAM_SPAN 0.05
#define SCALE 32

// NOTE: Remember to change all i++ to ++i

void create_histogram(double values[], int counts[]) {
    
    memset(counts, 0, sizeof(int) * BINS);
    double bin_size = HISTOGRAM_SPAN / (double) BINS;

    for (int j = 0; j < RUNS; ++j) {
        int index = (int) ((values[j] + HISTOGRAM_SPAN / 2) / bin_size);
        
        if (index >= 0 && index < BINS) {
            ++counts[index];
        }
    }
    // TESTING counts array
    //for (int i = 0; i < BINS; ++i) {
    //    printf("counts[%d]: %d\n", i, counts[i]);
    //}
}

void print_histogram(const int counts[]) {
    double bin_size = HISTOGRAM_SPAN / (double)BINS;
    double bin_start = -HISTOGRAM_SPAN / 2.0;  // Left end of the histogram span
    
    for (int i = 0; i < BINS; i++) {
        // Calculate the label (center of the bin)
        double label = bin_start + (bin_size / 2.0);
        
        // Print the label
        printf("%7.4f ", label);
        
        // Print the scaled number of Xs
        int scaled_count = counts[i] / SCALE;
        for (int j = 0; j < scaled_count; j++) {
            printf("X");
        }
        printf("\n");
        
        // Move to the next bin
        bin_start += bin_size;
    }
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
        //printf("mean %d is: %f\n", i+1, values[i]);
        
        sum += values[i];
    }
    
    return sum / RUNS;
}

int main() {
    srand(time(NULL));
    
    // Allocate memory for the values array using calloc
    
    double *values = (double *)calloc(RUNS, sizeof(double));
    int counts[BINS];

    if (values == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    
    // Call populate_values_and_get_mean
    double mean = populate_values_and_get_mean(values, RUNS);
        
    // Call get_mean_squared_error
    double mse = get_mean_squared_error(values, mean);    

    // TEST
    // printf("mean squared error is: %f\n", mse);

    create_histogram(values, counts); 
    print_histogram(counts);
    printf("Sample mean: %f\t Sample variance: %f\n", mean, mse);
    
    // Free the allocated memory
    free(values);

    return 0;
}
