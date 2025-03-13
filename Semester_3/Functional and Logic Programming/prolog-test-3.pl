% 3. Definiti un predicat ce returneaza o lista continand toate pozitiile pe care apare elem min intr-o alta lista de nr intregi.
% Ex. [10, -14, 12, 13, -14] => [2, 5]

min_number([], Min, Min).
min_number([H|T], Min, R) :- 
    H < Min, 
    min_number(T, H, R).
min_number([H|T], Min, R) :- 
    H >= Min, 
    min_number(T, Min, R).

min_positions([], _, _, []).
min_positions([H|T], Min, Poz, [Poz|Res]) :-
    H=:=Min,
    Poz1 is Poz + 1,
    min_positions(T, Min, Poz1, Res).
min_positions([H|T], Min, Poz, Res) :-
    H=\=Min,
    Poz1 is Poz + 1,
    min_positions(T, Min, Poz1, Res).


% Main predicate
% Flow model: (i, o)
% Model matematic:

% Gasire elem minim
% Model matematic:
% min_number(l1, l2, ..., ln, min) = { min, n = 0
%                                   min_number(l2, ..., ln, l1), l1 < min }
%                                   min_number(l2, ..., ln, min), l1 >= min }

% Pozitii elem min
% Model matematic:
% min_positions(l1, l2, ..., ln, min, poz, rez) = { rez, n = 0
%                                                  min_positions(l2, ..., ln, min, poz + 1, rez), l1 != min
%                                                  min_positions(l2, ..., ln, min, poz + 1, rez + poz), l1 = min }


min_positions_main(L, R) :-
    min_number(L, 9999, Min),
    min_positions(L, Min, 1, R).