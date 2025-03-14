clear all;
clc;
pause(0.2);


p = 0;
while p < 0.05 | p > 0.95
    p=input("prob. of success (0.05 <= p <= 0.95)=");
end

for n=1:5:100
    mu = n*p;
    sigma = sqrt(n*p*(1-p));

    k = 0:n;
    px = binopdf(k, n, p);
    plot(k, px, 'x');
    hold on;

    kreal=0:0.01:n;
    normpx=normpdf(kreal, mu, sigma);
    plot(kreal, normpx);
    hold off;

    title("The approx. of the Binomial Distr. Model with the Normal Distr. Model");
    legend("bino", "norm");

    pause(0.5);
end