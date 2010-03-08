/***
* tturns_small.c
*
* Ryan Wolf
*
***
* version 2: same great taste, plus the commandline
* arguements you want.
***
* outputs a dot file of all of the relationships between
* possible states of a game of twist turns
* usage:
* $ time ./tturns_small 3 2
* graph T {
* "2 1 0 " -- "1 2 0 ";
* "2 1 0 " -- "1 0 2 ";
* "2 1 0 " -- "0 2 1 ";
* "1 2 0 " -- "2 1 0 ";
* "1 2 0 " -- "2 0 1 ";
* "1 2 0 " -- "0 1 2 ";
* "2 0 1 " -- "0 2 1 ";
* "2 0 1 " -- "0 1 2 ";
* "2 0 1 " -- "1 2 0 ";
* "0 2 1 " -- "2 0 1 ";
* "0 2 1 " -- "2 1 0 ";
* "0 2 1 " -- "1 0 2 ";
* "1 0 2 " -- "0 1 2 ";
* "1 0 2 " -- "0 2 1 ";
* "1 0 2 " -- "2 1 0 ";
* "0 1 2 " -- "1 0 2 ";
* "0 1 2 " -- "1 2 0 ";
* "0 1 2 " -- "2 0 1 ";
* }
*
* real	0m0.002s
* user	0m0.000s
* sys	0m0.004s
*
***/

#include <stdio.h>
#include <stdlib.h>
#include "utils.h" // twist turns utilities

main(int argc, char* argv[]) {
	if (argc == 3 && atoi(argv[1]) >= atoi(argv[2])) {
		state universe = build_universe(atoi(argv[1]),atoi(argv[2]));
		print_states_dot(universe);
	}
	else {
		printf("  usage: .tturns_small 'number of tiles' 'diameter of wheel'\n");
	}
	return 0;
}
