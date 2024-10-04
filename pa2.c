//Authors: Gleidson De Sousa - desousag@bc.edu, Andrew Bevington - bevingta@bc.edu
#include <stdio.h>
#include <stdlib.h>
//used for DBL_MAX and DBL_MIN
#include <float.h>
#include <time.h>

// Number of random samples to take
#define SAMPLES 10
// Number of times to run the experiment
#define RUNS 10
// Number of bins in the histogram
#define BINS 64
//the size of the smallest interval chosen for the histogram
#define HISTOGRAM_SPAN 0.05
// factor to divide the count by when printing the histogram
#define SCALE 32

void create_histogram(double values[], int counts[]) {
  //print all values in the counts array
  for (int i = 0; i < BINS; i++) {
    printf("Count: %d\n", i);
  }

  printf("Creating histogram...\n");
  //iterate over the values array
  for (int i = 0; i < RUNS; i++) {
    //get the index of the bin
    int bin = (int)(values[i] / HISTOGRAM_SPAN);
    //increment the count of the bin
    counts[bin]++;
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

double populate_values_and_get_mean(double values[], int n) {
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
  
  if (values == NULL) {
      fprintf(stderr, "Memory allocation failed\n");
      return 1;
  }
  
  for(int runs = 0; runs < RUNS; runs++) {
    // Call populate_values_and_get_mean
    double mean = populate_values_and_get_mean(values, RUNS);
    // Call get_mean_squared_error
    double mse = get_mean_squared_error(values, mean);

    printf("Mean: %f\n", mse);
    //create the counts array
    int counts[BINS] = {0};
    // Call create_histogram
    create_histogram(values, counts);
  }
 // Free the allocated memory
  free(values);

  return 0;
}
