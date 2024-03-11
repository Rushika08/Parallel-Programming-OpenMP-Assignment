#include <omp.h> 
#include <stdio.h> 
#define ARR_SIZE 1000000000 
static int a[ARR_SIZE]; 

int main(int *argc, char *argv[]) 
{ 
    int i, sum = 0; 
    int tid, numt = 0; 
    double t1, t2; 

    /* Initialize the array */ 
    for(i = 0; i < ARR_SIZE; i++) 
        a[i] = 1; 

    t1 = omp_get_wtime(); 

    #pragma omp parallel default(shared) private(i, tid) 
    { 
        tid = omp_get_thread_num(); 
        numt = omp_get_num_threads(); 

        // Manually distribute the workload among threads
        int chunk_size = ARR_SIZE / numt;
        int start_index = tid * chunk_size;
        int end_index = (tid == numt - 1) ? ARR_SIZE : start_index + chunk_size;

        // Calculate the sum for the assigned chunk
        int local_sum = 0;
        for(i = start_index; i < end_index; i++) 
            local_sum += a[i];

        // Combine local sums from all threads
        #pragma omp critical
        sum += local_sum;
    } 

    t2 = omp_get_wtime(); 

    printf("Number of threads: %d\n", numt); 
    printf("Time taken: %g for sum: %d \n", t2 - t1, sum); 

    return 0; 
} 
