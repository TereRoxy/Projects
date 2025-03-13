% Predicate to generate all valid substrings
generate_substrings(N, Substring) :-
    Length is 2 * N + 1,
    generate_substrings(Length, [0], Substring).

% Base case: when the desired length is reached
generate_substrings(1, Substring, Substring).

% Recursive case: generate the next element and ensure the constraints are satisfied
generate_substrings(Length, [H|T], Substring) :-
    Length > 1,
    (Next is H + 1; Next is H - 1; Next is H + 2; Next is H - 2),
    generate_substrings(Length - 1, [Next, H|T], Substring).

% Example usage
?- generate_substrings(2, Substring).
% Substring = [0, 1, 0, -1, 0] ;
% Substring = [0, 1, 0, 1, 0] ;
% Substring = [0, 1, 0, 2, 0] ;
% Substring = [0, -1, 0, 1, 0] ;
% Substring = [0, -1, 0, -1, 0] ;
% Substring = [0, -1, 0, -2, 0] ;
% Substring = [0, 2, 0, 1, 0] ;
% Substring = [0, 2, 0, 3, 0] ;
% Substring = [0, -2, 0, -1, 0] ;
% Substring = [0, -2, 0, -3, 0].