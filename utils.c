/***
* utils.c
* 
* utility subroutines for tree
*
***
* version 2
***
* print_states_dot() now only prints one of the two links,
* using Jim's pointer trick.
* now outputs colored links (red for rotation, red for step)
***/

#include <stdio.h>
#include <stdlib.h>
#include "primes.h"
#include "perm_gen.h"

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

// constructor for advance_node
advance_node new_advance_node(int i, advance_node next, state leads_to) {
	advance_node self = (advance_node) malloc(sizeof(struct advance_node_type));
	if (self){                  // don't do this if memory wasn't allocated.
		self->steps = i;      // set fields
		self->next = next;
		self->leads_to = NULL;
	}
	return self;
}

// 
struct state_type {
	link board;
	state next;
	state rotate;
	advance_node advances;
};

// constructor for single node
state new_state(link chain, state next) {
	state self = (state) malloc(sizeof(struct state_type));
	if (self){                  // don't do this if memory wasn't allocated.
		self->board = chain;      // set fields
		self->next = next;
		self->rotate = NULL; // set later
		self->advances = NULL; // set later
	}
	return self;
}

// utilities

// compute the base signature of a chain of a given size
// i.e. if the board is size 3, the base sig is
// (first prime) * (second prime) * (3rd prime)
// 2*3*5 = 30
int base_signature(prime list) {
	int product = 1;
	while (list != NULL) {
		product *= list->value;
		list = list->next;
	}
	return product;
}

// compute the signature of a given chain
// i.e. if the chain is (0,1,1):
// sig = 2*3*3 = 18
int gen_sig (link chain, prime list) {
	link first_chain = chain;
	prime first_prime = list;
	int product = 1;
	while (chain != NULL) {
		int i = chain->value;
		list = first_prime;
		//printf("  for %d:\n", chain->value);
		while((list != NULL) && (i > 0)) {
			i--;
			list = list->next;
		}
		//printf("    prime is %d\n", list->value);
		product *= list->value;
		chain = chain->next;
	}
	return product;
}

// given the base signature of chain of length n,
// determine if a given chain contains duplicates
int no_dupes(link chain, int sig, prime primes) {
	if (gen_sig(chain, primes) != sig) {
		return 0;
	}
	return 1;
}

// given a chain and a distance, advance chain until that position
// fails for numbers higher than n-1, where n is the size of the chain
link advance(link chain, int r) {
	link old_start = chain; // pointer to first
	// move to the rth node
	while (r > 0) {
		r--;
		chain = chain->next;
	}
	link new_start = chain; // this is the new start of the chain
	// move to the end of the chain
	while (chain->next != NULL) {
		chain = chain->next;
	}
	chain->next = old_start; // connect old start to end
	// add the null to the end of old chain segment
	while (chain->next != new_start) {
		chain = chain->next;
	}
	chain->next = NULL;
	return new_start;
}

// given a chain and a wheel radius, spin the first r elements of the chain
link spin(link chain, int r) {
	link old = chain;
	// move to the rth node
	while (r > 1) {
		r--;
		chain = chain->next;
	}
	link new_start = chain;
	link broken = chain->next; // bit that is not spun
	link end = broken;
	// pull bits off start, add to end of broken
	while (old->next != end) {
		link tmp = old->next;
		old->next = broken;
		broken = old;
		old = tmp;
	}
	new_start->next = broken; // reconnect broken bits to start
	return new_start;
}

// print list of chains
int print_states(state first) {
	printf("  list of states:\n");
	state tmp = first;
	while (tmp != NULL) {
		printf("  %p\n    board: ", tmp);
		link links = tmp->board;
		while (links != NULL) {
			printf("%d ", links->value);
			links = links->next;
		}
		printf("\n");
		printf("    rotate: %p\n", tmp->rotate);
		printf("    steps: ");
		advance_node tmp_ad = tmp->advances;
		while (tmp_ad != NULL) {
			printf("%d->%p ", tmp_ad->steps, tmp_ad->leads_to);
			tmp_ad = tmp_ad->next;
		}
		printf("\n");
		tmp = tmp->next;
	}
	return 0;
}

// radix addition
// returns a new chain
link radix_increment(link target, int base) {
	link new = chain_cpy(target);
	link marker = new;
	while (marker != NULL) {
		if (marker->value < (base - 1)) {
			marker->value++;
			return new;
		}
		marker->value = 0;
		marker = marker->next;
	}
	return NULL; // not big enough
};

// given n (number of links in chain), return list of possible advances
advance_node n_advances(int n) {
	n--;
	advance_node marker = new_advance_node(n, NULL, NULL);
	while (n > 1) {
		n--;
		advance_node new_node = new_advance_node(n, marker, NULL);
		marker = new_node;
	}
	return marker;
}

// given the number of links, create a list of all the chain permutations with 
// that many links
state generate_perms(int n) {
	//printf("  generating possible chains:\n");
	// list of the first n primes
	prime primes = first_n_primes(n);
	// base signature
	int base_sig = base_signature(primes);
	//printf("    base signature: %d\n", base_sig);
	// empty chain list
	state states = new_state(NULL, NULL);
	states->advances = n_advances(n);
	// first one is lowest possible number with all linksn_
	link lowest = new_chain(n);
	link cur = lowest;
	int c = n;
	// fill in the first links
	// i.e. 0 1 2 3
	while (cur != NULL) {
		c--;
		cur->value = c;
		cur = cur->next;
	}
	//printf("    lowest:   ");
	//	print_chain(lowest);
	//printf("\n");
	// highest possible is reverse of lowest
	int k = 0;
	link highest = new_chain(n);
	cur = highest;
	while (cur != NULL) {
		cur->value = k;
		cur = cur->next;
		k++;
	}
	//printf("    highest:  ");
	//	print_chain(highest);
	//printf("\n");
	states->board = lowest; // first link in chain
	state tmp_state = states; // generic marker version
	link poss = chain_cpy(tmp_state->board);
	//printf("    trying: (*success)\n");
	while (!chains_equal(tmp_state->board, highest)) {
		poss = radix_increment(poss, n);
		//printf("      ");
		//print_chain(poss);
		if (no_dupes(poss, base_sig, primes)) {
			state add_state = new_state(chain_cpy(poss), NULL);
			add_state->advances = n_advances(n);
			tmp_state->next = add_state;
			tmp_state = add_state;
			//printf("*");
		}
		//printf("\n");
	} 
	return states;
}

