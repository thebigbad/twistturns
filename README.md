TwistTurns
===

Once when I was working on some (homework)[http://cs.marlboro.edu/courses/fall2008/algorithms/special/assignments#2008-09-18], I became distracted by the idea that I could graph all possible states of ("Top Spin")[http://www.jaapsch.net/puzzles/topspin.htm]-esque puzzles. After holing up in my room for two days, this project was the result.

I didn't know anything about making graphs, so I offloaded that bit to (dot)[http://www.graphviz.org/]. While looking up ways to generate permutations, I came across ("Generation of Permutations by Addition")[http://www.jstor.org/pss/2003066], which I used to write perm_gen.c.

Usage
---

    $ make
    $ ./tturns 3 2
    graph T {
    "2 1 0 " -- "1 2 0 " [color=red];
    "2 1 0 " -- "1 0 2 " [color=blue];
    "2 1 0 " -- "0 2 1 " [color=blue];
    "1 2 0 " -- "2 0 1 " [color=blue];
    "1 2 0 " -- "0 1 2 " [color=blue];
    "2 0 1 " -- "0 2 1 " [color=red];
    "2 0 1 " -- "0 1 2 " [color=blue];
    "0 2 1 " -- "1 0 2 " [color=blue];
    "1 0 2 " -- "0 1 2 " [color=red];
    }

See samples/ for output from dot for a few values.

Thanks
---

* Jim Mahoney, for teaching a rad class
* Binary Arts, for making an puzzle that was fun to hack about
* The folks at graphiz, for writing an awesome free graphing utility
* John R. Howell, for making permutations so easy I could dive in before taking that Probability class

TODO
---

I don't know if I'll get back to this project, but...

* soup it up until it can handle 20d4
* primes.c seems to be using a dingy variation of the (sieve)[http://www.cs.hmc.edu/~oneill/papers/Sieve-JFP.pdf]. run benchmark on this and the related project euler (answer)[http://github.com/thebigbad/proud-jack-foiler/blob/master/010/010.pl]--I can do better.
* see if I can make the permutations bit more generic for I can reuse this code for the "book of tic-tac-toe" project
