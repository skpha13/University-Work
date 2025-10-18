% house functor:
% house(No., Color, Nationality, Drink, Cigarette, Animal)

left(X, Y) :- X =:= Y - 1.
next(X, Y) :- X =:= Y + 1; X =:= Y - 1.

akinator(Solution, FishPossesor) :- 
    Solution = [
      house(1, _, _, _, _, _),
      house(2, _, _, _, _, _),
      house(3, _, _, _, _, _),
      house(4, _, _, _, _, _),
      house(5, _, _, _, _, _)
	],
    
member(house(_, red, british, _, _, _), Solution),
    
% member(house(), Solution),
member(house(N, _, norwegian, _, _, _), Solution),
member(house(B, blue, _, _, _, _), Solution),
next(N, B),

member(house(G, green, _, _, _, _), Solution),
member(house(W, white, _, _, _, _), Solution),
left(G, W),
    
member(house(_, green, _, coffee, _, _), Solution),
member(house(3, _, _, milk, _, _), Solution),

member(house(_, yellow, _, _, dunhill, _), Solution),

member(house(1, _, norwegian, _, _, _), Solution),

member(house(_, _, swedish, _, _, dog), Solution),
    
member(house(_, _, _, _, pall_mall, bird), Solution),
    
member(house(M, _, _, _, malboro, _), Solution),
member(house(C, _, _, _, _, cat), Solution),
next(M, C),

member(house(_, _, _, beer, windfield, _), Solution),

member(house(H, _, _, _, _, horse), Solution),
member(house(D, _, _, _, dunhill, _), Solution),
next(H, D),
    
member(house(_, _, german, _, rothmans, _), Solution),
    
member(house(A, _, _, _, malboro, _), Solution),
member(house(B, _, _, water, _, _), Solution),
next(A, B),
    
member(house(_, _, FishPossesor, _, _, peste), Solution).