% Sort a list with removing the double values. E.g.: [4 2 6 2 3 4] --> [2 3 4 6]

% remove_doubles(L:list, R:list)
% flow model: (i o), (i i)
remove_doubles([], []).
remove_doubles([H|T], R) :- 
    member(H, T), 
    remove_doubles(T, R).

remove_doubles([H|T], [H|R]) :-
    \+ member(H, T),
    remove_doubles(T, R).

% Predicate to insert an element into a sorted list
insert_sorted(X, [], [X]).
insert_sorted(X, [H|T], [X,H|T]) :- X =< H.
insert_sorted(X, [H|T], [H|R]) :- X > H, insert_sorted(X, T, R).

% Predicate to sort a list using insertion sort
insertion_sort([], []).
insertion_sort([H|T], Sorted) :-
    insertion_sort(T, SortedTail),
    insert_sorted(H, SortedTail, Sorted).

% Predicate to sort a list and remove duplicates
sort_and_remove_duplicates(List, Result) :-
    remove_doubles(List, NoDuplicates),
    insertion_sort(NoDuplicates, Result).

% Predicate to merge two sorted lists and remove duplicates
merge_sorted([], L, L).
merge_sorted(L, [], L).
merge_sorted([H1|T1], [H2|T2], [H1|Result]) :-
    H1 < H2,
    merge_sorted(T1, [H2|T2], Result).
merge_sorted([H1|T1], [H2|T2], [H2|Result]) :-
    H1 > H2,
    merge_sorted([H1|T1], T2, Result).
merge_sorted([H|T1], [H|T2], [H|Result]) :-
    merge_sorted(T1, T2, Result).

% Predicate to convert a list representation of a number to an integer
list_to_number([], 0).
list_to_number([H|T], Number) :-
    list_to_number(T, RestNumber),
    length(T, Length),
    Number is H * 10^Length + RestNumber.

% Predicate to convert an integer to a list representation
number_to_list(0, [0]).
number_to_list(Number, List) :-
    Number > 0,
    number_to_list_helper(Number, [], List).

number_to_list_helper(0, Acc, Acc).
number_to_list_helper(Number, Acc, List) :-
    Number > 0,
    Digit is Number mod 10,
    NewNumber is Number // 10,
    number_to_list_helper(NewNumber, [Digit|Acc], List).

% Predicate to sum two numbers in list representation
sum_list_numbers(List1, List2, Result) :-
    list_to_number(List1, Number1),
    list_to_number(List2, Number2),
    Sum is Number1 + Number2,
    number_to_list(Sum, Result).

% Predicate to substitute all occurrences of an element in a list with all elements of another list
subst([], _, _, []).
subst([H|T], Elem, SubstList, Result) :-
    H =:= Elem,
    subst(T, Elem, SubstList, RestResult),
    append(SubstList, RestResult, Result).
subst([H|T], Elem, SubstList, [H|Result]) :-
    H =\= Elem,
    subst(T, Elem, SubstList, Result).

% Predicate to substitute all occurrences of an element in a list with all elements of another list
subst([], _, _, []).
subst([H|T], Elem, SubstList, Result) :-
    H =:= Elem,
    subst(T, Elem, SubstList, RestResult),
    append(SubstList, RestResult, Result).
subst([H|T], Elem, SubstList, [H|Result]) :-
    H =\= Elem,
    subst(T, Elem, SubstList, Result).

% Predicate to substitute all occurrences of an element in a list with all elements of another list
subst([], _, _, []).
subst([H|T], Elem, SubstList, Result) :-
    H =:= Elem,
    subst(T, Elem, SubstList, RestResult),
    append(SubstList, RestResult, Result).
subst([H|T], Elem, SubstList, [H|Result]) :-
    H =\= Elem,
    subst(T, Elem, SubstList, Result).

% Predicate to substitute all occurrences of an element in a list with all elements of another list
subst([], _, _, []).
subst([H|T], Elem, SubstList, Result) :-
    H =:= Elem,
    subst(T, Elem, SubstList, RestResult),
    append(SubstList, RestResult, Result).
