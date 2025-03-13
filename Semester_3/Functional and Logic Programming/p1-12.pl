% a. Write a predicate to substitute in a list a value with all the elements of another list.
% b. Remove the n-th element of a list.

% a

% Mathematical model:
% sub(O, N, l1...ln) = {
%   [], n = 0
%   N + sub(O, N, l2...ln), l1 = O
%   l1 + sub(O, N, l2...ln), l1 != O
% }
% sub(O, N, L:list, R:list)
% flow model (i, i, i, o)

my_append([], L, L).
my_append([H|T], L, [H|R]) :-
    my_append(T, L, R).

sub(_, _, [], []).
sub(O, N, [O|T], Res) :-
    sub(O, N, T, Res1),
    my_append(N, Res1, Res).
sub(O, N, [H|T], [H|Res]) :-
    H \= O,
    sub(O, N, T, Res).

% Example: sub(1, [a, b], [1, 2, 3], Res).


% b

% Mathematical model:
% rmv(N, l1...ln) = {
%   [], n = 0
%   l2...ln, N = 1
%   l1 + rmv(N-1, l2...ln), N > 1
% }
% rmv(N:number, L:list, R:list)
% flow model (i, i, o)
rmv(0, [_|T], T).
rmv(N, [H|T], [H|Res]) :-
    N > 0,
    N1 is N - 1,
    rmv(N1, T, Res).
% Example: rmv(2, [1, 2, 3], Res).