/**
* primes.h : "header" (i.e. API interface) for primes.c code.
*
* adapted from http://cs/courses/fall2008/algorithms/code/c_examples/multiple_files/some_func.h
**/

typedef struct prime_type *prime;
struct prime_type {
	int value;
	prime next;
};

prime first_n_primes(int n);

int print_primes(prime first);