// given a list of states and a board, find the state with the board
state board_search(link query, state states) {
	state marker = states;
	while (marker != NULL) {
		if (chains_equal(query, marker->board)) {
			return marker;
		}
		marker = marker->next;
	}
	return NULL;
}

// given a state, pair it with it's rotated state
int link_rotations(state this_state, state states, int diameter) {
	if (this_state->rotate != NULL) {
		return 0;
	}
	link board = spin(chain_cpy(this_state->board), diameter);
	state mate = board_search(board, states);
	if (mate) {
		this_state->rotate = mate;
		mate->rotate = this_state;
		return 1;
	}
	return 0;
}

// given a state and a step, pair it with it's complementary step
int link_steps(state this_state, state states, advance_node adv, int n) {
	if (adv->leads_to != NULL) {
		return 0;
	}
	link board = advance(chain_cpy(this_state->board), adv->steps);
	state mate = board_search(board, states);
	if (mate) {
		adv->leads_to = mate;
		int i = n - adv->steps;
		advance_node tmp_adv = mate->advances;
		while (tmp_adv->steps != i) {
			tmp_adv = tmp_adv->next;
		}
		tmp_adv->leads_to = this_state;
		return 1;
	}
	return 0;
}

// given a number of links and the wheel diameter, 
// create the list of permutations and link them
state build_universe(int n, int d) {
	state states = generate_perms(n);
	state st_marker = states;
	while (st_marker != NULL) {
		link_rotations(st_marker, states, d);
		advance_node adv_marker = st_marker->advances;
		while (adv_marker->next != NULL) {
			link_steps(st_marker, states, adv_marker, n);
			adv_marker = adv_marker->next;
		}
		st_marker = st_marker->next;
	}
	return states;
}

// print board in dot-friend format
int print_board_dot(link board) {
	printf("\"");
	print_chain(board);
	printf("\"");
	return 1;
}

// print states in dot format
int print_states_dot(state states, int n) {
	printf("graph T {\n");
	state st_marker = states;
	while (st_marker != NULL) {
/***
* if p1 < p2 
* prevents duplicates
* (Jim's idea)
***/	
		// print rotate relationship
		if (st_marker < st_marker->rotate) {
			print_board_dot(st_marker->board);
			printf(" -- ");
			print_board_dot(st_marker->rotate->board);
			printf(" [color=red];\n");
		}
		// print each advance relationship
		advance_node ad_marker = st_marker->advances;
		while (ad_marker != NULL) {
			if (st_marker < ad_marker->leads_to) {
				print_board_dot(st_marker->board);
				printf(" -- ");
				print_board_dot(ad_marker->leads_to->board);
				printf(" [color=blue];\n");
			}
			ad_marker = ad_marker->next;
		}
		st_marker = st_marker->next;
	}
	printf("}\n");
	return 0;
}


int test_utils() {
	printf("***general utility tests\n");
	prime test_prime = first_n_primes(3);
	print_primes(test_prime);
	int base = base_signature(test_prime);
	printf("  base signature: %d\n", base);
	link test_chain = new_chain(3);
	test_chain->value = 0;
	test_chain->next->value = 1;
	test_chain->next->next->value = 2;
	printf("  chain: ");
	print_chain(test_chain);
	printf("\n");
	printf("  chain signature: %d\n", gen_sig(test_chain, test_prime));
	printf("  no dupes? (expect 1): %d\n", no_dupes(test_chain, base, test_prime));
	link test_chain2 = advance(test_chain, 2);
	printf("  advance chain 2: ");
	print_chain(test_chain2);
	printf("\n");
	link test_chain3 = spin(test_chain2, 2);
	printf("  spin chain 2: ");
	print_chain(test_chain3);
	printf("\n");
	test_chain3 = radix_increment(test_chain3, 3);
	printf("  add 1 radix 3: ");
	print_chain(test_chain3);
	printf("\n");
	test_chain3 = radix_increment(test_chain3, 3);
	printf("  add 1 radix 3: ");
	print_chain(test_chain3);
	printf("\n");
	test_chain3 = radix_increment(test_chain3, 3);
	printf("  add 1 radix 3: ");
	print_chain(test_chain3);
	printf("\n");
	test_chain3 = radix_increment(test_chain3, 3);
	printf("  add 1 radix 3: ");
	print_chain(test_chain3);
	printf("\n");
	////////////////////////////////
	printf("***make the universe, pair some states\n");
	state test_state = generate_perms(3);
	link_rotations(test_state, test_state, 2);
	link_steps(test_state->next, test_state, test_state->next->advances->next, 3);
	print_states(test_state);
	///////////////////////////////
	printf("***make the universe, fill all states\n");
	print_states(build_universe(3, 2));
	printf("***output for dot\n");
	print_states_dot(build_universe(3, 2),3);
	return 0;
}

