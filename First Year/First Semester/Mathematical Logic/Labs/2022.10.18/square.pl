line(0,_) :- nl.
line(X,C) :- X>0, Y is X-1, write(C), line(Y,C).

rectangle(0,_,_) :- nl.
rectangle(X,Z,C) :- X>0, Y is X-1, line(Z,C), nl, rectangle(Y,Z,C).

square(X,C) :- rectangle(X,X,C).