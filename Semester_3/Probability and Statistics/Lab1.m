A = [1 0 -2; 2 1 3; 0 1 0];
B = [2 1 1; 1 0 -1; 1 1 0];
C =  A - B;
D = A * B;
E = A.*B;

x = 0:0.01:3;
y1 = x.^5/10;
y2 = x.*sin(x);
y3 = cos(x);

plot(x, y1, 'r--');
hold on;
plot(x, y2, 'm');
plot(x, y3, 'b');
hold off;

title("Exercise 2");
legend("x^5/10", "xsin(x), cos(x)");

%subplot() to plot each function on a different graph