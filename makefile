CC = gcc

tturns_small:	tturns_small.o
		$(CC) -O3 primes.o perm_gen.o utils.o tturns_small.o -o tturns_small

tturns_small.o:	utils.o utils.h tturns_small.c
		$(CC) -O3 -c primes.o perm_gen.o utils.o tturns_small.c

utils.o:		primes.o perm_gen.o utils.c utils.h
		$(CC) -O3 -c primes.o perm_gen.o utils.c

primes.o: 	primes.c primes.h
		$(CC) -O3 -c primes.c

perm_gen.o: 	perm_gen.c primes.h
		$(CC) -O3  -c perm_gen.c

clean:
		rm -f *.o tturns_small
