clc
clear all

% point b

n=3
p=0.5

x=0:3

fx = binopdf(x, n, p);
X = [0:3, fx];

x2 = 0:0.01:3;
gx = binocdf(x2, n, p);
plot(x2, p);

title("Ex 2");

% point c
fprintf("c)\nP(x=0)=%.3f\n", binopdf(0, n, p));
fprintf("P(X != 1) = %.3f\n", 1 - binopdf(1, n, p));

% point d
fprintf("d)\n P(X <= 2) = %.3f\n", binocdf(2, n, p));
fprintf("P(X < 2) = %.3f\n", binocdf(2, n, p) - binopdf(2, n, p));

% point e
fprintf("e)\nP(X >= 1) = %.3\n", 1 - (binocdf(1, n, p) - binopdf(1, n, p)));
fprintf("P(X > 1) = %.3f\n", 1 - binocdf(1, n, p));