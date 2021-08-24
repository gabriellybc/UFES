function [X,Y] = EulerMelhorado(f, x0, y0, h, n )
		X = zeros(1,n+1); Y = zeros(1,n+1);
		if nargin(f) ~= 2
			fprintf('Euler Melhorado: Erro: lado direito tem que ter dois argumentos: f(x,y)\n');
			return;
		end
		x = x0; y = y0;
		X(1) = x; Y(1) = y;
		for i=2:n+1
			if 0
				fprintf('Euler Mel.: (x_%d,y_%d)=f(%f,%f)=%f  f(x+h,y+h*f(x,y))=f(%f,%f)=%f y(%d)=%f\n',...
					i-2, i-2, x,y,f(x,y), x+h,y+h*f(x,y),f(x+h,y+h*f(x,y)), i-1, y + 0.5*h*( f(x,y) + f(x+h,y+h*f(x,y)) ) );
			end
			y = y + 0.5*h*( f(x,y) + f(x+h,y+h*f(x,y)) );
			x = x + h;
			X(i) = x; Y(i) = y;
		end
end	
