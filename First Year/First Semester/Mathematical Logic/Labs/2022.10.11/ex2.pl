female(mary).
female(sandra).
female(juliet).
female(lisa).
male(peter).
male(paul).
male(dony).
male(bob).
male(harry).
parent(bob, lisa).
parent(bob, paul).
parent(bob, mary).
parent(juliet, lisa).
parent(juliet, paul).
parent(juliet, mary).
parent(peter, harry).
parent(lisa, harry).
parent(mary, dony).
parent(mary, sandra).

father_of(Father,Child) :- parent(Father,Child), male(Father).
mother_of(Mother,Child) :- parent(Mother,Child), female(Mother).
grandfather_of(Grandfather, Child) :- parent(Grandfather,P), parent(P, Child), male(Grandfather).
grandmother_of(Gm,C) :- parent(Gm,P), parent(P,C), female(Gm).
sister_of(S,C) :- parent(X,S),parent(X,C), female(S), S\=C.
brother_of(B,C) :- parent(X,B), parent(X,C), male(B), B\=C.
aunt_of(A,P) :- parent(Y,P), sister_of(A,Y).
uncle_of(U,P) :- parent(Y,P), brother_of(U,Y).