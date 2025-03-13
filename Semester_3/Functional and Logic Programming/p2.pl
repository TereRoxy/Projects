% 12.
% a. Define a predicate to add after every element from a list, the divisors of that number.
% b. For a heterogeneous list, formed from integer numbers and list of numbers, define a predicate to add in
% every sublist the divisors of every element.
% Eg.: [1, [2, 5, 7], 4, 5, [1, 4], 3, 2, [6, 2, 1], 4, [7, 2, 8, 1], 2] =>
% [1, [2, 5, 7], 4, 5, [1, 4, 2], 3, 2, [6, 2, 3, 2, 1], 4, [7, 2, 8, 2, 4, 1], 2]

% a
% divisors(N:number, D:number, R:list)
% flow model (i, i, o)

% find the divisors of a number and add them to a list
% divisor exceeds the number
divisors(N, D, []) :- D >= N, !.

% D is a divisior of N, add it to the list of divisors
divisors(N, D, [D|Res]) :-
    D =< N,
    N mod D =:= 0, 
    D1 is D + 1,
    divisors(N, D1, Res).

% D is not a divisor of N, continue
divisors(N, D, Res) :-
    D =< N,
    N mod D =\= 0,       % \+ is also a negation operator 
    D1 is D + 1,
    divisors(N, D1, Res).

% wrapper function
divisors(N, D) :- divisors(N, 2, D).

% add_divisors(L:list, R:list)
% flow model (i, o)
% process the given list and add the divisors of each element
add_divisors([], []).
add_divisors([H|T], [H|Res]) :-
    divisors(H, Divisors),
    append(Divisors, Res1, Res),
    add_divisors(T, Res1).

% b
% add the divisors of each element of the sublist
add_div_b([], []).

add_div_b([H|T], [H|Res]) :-
    integer(H),
    add_div_b(T, Res).

add_div_b([H|T], [Res|Res1]) :-
    is_list(H),
    add_divisors(H, Res),
    add_div_b(T, Res1).