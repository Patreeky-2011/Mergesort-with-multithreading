/**
 * This file implements parallel mergesort.
 */

#include <stdio.h>
#include <string.h> /* for memcpy */
#include <stdlib.h> /* for malloc */
#include "mergesort.h"

/* this function will be called by mergesort() and also by parallel_mergesort(). */
void merge(int leftstart, int leftend, int rightstart, int rightend){
    int i = leftstart;      
    int j = rightstart;    
    int k = leftstart;      
    
    // Step 1: Merge both subarrays into B while comparing
    while (i <= leftend && j <= rightend) {
        if (A[i] <= A[j]) {
            B[k] = A[i];
            i++;
        } else {
            B[k] = A[j];
            j++;
        }
        k++;
    }
    
    // Step 2: Copy remaining elements from left subarray (if any)
    while (i <= leftend) {
        B[k] = A[i];
        i++;
        k++;
    }
    
    // Step 3: Copy remaining elements from right subarray (if any)
    while (j <= rightend) {
        B[k] = A[j];
        j++;
        k++;
    }
    
    // Step 4: Copy merged result from B back to A
    for (int m = leftstart; m <= rightend; m++) {
        A[m] = B[m];
    }
}

/* this function will be called by parallel_mergesort() as its base case. */
void my_mergesort(int left, int right){
	//Base case
	if (left > right) {
		return;
	}

	int mid = (left+right)/2;
	
	//Recursive calling logic for mergesort
	my_mergesort(left, mid);
	my_mergesort(mid+1, right);
	merge(left, mid, mid+1, right);
}

/* this function will be called by the testing program. */
void * parallel_mergesort(void *arg){
		return NULL;
}

/* we build the argument for the parallel_mergesort function. */
struct argument * buildArgs(int left, int right, int level){
		return NULL;
}

