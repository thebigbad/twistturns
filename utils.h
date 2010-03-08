/**
* utils.h : "header" (i.e. API interface) for utils.c code.
*
* adapted from http://cs/courses/fall2008/algorithms/code/c_examples/multiple_files/some_func.h
**/

#include "primes.h"
#include "perm_gen.h"

// c seems to want all the definitions, so here they are agian
// DEFINTIONS
// type definitions used later
typedef struct advance_node_type *advance_node;
typedef struct state_type *state;

// since the number of times you can advance the tiles is variable,
// links to the states that result from those changes will go into an
// array
struct advance_node_type {
	int steps; // how far to advance
	state leads_to; // what state you enter after making that move
	advance_node next;
};

// 
struct state_type {
	link board;
	state next;
	state rotate;
	advance_node advances;
};

/***
*
* API
*
***/

// build_universe
// generates the "universe" of a game of twistturns
// (each of the possible board states, and the links between them)
// usage: state built_universe(the number of tiles in the game, the diameter of the wheel);
state build_universe(int n, int d);

// print_states_dot
// prints out the relationships between each state in a universe in dot format
// usage: print_states_dot(universe);
int print_states_dot(state states);
