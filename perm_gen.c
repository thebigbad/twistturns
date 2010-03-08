/***
* perm_gen.c
* 
* adapted from http://cs/courses/fall2008/algorithms/code/c_examples/structs.c
* and http://cs/courses/fall2008/algorithms/code/c_examples/node_list.c
***/

#include <stdio.h> // printf
#include <stdlib.h> // for malloc

// link
// alias for pointer
typedef struct link_type *link;
// structure pointed to
struct link_type {
	int value;
	link next;
};
// constructor
link new_link(int value, link next){
	link self = (link) malloc(sizeof(struct link_type));
	if (self){                  // don't do this if memory wasn't allocated.
		self->value = value;      // set fields
		self->next = next;
	}
	return self;
}

// build a chain of links
link new_chain(int links) {
	// make an empty chain
	link cur = NULL;
	int i = 0;
	for (i; i < links; i++) {
		link next = new_link(0, cur);
		cur = next;
	}
	return cur; // last link in chain
}

// chain utilities

// chain comparision
// 1 for true, 0 for false
int chains_equal (link first, link second) {
	while (first->next != NULL) {
		if (second->next == NULL) { // if first is longer than second
			return 0;
		}
		else if (first->value != second->value) {
			return 0;
		}
		first = first->next; // advance along chains
		second = second->next;
	}
	// if second is longer than first
	if (second->next != NULL) {
		return 0;
	}
	// if they are the same length and each link has the same value
	return 1;
}

// copy a chain
link chain_cpy(link target) {
	if (target == NULL) {
		return NULL;
	}
	link first = new_link(target->value, NULL);
	link last = first;
	link tmp_tar = target;
	while (tmp_tar->next != NULL) {
		tmp_tar = tmp_tar->next; // advance
		link next = new_link(tmp_tar->value, NULL);
		last->next = next;
		last = next;
	}
	return first;
}

// print chain
int print_chain(link cur) {
	while (cur != NULL) {
		printf("%d ", cur->value);
		cur = cur->next; 
	}
	return 0;
}

int perm_gen_test() {
	link first = new_chain(3); // two empty chains, length 3
	link second = new_chain(3);
	printf("Test (expect 1): %d\n", chains_equal(first, second)); // are equal
	
	second = new_chain(2); // turn one of them into a chain of 2
	printf("Test (expect 0): %d\n", chains_equal(first, second)); // no longer equal
	
	first->next->next->value = 4; // set the value of the last link in the first chain
	printf("Test (expect 4): %d\n", first->next->next->value); // print it
	
	second = new_chain(3); // change second chain back to length 3
	printf("Test (expect 0): %d\n", chains_equal(first, second)); // are not equal
	
	// printing 
	printf("Test (expect 0 0 4): ");
	print_chain(first);
	printf("\n");	
	return 0;
}
