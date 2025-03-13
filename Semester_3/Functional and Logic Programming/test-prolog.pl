% data fiind o lista de numere intregi, adaugati o valoare data dupa primul, al treilea, al 7lea si al 15lea samd element din lista
% pt prima adaugare elem trb adaugat o data, pt a doua de 2 ori, pt a treia de 3 ori samd
% ex: [1,2,3,4,5,6,7,8,9,10], 0 => [1, 0, 2, 3, 0, 0, 4, 5, 6, 7, 0, 0, 0, 8, 9, 10]

% matheatical model
% insert_values(l1..ln, value, pos, count) = [], n = 0
%                                           = l1 + insert_values(l2..ln, value, pos + 1, count), pos is not a power of 2 - 1
%                                           = value*count + insert_values(l1..ln, value, pos + 1, count + 1), pos is a power of 2 - 1
%
% insert_n_times(value, n) = [], n = 0
%                          = value + insert_n_times(value, n - 1), n > 0


% Predicate to check if a number is a power of 2 minus 1
is_position(0).
is_position(N) :-
    N > 0,
    N1 is N + 1,
    is_power_of_two(N1).

% Predicate to check if a number is a power of 2
is_power_of_two(1).
is_power_of_two(N) :-
    N > 1,
    N mod 2 =:= 0,
    N1 is N // 2,
    is_power_of_two(N1).

% Helper predicate to insert a value N times
insert_n_times(_, 0, Res, Res).
insert_n_times(Value, N, [Value|Rest], FinalRes) :-
    N > 0,
    N1 is N - 1,
    insert_n_times(Value, N1, Rest, FinalRes).

% Main predicate
insert_values([], _, _, _, []).
insert_values([H|T], Value, Pos, Count, [H|Result]) :-
    \+ is_position(Pos),
    NextPos is Pos + 1,
    insert_values(T, Value, NextPos, Count, Result).
insert_values([H|T], Value, Pos, Count, [H|Result]) :-
    is_position(Pos),
    insert_n_times(Value, Count, Result, TempResult),
    NextCount is Count + 1,
    NextPos is Pos + 1,
    insert_values(T, Value, NextPos, NextCount, TempResult).
    
% Wrapper
main(L, Value, Result) :-
    insert_values(L, Value, 1, 1, Result).