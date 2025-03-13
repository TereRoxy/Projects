% recap
% bernoulli model -> bern
% binomial -> bino


% Continuous models
% normal -> norm
% student(t) -> t
% chi^2 -> chi2
% Fisher -> f
% Poisson -> poiss

% cdf(k) = P(x<=k) = integral(pdf(t)dt) |(-inf) k

% ex 1
% a) cdf(0), 1-P(x<0) = 1-cdf(0)
% b) cdf(1) - cdf(-1), 1 - P(-1 < x < 1)
% d) P(x >= x beta) = beta <=> 1 - P(x < x beta) <=> P(x <= x beta) = 1 -
% beta

clear all;
clc;
pause(0.5);

option = input("Distr. model (Normal, Student, Chi2, Fisher)", "s");
alpha = input("alpha = "); % 0.2
beta = input("beta = "); %0.2

switch option
    case 'Normal'
        fprintf("Normal distribution model\n");
        mu = input("mu= "); %1
        sigma = input("sigma= "); %0.5
        result = normcdf(0, mu, sigma);
        fprintf("a)\nP(x<=0)=%f\n", result); % 0.02275
        fprintf("P(x>=0)=%f\n", 1-result); % 0.97725
        fprintf("b) P(-1<=x<=1)=%f\n", normcdf(1, mu, sigma)-normcdf(-1, mu, sigma));
        fprintf("c) P(x < x alpha) = P(x <= x alpha) = alpha \n x alpha = %f\n", norminv(alpha, mu, sigma));
        fprintf("d) P(x > x beta) = beta \n x beta = %f\n", norminv(1-beta, mu, sigma));
    case 'Student'
        fprintf("Student distribution model\n");
        n = input("n= ");
        result = tcdf(0,n);
        fprintf("a)\nP(x<=0)=%f\n", result);
        fprintf("P(x>=0)=%f\n", 1-result);
    case 'Chi2'
        fprintf("Chi2 distribution model\n");
        n = input("n= ");
        result = chi2cdf(0, n);
        fprintf("a)\nP(x<=0)=%f\n", result);
        fprintf("P(x>=0)=%f\n", 1-result);
    case 'Fisher'
        fprintf("Fisher distribution model\n");
        m = input("m= ");
        n = input("n= ");
        result = fishercdf(0, m, n);
        fprintf("a)\nP(x<=0)=%f\n", result);
        fprintf("P(x>=0)=%f\n", 1-result);
    otherwise
        fprintf("Wrong option!\n");
end

% inv -> quantile of order alpha P(x<=? = alpha)