n=3;
p=0.5;
S=input("number of simulation=");

U=rand(n, S);
U = U < 0.5;

X=sum(U);

c=hist(X,n+1)/S