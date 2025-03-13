% Binomial distribution
clear all;
clc;
pause(0.5);

p = -1;
while p < 0 || p > 1
    p = input("probability for success = ");
end

% number of failures before N successes
N = input("numb of successes needed = ");
S = input("numb. of simulations = ");
X = zeros(1, S);
C = zeros(1, S); % counter for the number of current successes

for i=1:S
    % the i-th simulation
    % X(i) = number of failures before the n-th success during the i-th
    % simulation
    while C(i) < N %while we have not reached N
        if (rand<=p) %if it's a failure
            X(i) = X(i) + 1;
        else
            C(i) = C(i) + 1;
        end
    end
end

% Count the number of occurences of a particular state
U_X=unique(X); % extracts the number of unique values in the vector
n_X = hist(X, length(U_X));
rel_freq = n_X/S;

% plot the binomial model
clf
plot(0:max(U_X), nbinpdf(0:max(U_X), N, p), 'o');
hold on;
plot(U_X, rel_freq, 'x');
hold off;
legend("Nbpdf", "Simulation");