//Authors: Gleidson De Sousa - desousag@bc.edu, Andrew Bevington - bevingta@bc.edu
#include <stdio.h>
#include <stdlib.h>
//used for DBL_MAX and DBL_MIN
#include <float.h>
#include <time.h>

// Number of random samples to take
#define SAMPLES 10000
// Number of times to run the experiment
#define RUNS 50000
// Number of bins in the histogram
#define BINS 64
//the size of the smallest interval chosen for the histogram
#define HISTOGRAM_SPAN 0.05
// factor to divide the count by when printing the histogram
#define SCALE 32

void create_histogram(const double values[], int counts[]) {
    double bin_size = HISTOGRAM_SPAN / (double)BINS;
    double lower_bound = -HISTOGRAM_SPAN / 2.0;
    
    for (int i = 0; i < RUNS; i++) {
        if (values[i] >= lower_bound && values[i] < -lower_bound) {
            int index = (int)((values[i] - lower_bound) / bin_size);
            
            // Ensure the index is within bounds
            if (index < 0) index = 0;
            if (index >= BINS) index = BINS - 1;
            
            counts[index]++;
        }
    }
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
  }

  return sum / RUNS;
}

double get_mean_of_uniform_random_samples() {
    double sum = 0.0;
    for (int i = 0; i < SAMPLES; i++) {
        double random = (double)rand() / RAND_MAX;
        // Normalize the random number to be between -1 and 1
        double normalized = random * 2.0 - 1.0;
        sum += normalized;
        // printf("Random number: %f\n", normalized);
    }
    return sum / SAMPLES;
}

double populate_values_and_get_mean(double values[]) {
    double sum = 0.0;
    
    for (int i = 0; i < RUNS; i++) {
        values[i] = get_mean_of_uniform_random_samples();
        sum += values[i];
    }
    
    return sum / RUNS;
}

int main() {
    srand(time(NULL));
    
    // Allocate memory for the values array using calloc
    double *values = (double *)calloc(RUNS, sizeof(double));
    int counts[BINS] = {0};  // Initialize all counts to 0
    
    if (values == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    // Call populate_values_and_get_mean
    double mean = populate_values_and_get_mean(values);
    
    // Call get_mean_squared_error
    double mse = get_mean_squared_error(values, mean);
    
    // Call create_histogram
    create_histogram(values, counts);
    
    // Print results    
    print_histogram(counts);
    printf("Sample mean: %f\n Sample variance: %f\n", mean, mse);
    // Free the allocated memory
    free(values);
    
    return 0;
}