subst([H|T], Elem, SubstList, [H|Result]) :-
    H =\= Elem,
    subst(T, Elem, SubstList, Result).

% Predicate to process a heterogeneous list
replace_in_sublists([], _, []).
replace_in_sublists([H|T], SubstList, [ProcessedH|Result]) :-
    is_list(H),
    H = [FirstElem|_],
    subst(H, FirstElem, SubstList, ProcessedH),
    replace_in_sublists(T, SubstList, Result).
replace_in_sublists([H|T], SubstList, [H|Result]) :-
    \+ is_list(H),
    replace_in_sublists(T, SubstList, Result).


% Helper predicate to multiply a single digit with carry
multiply_digit(Digit, Multiplier, Carry, ResultDigit, NewCarry) :-
    Product is Digit * Multiplier + Carry,
    ResultDigit is Product mod 10,
    NewCarry is Product // 10.

% Predicate to multiply a list of digits by a given digit
multiply_list([], _, 0, []).
multiply_list([], _, Carry, [Carry]) :- Carry > 0.
multiply_list([H|T], Multiplier, Carry, [ResultDigit|Result]) :-
    multiply_digit(H, Multiplier, Carry, ResultDigit, NewCarry),
    multiply_list(T, Multiplier, NewCarry, Result).

% Predicate to reverse a list
reverse_list(List, Reversed) :-
    reverse_list(List, [], Reversed).

reverse_list([], Acc, Acc).
reverse_list([H|T], Acc, Reversed) :-
    reverse_list(T, [H|Acc], Reversed).

% Predicate to find the position of the maximum element in a list
max_position(List, Position) :-
    max_position(List, 0, 0, -inf, Position).

max_position([], _, MaxPos, _, MaxPos).
max_position([H|T], CurrentPos, _, Max, Position) :-
    H > Max,
    NewPos is CurrentPos + 1,
    max_position(T, NewPos, CurrentPos, H, Position).
max_position([H|T], CurrentPos, MaxPos, Max, Position) :-
    H =< Max,
    NewPos is CurrentPos + 1,
    max_position(T, NewPos, MaxPos, Max, Position).

% Predicate to process a heterogeneous list
replace_sublists_with_max_position([], []).
replace_sublists_with_max_position([H|T], [MaxPos|Result]) :-
    is_list(H),
    max_position(H, MaxPos),
    replace_sublists_with_max_position(T, Result).
replace_sublists_with_max_position([H|T], [H|Result]) :-
    \+ is_list(H),
    replace_sublists_with_max_position(T, Result).


% Predicate to find the longest sequence of even numbers in a list
longest_even_sequence(List, LongestSeq) :-
    longest_even_sequence(List, [], [], LongestSeq).

% Base case: when the list is empty, the longest sequence is the current longest sequence
longest_even_sequence([], CurrentSeq, LongestSeq, LongestSeq) :-
    length(CurrentSeq, CurrentLen),
    length(LongestSeq, LongestLen),
    CurrentLen =< LongestLen, !.
longest_even_sequence([], CurrentSeq, _, CurrentSeq).

% If the head is even, add it to the current sequence
longest_even_sequence([H|T], CurrentSeq, LongestSeq, Result) :-
    H mod 2 =:= 0,
    append(CurrentSeq, [H], NewCurrentSeq),
    longest_even_sequence(T, NewCurrentSeq, LongestSeq, Result).

% If the head is not even, compare the current sequence with the longest sequence and reset the current sequence
longest_even_sequence([H|T], CurrentSeq, LongestSeq, Result) :-
    H mod 2 =\= 0,
    length(CurrentSeq, CurrentLen),
    length(LongestSeq, LongestLen),
    (CurrentLen > LongestLen -> NewLongestSeq = CurrentSeq ; NewLongestSeq = LongestSeq),
    longest_even_sequence(T, [], NewLongestSeq, Result).

% Predicate to process a heterogeneous list
replace_sublists_with_longest_even_sequence([], []).
replace_sublists_with_longest_even_sequence([H|T], [ProcessedH|Result]) :-
    is_list(H),
    longest_even_sequence(H, ProcessedH),
    replace_sublists_with_longest_even_sequence(T, Result).
