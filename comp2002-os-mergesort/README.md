

## Operating Systems Assignment 3 - Concurrency

Authors: 
- Caden Ratcliffe – a1926128
- Rajkarthick Raju – a1889911
- Dineth Wickramasekara – a1894205

Group name: Group 34

## Overview


This project is an implementation of parallel merge sort in C, using the pthreads library. It follows a recursive divide-and-conquer approach where each time the array is split into subarrays, new threads are spawned to sort them concurrently. A user-specified cutoff level limits the recursion depth for thread creation, with level 0 running a serial merge sort, and higher levels enbling increasing parallelism. The test program generates a random array, sorts it, and reports the execution time.

## Manifest

| File | Description |
|------|--------------|
| `Makefile` | Builds the project using gcc and links the pthread library. |
| `mergesort.c` | Implements parallel merge sort using recursion and pthreads. |
| `mergesort.h` | Contains the global variables, data structures, and function prototypes. |
| `test-mergesort.c` | Driver program that generates input data, calls the sorting functions, and reports runtime. |
| `README.md` | Project documentation and testing results. |
| `testscript.sh` | Bash script to automatically run `./test-mergesort` with 6 different array sizes (starting from 2 items - up to 100,000,000 items) and 9 cutoff levels (0 - 8)|
| `testresults/` | Contains the test results from running  `testscript.sh`. Results and files explained in _Testing_ section. |


## Building the project

To build the program, open a terminal in the project directory and run:

```bash
make
```

This will compile all of the source files, link them with the pthread library and produce the executable `test-mergesort` in the same folder. You can then run the executable using:
```bash
./test-mergesort <input_size> <cutoff_level> <seed>
```

Example - the following command will generate an array of 10,000 random integers and run parallel merge sort, with a cutoff level of 2. Using the random seed `1234` will make sure the randomly generated input array is the same each time, as long as the array size is consistent.
```bash
./test-mergesort 10000 2 1234
```




## Features and usage

### Features
A multithreaded version of merge sort using the `pthread` library. The array is recursively divided and sorted in parallel up to a user-defined cutoff level, and then merged. Main features are:

- **Configurable cutoff level** using a `cutoff` parameter that controls how many levels of threading are created. A higher cutoff value creates more threads and can improve performance _up to a limit_.
    - When `cutoff = 0`, the program performs a standard single-threaded (serial) merge sort.  
  - When `cutoff > 0`, it performs parallel merge sort with multiple threads.
  
- **Automatic performance testing** with `test-mergesort.c` which measures and displays the total sorting time for each run, rounded up to 2 decimal points.

- **Determinisitic input generation** using a random seed value that ensures the same input array is generated for reproducible testing.

### Usage

After the building the project using `make` (explained in above section), you can run the executable using:

```bash
./test-mergesort <input_size> <cutoff_level> <seed>
```

An an example, the following command will generate an array of 10,000 random integers and run parallel merge sort, with a cutoff level of 2. Using the random seed `1234` will make sure the randomly generated input array is the same each time, as long as the array size is consistent.
```bash
./test-mergesort 10000 2 1234
```

We have provided a bash script `testscript.sh` which automatically runs ./test-mergesort with 6 different array sizes (starting from 2 items - up to 100,000,000 items) and 9 cutoff levels (0 - 8). You can run this using the following commands **while in your project folder**:
```bash
sudo chmod +x testscript.sh
./testscript.sh
```
---
#### Running the algorithm on different types of arrays 
By default, `test-mergesort.c` will run the algorithm on a randomly generated array using the `generate_random_array()` function:
```c
// generate random input
generate_random_array(A, n, seed);
```
You can replace that line in **`main()`** with one of the following snippets to test different input patterns.


##### 1. Already Sorted Array
This creates an ascending array `[0, 1, 2, ..., n-1]`.

```c
for (int i = 0; i < n; i++) {
    A[i] = i;
}
```

##### 2. Reverse Sorted Array
This creates a descending array `[n-1, n-2, ..., 0]`.

```c
for (int i = 0; i < n; i++) {
    A[i] = n - i;
}
```

##### 3. Duplicate Elements Array
This fills the array with repeating values to test handling of duplicates.

```c
for (int i = 0; i < n; i++) {
    A[i] = i % 5;   // repeats 0, 1, 2, 3, 4
}
```
***Please note that after replacing this segment in `test-mergesort.c`***, you will have to modify the `Makefile`, replacing the `-std=gnu89` flag with `-std=c99` in order to successfully recompile the program. After modifying the makefile, you can repeat the steps in the `Building the project` section to run the program as usual.

