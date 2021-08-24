function [X,Y] = EulerModificado(f, x0, y0, h, n )
		X = zeros(1,n+1); Y = zeros(1,n+1);
		if nargin(f) ~= 2
			fprintf('Euler Modificado: Erro: lado direito tem que ter dois argumentos: f(x,y)\n');
			return;
		end
		x = x0; y = y0;
		h2 = h/2.0;
		X(1) = x; Y(1) = y;
		for i=2:n+1
			%fprintf('Euler Mod.: f(x_%d,y_%d)=f(%f,%f)=%f  f(x+h/2,y+h/2*f(x,y)) = f(%f,%f)=%f y(%d)=%f\n',...
			%		i-2, i-2, x,y,f(x,y), x+h2, y+h2*f(x,y), f(x+h2, y+h2*f(x,y)), i-1, y+h*f(x+h2, y+h2*f(x,y)) );
			y = y + h*f(x+h2, y+h2*f(x,y));
			x = x + h;
			X(i) = x; Y(i) = y;
		end
end	
