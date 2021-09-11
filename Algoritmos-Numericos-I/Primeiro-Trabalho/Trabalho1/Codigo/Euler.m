function [X, Y] = Euler(f, x0, y0, h, n )
	%%%
	%%% Aproximação de EDO por método de Euler
	%%%
	%%% f       Lado direito de equação diferencial, exemplo: f = @(x,y) x.*log(x)
	%%% x0      Valor inicial no eixo x
	%%% y0      Valor inicial no eixo y0
	%%% h       Passo: x_n+1 = x_n + h
	%%% n       Quantidade de passos andados
	%%%
	X = zeros(1,n+1); Y = zeros(1,n+1);
	if nargin(f) ~= 2
		error('Euler: Erro: lado direito tem que ter dois argumentos: f(x,y), mas tem %d argumentos\n', nargin(f));
	end
	x = x0; y = y0;
	X(1) = x; Y(1) = y;
	for i=2:n+1
		if 0
			f
			fprintf('Euler: f(x_%d,y_%d)=f(%f,%f)=%f  y(%d)=%f\n',...
					i-2, i-2, x,y,f(x,y), i-1, y+h*f(x,y) );
			printf("y=%f h=%f f(x,y)=%f\n",y,h,f(x,y));
		end
		y = y + h*f(x,y);
		
		x = x + h;
		X(i) = x; Y(i) = y;
	end
end	

