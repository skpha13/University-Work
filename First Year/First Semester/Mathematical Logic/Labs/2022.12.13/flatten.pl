listN([],0).
listN([a|T],N) :- N>0, M is N-1, listN(T,M).

reva(L,R) :- revah(L,[],R).
revah([],R,R).
revah([H|T],S,N) :- revah(T,[H|S],N).

revd(L,R) :- revdh(L,(R,[])).
revdh([],(R,R)).
revdh([H|T],(N,S)) :- revdh(T,(N,[H|S])).

flatten([],[]).
flatten([H|T],[H|R]) :- not(is_list(H)), flatten(T,R).
flatten([[]|T],R) :- flatten(T,R).
flatten([[A|X]|T],R) :- flatten([A|X],S), flatten(T,U), append(S,U,R). 

flattend(L,R) :- flattendh(L,(R,[])).
flattendh([],(R,R)).
flattendh([H|T],([H|R],S)) :- not(is_list(H)), flattendh(T,(R,S)).
flattendh([[]|T],(R,S)) :- flattendh(T,(R,S)).
flattendh([[A|X]|T],(R,S)) :- flattendh([A|X],(R,W)), flattendh(T,(W,S)). 
