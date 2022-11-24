trans_a_b([],[]).
trans_a_b([a|X],[b|Y]) :- trans_a_b(X,Y).

scalarMult(_,[],[]).
scalarMult(N,[H|T],[X|Y]) :- X is N*H, scalarMult(N,T,Y).

dot([],[],0).
dot([H|T],[X|Y],M) :- dot(T,Y,N), M is N+H*X.

max([],0).
max([H|T],X) :- max(T,X), X>=H.
max([H|T],H) :- max(T,X), H>X.