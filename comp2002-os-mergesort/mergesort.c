/**
 * This file implements parallel mergesort.
 */

#include "mergesort.h"

#include <stdio.h>
#include <stdlib.h> /* for malloc */
#include <string.h> /* for memcpy */

/* this function will be called by mergesort() and also by parallel_mergesort().
 */
void merge(int leftstart, int leftend, int rightstart, int rightend) {
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
  memcpy(A + leftstart, B + leftstart,
         (rightend - leftstart + 1) * sizeof(int));
}

/* this function will be called by parallel_mergesort() as its base case. */
void my_mergesort(int left, int right) {
  // Base case
  if (left >= right) {
    return;
  }

  int mid = (left + right) / 2;

  // Recursive calling logic for mergesort
  my_mergesort(left, mid);
  my_mergesort(mid + 1, right);
  merge(left, mid, mid + 1, right);
}

/* this function will be called by the testing program. */
void* parallel_mergesort(void* arg) {
  struct argument* args = (struct argument*)arg;
  int left = args->left;
  int right = args->right;
  int level = args->level;

  // Base case to standard merge-sort at or after cutoff.
  // Level should never exceed cutoff, and something has gone wrong if it does.
  if (level == cutoff || left >= right) {
    my_mergesort(left, right);
    return NULL;
  }

  // Threads
  int mid = (left + right) / 2;

  pthread_t t1, t2;
  struct argument* leftArgs = buildArgs(left, mid, level + 1);
  struct argument* rightArgs = buildArgs(mid + 1, right, level + 1);

  // Make the threads
  pthread_create(&t1, NULL, parallel_mergesort, leftArgs);
  pthread_create(&t2, NULL, parallel_mergesort, rightArgs);

  // Main thread waits on children
  pthread_join(t1, NULL);
  pthread_join(t2, NULL);

  // We don't need the args any more
  free(leftArgs);
  free(rightArgs);

  // Merge
  merge(left, mid, mid + 1, right);
  return NULL;
}

/* we build the argument for the parallel_mergesort function. */
struct argument* buildArgs(int left, int right, int level) {
  struct argument* arg = malloc(sizeof(struct argument));
  if (!arg) {
    // The other mallocs in the test script don't crash on failure, so this
    // check could probably be omitted. Depends if you prefer a controlled
    // crash or a segfault.
    perror("malloc");
    exit(-1);
  }
  arg->left = left;
  arg->right = right;
  arg->level = level;
  return arg;
}
