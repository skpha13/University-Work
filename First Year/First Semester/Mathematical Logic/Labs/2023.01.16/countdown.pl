word_letters(X,Y) :- atom_chars(X,Y).

liminus([C|L],C,L).
liminus([D|L],C,[D|M]) :- D\==C, liminus(L,C,M).

cover([],_).
cover([H|T],L) :- liminus(L,H,M), cover(T,M).

solution(Letters, Word, Len) :- word(Word), word_letters(Word,WordLetters), length(WordLetters,Len), cover(WordLetters, Letters).

search_solution(_,'no solution',0).
search_solution(ListLetters,Word,X) :- X > 0, solution(ListLetters,Word,X).
search_solution(ListLetters,Word,X) :- X > 0, not(solution(ListLetters,Word,X)), Y is X-1, search_solution(ListLetters,Word,Y).

topsolution(ListLetters,Word) :- length(ListLetters, MaxScore),  search_solution(ListLetters,Word,MaxScore).