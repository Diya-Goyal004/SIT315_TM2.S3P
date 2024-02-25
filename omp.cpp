#include <chrono>        // Header for time measurement
#include <cstdlib>       // Standard library for memory allocation
#include <iostream>      // Standard I/O library
#include <time.h>        // Time manipulation functions
#include <omp.h>         // OpenMP header for parallelization

using namespace std::chrono; // Namespace for chrono library
using namespace std;          // Standard namespace

// Function to generate random values into a vector
void randomVector(int vector[], int size) {
    // Generate random values for each element of the vector
    for (int i = 0; i < size; i++) {
        vector[i] = rand() % 100; // Generate random numbers between 0 and 99
    }
}

int main() {
    unsigned long size = 100000000; // Size of the vectors
    srand(time(0));                 // Seed the random number generator with current time
    int *v1, *v2, *v3;              // Pointers for vectors

    auto start = high_resolution_clock::now(); // Start measuring time

    // Allocate memory for the vectors
    v1 = (int *)malloc(size * sizeof(int));
    v2 = (int *)malloc(size * sizeof(int));
    v3 = (int *)malloc(size * sizeof(int));

    // Generate random values for v1 and v2
    randomVector(v1, size);
    randomVector(v2, size);

    // Adding parallelism using OpenMP
    #pragma omp parallel default(none) shared(v1, v2, v3, size)
    {
        // Generate random values for v1 and v2 in parallel
        randomVector(v1, size);
        randomVector(v2, size);

        // Parallelize the loop for vector addition
        #pragma omp for
        for (int i = 0; i < size; i++) {
            v3[i] = v1[i] + v2[i]; // Add corresponding elements of v1 and v2 and store in v3
        }
    }

    auto stop = high_resolution_clock::now(); // Stop measuring time
    auto duration = duration_cast<microseconds>(stop - start); // Calculate duration

    // Output the time taken by the function
    cout << "Time taken by function: " << duration.count() << " microseconds" << endl;

    // Free dynamically allocated memory
    free(v1);
    free(v2);
    free(v3);

    return 0;
}