replace_sublists_with_longest_even_sequence([H|T], [H|Result]) :-
    \+ is_list(H),
    replace_sublists_with_longest_even_sequence(T, Result).



% Predicate to select an element from a list
select_elem(X, [X|T], T).
select_elem(X, [H|T], [H|R]) :-
    select_elem(X, T, R).

% Predicate to generate permutations of a list
permute([], []).
permute(List, [H|Perm]) :-
    select_elem(H, List, Rest),
    permute(Rest, Perm).

% Predicate to check if two numbers are consecutive
consecutive(X, Y) :-
    Y is X + 1;
    Y is X - 1.

% Predicate to remove sequences of consecutive values from a list
remove_consecutive([], []).
remove_consecutive([X], [X]).
remove_consecutive([X, Y | T], Result) :-
    consecutive(X, Y),
    skip_consecutive([Y | T], Rest),
    remove_consecutive(Rest, Result).
remove_consecutive([X, Y | T], [X | Result]) :-
    \+ consecutive(X, Y),
    remove_consecutive([Y | T], Result).

% Helper predicate to skip consecutive values
skip_consecutive([X, Y | T], Rest) :-
    consecutive(X, Y),
    skip_consecutive([Y | T], Rest).
skip_consecutive([X | T], [X | T]) :-
    \+ consecutive(X, _).

% Predicate to process a heterogeneous list
remove_consecutive_from_sublists([], []).
remove_consecutive_from_sublists([H | T], [ProcessedH | Result]) :-
    is_list(H),
    remove_consecutive(H, ProcessedH),
    remove_consecutive_from_sublists(T, Result).
remove_consecutive_from_sublists([H | T], [H | Result]) :-
    \+ is_list(H),
    remove_consecutive_from_sublists(T, Result).


% Helper predicate to check if a number is prime
is_prime(2) :- !.
is_prime(N) :-
    N > 2,
    \+ has_divisor(N, 2).

% Helper predicate to check if a number has a divisor other than 1 and itself
has_divisor(N, D) :-
    D * D =< N,
    (N mod D =:= 0 ; D1 is D + 1, has_divisor(N, D1)).

% Predicate to duplicate prime numbers in a list
duplicate_primes([], []).
duplicate_primes([H|T], [H, H|Result]) :-
    is_prime(H),
    duplicate_primes(T, Result).
duplicate_primes([H|T], [H|Result]) :-
    \+ is_prime(H),
    duplicate_primes(T, Result).

% Predicate to process a heterogeneous list
duplicate_primes_in_sublists([], []).
duplicate_primes_in_sublists([H|T], [ProcessedH|Result]) :-
    is_list(H),
    duplicate_primes(H, ProcessedH),
    duplicate_primes_in_sublists(T, Result).
duplicate_primes_in_sublists([H|T], [H|Result]) :-
    \+ is_list(H),
    duplicate_primes_in_sublists(T, Result).


% Predicate to insert a value after specified positions in a list
insert_after_positions(List, Value, Positions, Result) :-
    insert_after_positions(List, Value, Positions, 1, Result).

insert_after_positions([], _, _, _, []).
insert_after_positions([H|T], Value, Positions, Index, [H, Value|Result]) :-
    member(Index, Positions),
    NextIndex is Index + 1,
    insert_after_positions(T, Value, Positions, NextIndex, Result).
insert_after_positions([H|T], Value, Positions, Index, [H|Result]) :-
    \+ member(Index, Positions),
    NextIndex is Index + 1,
    insert_after_positions(T, Value, Positions, NextIndex, Result).

% Predicate to process a heterogeneous list
process_heterogeneous_list([], _, []).
process_heterogeneous_list([H|T], _, [H|Result]) :-
    \+ is_list(H),
    process_heterogeneous_list(T, H, Result).
process_heterogeneous_list([H|T], PrevValue, [ProcessedH|Result]) :-
    is_list(H),
    insert_after_positions(H, PrevValue, [1, 3, 7, 15], ProcessedH),
    process_heterogeneous_list(T, PrevValue, Result).
