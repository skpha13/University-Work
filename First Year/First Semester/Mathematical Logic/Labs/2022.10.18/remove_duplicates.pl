remove_duplicates([],[]).

remove_duplicates([H|L],M) :- 
    remove_duplicates(L,M), member(H,M).
remove_duplicates([H|L],[H|M]) :-
    remove_duplicates(L,M), not(member(H,M)).
