parent(bill, mary).
parent(mary, john).

ancestor(X, Y) :- parent(X, Y).
ancestor(X, Y) :- parent(X, Z), ancestor(Z, Y).

?- ancestor(john, X).

?- ancestor(mary, X).

?- ancestor(bill, X).

?- ancestor('some string \\ \' \\', X).
