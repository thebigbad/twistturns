/**
* perm_gen.h : "header" (i.e. API interface) for perm_gen.c code.
*
* adapted from http://cs/courses/fall2008/algorithms/code/c_examples/multiple_files/some_func.h
**/

typedef struct link_type *link;
struct link_type {
	int value;
	link next;
};

link new_chain(int links);

link chain_cpy(link target);

int chains_equal (link first, link second);

int print_chain(link cur);
