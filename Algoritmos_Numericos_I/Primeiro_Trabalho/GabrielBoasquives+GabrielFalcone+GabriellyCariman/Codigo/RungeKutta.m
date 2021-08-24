%
% Runge-Kutta methods
% https://en.wikipedia.org/wiki/List_of_Runge%E2%80%93Kutta_methods
%
% Genereal purpose method which uses the Butcher tableau
% https://en.wikipedia.org/wiki/Runge%E2%80%93Kutta_methods#Explicit_Runge.E2.80.93Kutta_methods
%
%
function [T, Y, YLow] = RungeKutta(f, x0, y0, h, n, butcher, s )
    if nargin(f) ~= 2
    	fprintf('RungeKutta: Erro: lado direito tem que ter dois argumentos: f(x,y)\n');
    	return;
    end

% Y are the estimated y values.
% If method is embedded, Ylow are the lower order estimates
    isEmbedded = butcher.isEmbedded;
    c = butcher.c;
    b = butcher.b;
    if isEmbedded
        bstar = butcher.bstar;
    end
    a = butcher.a;
    
    T = linspace(x0,x0+n*h,n+1);
    k = zeros(1,s);
    Y = zeros(1,n+1);
    YLow = zeros(1,n+1);
    Y(1) = y0; YLow(1) = y0;
    for p=2:n+1
        t = T(p-1);
        y = Y(p-1);
                        
        k(1) = f(t,y);
        sumi = 0.0; sumiLowOrder = 0.0;
        for i=1:s
            sumj = 0.0;
            for j=1:s	% Must be 's', not 's-1' to include implicit methods
                sumj = sumj + a(i,j)*k(j);
            end
            k(i) = f( t+c(i)*h, y+h*sumj );
            sumi = sumi + b(i)*k(i);
            if isEmbedded
                sumiLowOrder = sumiLowOrder + bstar(i)*k(i);
            end            
        end
        Y(p) = y + h * sumi;
        if isEmbedded
		YLow(p) = y + h * sumiLowOrder;
	end;
    end
end	
