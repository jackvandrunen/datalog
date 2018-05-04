/* a test comment */
parent(bill, mary).
parent(mary, john).

ancestor(X, Y) :- /* another test comment */ parent(X, Y).
ancestor(X, Y) :- parent(X, Z), ancestor(Z, Y).

?- ancestor(john, X).

?- ancestor(mary, X).

?- ancestor(bill, X).

/* big
comment
incoming
**/

?- ancestor('some string \\ \' \\', X).

?- ancestor(X, 6789).
/* ending comment */