## Testing
After we were able to successfully compile and run our program using the specified command `./test-mergesort <input_size> <cutoff_level> <seed>`, we wrote a correctness and performance test using a bashscript (`testscript.sh`) to repeatedly run the program with 6 different array sizes (starting from 2 items - up to 100,000,000 items) and 9 cutoff levels (0 - 8).
```bash
# test sizes and cutoff levels
sizes=(2 10 1000 100000 1000000 100000000)
cutoffs=(0 1 2 3 4 5 6 7 8)
```
We started with an array size of 2, as it is the smallest non-trivial input the program can sort,  and ended with **100,000,000 elements**, as recommended by the assignment specification. 
This also provided a good case for testing the performance of our algorithm on large datasets.  We included intermediate array sizes (10, 1,000, 100,000, 1,000,000) to observe how performance scales across different input sizes.


We chose 9 cutoff levels so we could observe the performance gain as parallelism increases.  The following output shows the results for the largest test case (`n = 100,000,000`). The full output logs are available in `testresults/default_test_results_1.txt` and `testresults/default_test_results_2.txt`:

```txt
Test: n=100000000 cutoff=0 ... PASSED | Output: Sorting 100000000 elements took 16.27 seconds.
Test: n=100000000 cutoff=1 ... PASSED | Output: Sorting 100000000 elements took 8.57 seconds.
Test: n=100000000 cutoff=2 ... PASSED | Output: Sorting 100000000 elements took 5.08 seconds.
Test: n=100000000 cutoff=3 ... PASSED | Output: Sorting 100000000 elements took 3.73 seconds.
Test: n=100000000 cutoff=4 ... PASSED | Output: Sorting 100000000 elements took 2.71 seconds.
Test: n=100000000 cutoff=5 ... PASSED | Output: Sorting 100000000 elements took 2.56 seconds.
Test: n=100000000 cutoff=6 ... PASSED | Output: Sorting 100000000 elements took 2.94 seconds.
Test: n=100000000 cutoff=7 ... PASSED | Output: Sorting 100000000 elements took 2.69 seconds.
Test: n=100000000 cutoff=8 ... PASSED | Output: Sorting 100000000 elements took 2.74 seconds.
```

Based on this output, we observed a dramatic performance improvement (**~2× speedup**) between the serial merge sort (`cutoff = 0`) and the parallel version (`cutoff = 1`). Performance continued to improve up to around `cutoff = 4`, after which the gains started to plateau, indicating that the number of threads is no longer the bottleneck at higher cutoff levels.  At around `cutoff = 7` or `8`, performance began to decrease slightly, likely due to thread management overhead. This followed the pattern given in the _Expected Output_ section of the assignment specification, so we decided that the alogorithm itself would not require further modification.

#### Testing edge cases
Afterwards, we tested edge cases by modifying `test-mergesort.c` as described in the  
_“Running the algorithm on different types of arrays”_ section above.  
The full test results are located in the `testresults/` folder, with summaries below:

- Already sorted arrays: `testresults/already_sorted_array_test_results.txt`  
- Reverse sorted arrays: `testresults/reverse_sorted_array_test_results.txt`  
- Arrays with duplicate elements: `testresults/duplicate_elements_array_test_results.txt`


All three edge cases followed the same general performance pattern as the default random arrays,  with approximately a **2×speedup** between `cutoff = 0` and `cutoff = 1`, maximum efficiency around `cutoff = 4–5`, and a slight decline in performance beyond `cutoff = 7–8`.  However, the runtime for `n = 100,000,000` in the edge cases were on average less than half of that observed for randomly generated arrays.


## Known Bugs

List known bugs that you weren't able to fix (or ran out of time to fix).
Our program currently does not contain any known bugs.

## Reflection and Self Assessment

Discuss the issues you encountered during development and testing. What
problems did you have? What did you have to research and learn on your own?
What kinds of errors did you get? How did you fix them?

What parts of the project did you find challenging? Is there anything that
finally "clicked" for you in the process of working on this project? How well
did the development and testing process go for you?

#### Challenges during testing 
After fixing the initial errors mentioned earlier, the testing process became fairly straightforward since we were able to automate it using a bash script (`testscript.sh`). Testing both performance and correctness was simple; we ran the script against the default executable generated from `test-mergesort.c`, and were able to match the pattern given in the _Expected Results_ section of the assignment brief, therefore deciding that no more modifications to the algorithm were necessary.

We also tested 3 edge cases (already sorted arrays, reverse sorted arrays, and arrays with duplicate elements), which required minor modifications to `test-mergesort.c`, as explained in the _Usage_ section. The only challenge encountered was related to compilation: we had to update the Makefile by changing the `-std=gnu89` flag to `-std=c99` in order to successfully compile and run the edge case tests. This change was necessary because the updated `test-mergesort.c` used variable declarations inside `for` loop initializers (ex: `for (int i = 0; i < n; i++)`), which is not supported under the older C89/gnu89 standard. We did however revert this change after completing edge-case testing in order to ensure consistency with the assignment specifications and avoid potential problems with gradescope. 


## Sources Used

We used the following sources to understand how mergesort and parallel merge sort works, before doing our implementation:
- https://www.youtube.com/watch?v=KF2j-9iSf4Q&t=372s
- https://www.youtube.com/watch?v=3j0SWDX4AtU&t=519s


