% point a

n = input("number of trials=");
p = input("prob. of success=");

k=0:n;
px=binopdf(k,n,p);

kreal=0:0.01:n;
fx=binocdf(kreal, n, p);


plot(k, px, '*');
hold on;
plot(kreal, fx);
hold off;
title("The Binomial Model");
legend("pdf", "cdf");