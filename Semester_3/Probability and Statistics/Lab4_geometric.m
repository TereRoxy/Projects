% Binomial distribution
clear all;
clc;
pause(0.2);

p = -1;
while p < 0 || p > 1
    p = input("probability for success = ");
end

S = input("numb. of simulations = ");
X = zeros(1, S);

for i=1:S
    % the i-th simulation
    % X(i) = number of failures before the 1st success during the i-th
    % simulation
    while rand>=p %while we have a failure
        X(i) = X(i) + 1;
    end
end

% Count the number of occurences of a particular state
U_X=unique(X); % extracts the number of unique values in the vector
n_X = hist(X, length(U_X));
rel_freq = n_X/S;

% plot the binomial model
plot(0:max(U_X), geopdf(0:max(U_X), p), 'o');
hold on;
plot(U_X, rel_freq, 'x');
hold off;
legend("Geopdf", "Simulation");