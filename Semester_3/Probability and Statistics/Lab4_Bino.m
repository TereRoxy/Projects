% Binomial distribution
clear all;
clc;
pause(0.2);

p = -1;
while p < 0 || p > 1
    p = input("probability for success = ");
end

S = input("numb. of simulations = ");
n = input("numb. of trials = ");
U = rand(n, S);
X = sum(U < p);

% Count the number of occurences of a particular state
U_X=unique(X); % extracts the number of unique values in the vector
n_X = hist(X, length(U_X));
rel_freq = n_X/S;

% plot the binomial model
plot(0:n, binopdf(0:n, n, p), 'o');
hold on;
plot(U_X, rel_freq, 'x');
hold off;
legend("Binopdf", "Simulation");