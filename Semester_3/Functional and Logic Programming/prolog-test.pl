% 1. Definiti un predicat care creeaza dintr-o lista de numere o lista de frecvente de aparitii ale unui numar definite ca perechi nr-frecventa
% Ex. [11, 22, 11, 22, 11, 33, 11] => [{11, 4}, {22, 2}, {33, 1}]
% is_list, atomic, number

% Nr of appearances
% Model matematic:
% appearances(l1, l2, ..., ln, nr, rez) = { rez, n = 0
%                                           appearances(l2, ..., ln, nr, rez + 1), l1 = nr
%                                           appearances(l2, ..., ln, nr, rez), l1 != nr }

appearances([], _, 0).
appearances([H|T], Nr, R) :-
    H =:= Nr,
    appearances(T, Nr, R1),
    R is R1 + 1.
appearances([H|T], Nr, R) :-
    H =\= Nr,
    appearances(T, Nr, R).


