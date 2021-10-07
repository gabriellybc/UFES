%%
%% Monta o vetor dos coeficientes constantes b necessário para resolver sistema
%% linear: -1 integral 1 (t^k dt) = { 0 se k impar, 2/(k+1) se k for impar }
%%
%% Input: Coeficientes de Gauss-Legendre
%% Output: A tabela de Gauss-Legendre
%%
%%
function b = bcoefLegendre( nmax )
	%% Decide se número é impar: Uso de uma função 'inline' (uma linha)
	isodd=inline('x-2*floor(x/2)','x');

	b = zeros(1,nmax);
	for n = 1:nmax
		if ~isodd(n-1)
			b(1, n) = 2.0 / (n-1+1);
		end
	end
end

