/***
* primes.c
* 
* generate an singly-linked list of the first n primes
***/

#include <stdio.h>
#include <stdlib.h>

// from http://cs/courses/fall2008/algorithms/code/c_examples/node_list.c
typedef struct prime_type *prime;
struct prime_type {
	int value;
	prime next;
};

// constructor for single prime node
prime new_prime(int value, prime next) {
	prime self = (prime) malloc(sizeof(struct prime_type));
	if (self){                  // don't do this if memory wasn't allocated.
		self->value = value;      // set fields
		self->next = next;
	}
	return self;
}

// given a number and a list of all primes lower than that number,
// determine if number is prime
int is_prime(int n, prime prime_node) {
	while (prime_node != NULL) {
		if (n % prime_node->value == 0) {
			return 0;
		}
		prime_node = prime_node->next;
	}
	return 1;
}

// given a list of primes, find the next prime to add to the list
int next_prime(prime first, int last_prime) {
	int to_check = last_prime + 1;
	while (!is_prime(to_check,first)) {
		to_check++;
	}
	//printf("  the prime after %d is %d\n", last_prime, to_check);
	return to_check;
}

// build list of n primes, return first
prime first_n_primes(int n) {
	prime first = new_prime(2,NULL);
	prime cur = first;
	while (n > 1) {
		n--;
		prime next = new_prime(next_prime(first, cur->value), NULL);
		cur->next = next;
		cur = next;
	}
	
	return first;
}

// print list of primes
int print_primes(prime first) {
	prime cur = first;
	printf("  list of primes: ");
	while (cur != NULL) {
		printf("%d ", cur->value);
		cur = cur->next;
	}
	printf("\n");
	
	return 0;
}

int primes_test() {
	prime first = first_n_primes(10);
	return print_primes(first);
}
