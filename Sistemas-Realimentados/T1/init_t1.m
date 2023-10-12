function [Y,G1,G2] = init_t1(I)
load dadost1.mat
n=J(I);
Y(1).y=Y1(n).dat;Y(1).t=Y1(n).T;
Y(2).y=Y2(n).dat;Y(2).t=Y2(n).T;
Y(3).y=Y3(n).dat;Y(3).t=Y3(n).T;
G1=G1f(n).g;
G2=G2f(n).g;
end

