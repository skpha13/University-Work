fib(0,1).
fib(1,1).
fib(N,X) :- 2 =< N, M is N - 1, fib(M, Y), P is N - 2, fib(P, Z), X is Y + Z.

/* mai eficient */
fibo(0,0,1).
fibo(1,1,1).
fibo(N,Z,X) :- 2 =< N, M is N-1, fibo(M,Y,Z), X is Y+Z.

fibg(N,X) :- fibo(N,_,X).