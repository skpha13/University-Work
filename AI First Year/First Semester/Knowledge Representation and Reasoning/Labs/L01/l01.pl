parent(ion,maria).
parent(ana,maria).
parent(ana,dan).
parent(maria,elena).
parent(maria,radu).
parent(elena,nicu).
parent(radu,george).
parent(radu,dragos).

child(X, Y) :-
    parent(Y, X).
    
sibling(X, Y) :-
    parent(Z, X),
    parent(Z, Y),
    X \= Y.

grandparent(X, Z) :-
    parent(X, Y),
    parent(Y, Z).

pred(X,Y):-parent(X,Y).
pred(X,Z):-parent(X,Y), pred(Y,Z).

ancestor(X,Y) :-
    parent(X,Y);
    (parent(X,Z), ancestor(Z,Y)).

boy(radu, 32).
boy(dragos, 23).
boy(ion, 50).
boy(nicu, 60).

ageboys(L) :- findall(Age, boy(_, Age), L).

f(X,Y) :- (   
    X =< 3 -> Y = 0
    ; X =< 6 -> Y = 2
    ; Y = 4
).

%%%%%%%%%% 01 %%%%%%%%%%
max(X, Y, Z) :- (   
    X =< Y -> Z = Y
    ; Z = X
).

/* OR

max(X,Y,X) :- X >= Y, !.
max(_,Y,Y).

*/

%%%%%%%%%% 02 %%%%%%%%%%
member(X, [X|_]).
member(X, [_|T]) :- member(X, T).

concat([], L, L).
concat([H|T], L2, [H|L3]) :-
    concat(T, L2, L3).

%%%%%%%%%% 03 %%%%%%%%%%
alternateSum(L, S) :- alternateSum(L, 0, S).

alternateSum([], _, 0).
alternateSum([H|T], I, S) :-
    ( 0 is I mod 2 ->
        S1 is H
    ;
        S1 is -H
    ),
    I1 is I + 1,
    alternateSum(T, I1, S2),
    S is S1 + S2.

%%%%%%%%%% 04 %%%%%%%%%%
eliminateOne(_, [], []).
eliminateOne(X, [X|T], L) :- L = T.

eliminate(_, [], []).
eliminate(X, [X|T], L) :- eliminate(X, T, L).
eliminate(X, [Y|T], [Y|L]) :- eliminate(X, T, L).

%%%%%%%%%% 05 %%%%%%%%%%
reverse([], []).
reverse([H|T], R) :-
    reverse(T, TMP),
    concat(TMP, [H], R).

insertAll(X, L, [X|L]).
insertAll(X, [H|T], [H|R]) :-
    insertAll(X, T, R).

permutations([], []).
permutations([H|T], R) :-
	permutations(T, TMP),
	insertAll(H, TMP, R).

%%%%%%%%%% 06 %%%%%%%%%%
count(_, [], 0).
count(X, [X|T], C) :- 
    count(X, T, C1),
    C is C1 + 1.
count(X, [_|T], C) :- count(X, T, C).

%%%%%%%%%% 07 %%%%%%%%%%
insertAt(X, I, L, R) :- insert(X, I, L, 0, R).

insert(X, _, [], _, [X]).

insert(X, I, L, I, [X|L]).
insert(X, I, [H|T], K, [H|R]) :-
    K1 is K + 1,
    insert(X, I, T, K1, R).

%%%%%%%%%% 08 %%%%%%%%%%
mergeSorted([], L, L).
mergeSorted(L, [], L).

mergeSorted([X|XS], [Y|YS], [X|R]) :-
	X =< Y,
    mergeSorted(XS, [Y|YS], R).
mergeSorted([X|XS], [Y|YS], [Y|R]) :-
    X > Y,
    mergeSorted([X|XS], YS, R).
 
    