listaNelem(_,0,[]).
listaNelem([X|Y],N,[H|T]) :- N > 0, 
    					P is N - 1,
    					member(H,[X|Y]),
    					listaNelem(Y,P,T).