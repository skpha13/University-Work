% Varianta 2, Grupa 132, Mincu Adrian-Lucian

/* am creat un nou predicat consec2 pentru a avea o variabila X in plus pentru a ma 
ajuta la verificare. La inceput se autopeleaza pentru tail ul listei si X pentru a obtine 
ultima valoare pentru X in cazul consec([5,4,3,2,1]) 1, si verifica daca X este egal cu H,
care este 2 - 1. Cazul de iesire este atunci cand tail ul are lungimea 0, adica este doar un
element in lista, valoare pe care o ia X.
*/

consec2([H|_],H).
consec2([H|T],X) :- consec2(T,X), X is H-1.

consec([]).
consec(L) :- reverse(L,R), R == L.%, consec2(L,_).

% apel1 = consec([1,2,3]), returneaza false
% apel2 = consec([8,7,6,5,4,3,2,1]) returneaza true


% parcurg lista de studenti si verific daca elevul are nota peste prag si daca da ii dau 
% append in R.

listare_studenti([],_,[]).
listare_studenti([student(X,Y)|T],N,R) :- Y >= N, append([X],R,R), listare_studenti(T,N,R).
listare_studenti([student(_,Y)|T],N,R) :- Y < N, listare_studenti(T,N,R).

% listare_studenti([student(Adi,2)],5,[Adi]) rezulta false
% listare_studenti([student(Bobo,6),student(Razvan,7),2,R]) R = [Bobo,Razvan]

