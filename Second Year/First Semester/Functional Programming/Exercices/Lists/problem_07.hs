-- Transform a list, possibly holding lists as elements into a `flat' list by replacing each list with its elements (recursively)

data NestedList a = Elem a | List [NestedList a]

flatten :: NestedList a -> [a]
flatten (Elem x) = [x]
flatten (List []) = []
flatten (List [Elem x]) = [x]
flatten (List (x:xs)) = flatten x ++ flatten (List xs)

test1 = flatten (List [Elem 1, List [Elem 2, List [Elem 3, Elem 4], Elem 5]]) == [1,2,3,4,5]

