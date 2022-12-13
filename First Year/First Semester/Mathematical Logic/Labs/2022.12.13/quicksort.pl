split() :- .

quicksort([],[]).
quicksort([H|T],L) :- split(H,T,A,B), quicksort(A,M), quicksort(B,N), append(M,[H|N],L).