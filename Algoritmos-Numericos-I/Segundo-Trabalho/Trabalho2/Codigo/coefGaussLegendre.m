%%
%% Calculando recursivamente os coeficientes dos polinômios de Gauss-Legendre
%% Input: Grau máximo 'nmax'
%% Output: Todos os coeficientes de todos os polinômios de zero até grau nmax (i.e. nmax+1 conjuntos)
%
function C = coefGaussLegendre( nmax )
	% A linha n da matriz contém os coeficientes do polinômio L_n(x)
	% L_n(x) = a_0,n + a_1,n x + a_2,n x^2 + ... + a_n,n x^n 
	% (descontar 1 em cada índice da matriz, pois não permite comecar a contagem em 0
	C = zeros(nmax+1,nmax+1);
	C(1,1) = 1.0;	% a_0 de L_0(x)
	if nmax > 0
		C(2,2) = 1.0;	% a_1 de L_1(x)	( a_0 é 0, pois L_1(x) = 0 + 1 * x )
	end
	for n = 2:nmax
		aux1 = (1.0-n)/n;
		aux2 = (2*n-1.0)/n;

		C(n+1,1) = aux1 * C(n-1,1);
		for j = 2:n-1
			C(n+1,j) = aux1 * C(n-1,j) + aux2 * C(n,j-1); 
		end

		C(n+1,n) = aux2 * C(n,n-1);
		C(n+1,n+1) = aux2 * C(n,n); 
	end
end

