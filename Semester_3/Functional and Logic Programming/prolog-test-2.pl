% 2. Definiti un predicat ce intercaleaza 2 liste sortate de nr intregi si elimina valorile duplicate.
% Ex. [1, 2, 3, 5, 7], [2, 4, 6, 8] => [1, 2, 3, 4, 5, 6, 7, 8]

% Stergere duplicate
remove_duplicates([], []).
remove_duplicates([H], [H]).
remove_duplicates([H1, H2|T], [H1|Result]) :-
    H1 =:= H2,
    remove_duplicates([H2|T], Result).
remove_duplicates([H1, H2|T], [H1|Result]) :-
    H1 \= H2,
    remove_duplicates([H2|T], Result).


merge_sorted([], [], []).
merge_sorted([], [H|T], [H|T]).
merge_sorted([H|T], [], [H|T]).
merge_sorted([H1|T1], [H2|T2], [H1|Result]) :-
    H1 < H2,
    merge_sorted(T1, [H2|T2], Result).
merge_sorted([H1|T1], [H2|T2], [H2|Result]) :-
    H1 > H2,
    merge_sorted([H1|T1], T2, Result).
merge_sorted([H|T1], [H|T2], [H|Result]) :-
    merge_sorted(T1, T2, Result).


% Model matematic
% remove_duplicates(l1, l2, ..., ln, rez) = { [], n = 0
%                                             remove_duplicates(l2, ..., ln, rez), l1 = l2
%                                             l1 + remove_duplicates(l2, ..., ln, rez), l1 != l2 }

% Interclasare si eliminare duplicate
% Model matematic:
% merge_sorted(l1, l2, ..., ln,   m1, m2, ..., mn, rez) = { [], n = 0
%                                                           merge_sorted([], l2, ..., ln, m2, ..., mn, rez), m1 = m2
%                                                           merge_sorted(l1, ..., ln, [], m2, ..., mn, rez), m1 > m2
%                                                           m1 + merge_sorted(l2, ..., ln, m2, ..., mn, rez), m1 < m2 }

merge_and_remove_duplicates(List1, List2, Result) :-        
    merge_sorted(List1, List2, Merged),
    remove_duplicates(Merged, Result).
    
