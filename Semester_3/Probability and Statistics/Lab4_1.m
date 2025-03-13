% Standard matlab library
% rand, randn => random generator functions
% rand => random uniform distributions/probabilities U(0, 1)
% randn => random normal distribution N(0, 1)

% Probability and statistics library
% rnd(param of the model, size of the matrix)
% unifrnd(0, 1, 2, 3) - uniformly distributed numbers between 0 and 1
% arranged in a 2*3 matrix
% binornd(5 trials, 0.5 p of success, 2, 3)

% if we want S simulations with N trials, we generate a random N*S matrix
% (simulations on columns and trials on rows)
% U < p = ... 
% X = number of successes = sum(U < p) 
% Let X Bern(p)
% Let U in (0, 1), - cont
% cdf(k) = Fu (k) = { 0, if k < 0
%                      k, if 0 <= k < 1
%                      1, k >= 1
% X = {1, if U < p
%       0, U >= p}
% We want to prove that X is Bern(p)
% P(success) = P( X = 1) = P (U < p) = P (U <= p) = Fu(p) = p, p in (0, 1)

% Bernoulli distribution
clear all;
clc;
pause(0.2);

p = -1;
while p < 0 | p > 1
    p = input("probability for success = ");
end

S = input("numb. of simulations = ");
U = rand(1, S);
X = U < p;

% Count the number of occurences of a particular state
U_X=unique(X); % extracts the number of unique values in the vector
n_X = hist(X, length(U_X));
rel_freq = n_X/S;

[U_X; rel_freq]