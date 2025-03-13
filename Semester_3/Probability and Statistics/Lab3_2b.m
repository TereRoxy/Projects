clear all;
clc;
pause(0.2);


p = 1;
while p > 0.05
    p = input("prob. of success (p<=0.05 = ");
end

for n=30:40

    k = 0:n;
    px = binopdf(k, n, p);
    plot(k, px, 'x');
    hold on;
    
    kreal=0:n;
    lambda = n*p;
    poissp = poisspdf(kreal, lambda);
    plot(kreal, poissp);
    
    hold off;

    title("The approx. of the Binomial Distr. Model with the Poisson Distr. Model");
    legend("bino", "poiss");

    pause(0.5);
end