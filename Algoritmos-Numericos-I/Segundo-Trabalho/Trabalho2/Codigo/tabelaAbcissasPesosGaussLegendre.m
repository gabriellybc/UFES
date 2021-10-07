%%
%% Monta a tabela de abcissas t e pesos A para quadratura de Gauss-Legendre
%%
%% Input:   Coeficientes de Gauss-Legendre C
%% Output:  Tabela de Gauss-Legendre A
%%
function [T, A] = tabelaAbcissasPesosGaussLegendre( C )
	nmax = size(C,1)-1;
	if nmax == 0
		T = []; A = [];
		return;
	end
	T = zeros(nmax,nmax); A = zeros(nmax,nmax);
	for n = 1:nmax
		%fprintf('\n =====  n=%d ========\n',n);
		t = sort( roots( fliplr( C(n+1,1:n+1) ) ) );
		T(n,1:n) = t';
		T(n,n+1:nmax) = NaN; % preencher com valor 'vazio'
		% Temos o vetor das abcissas para o polinômio de grau n: [t1,...tn]
		% Montar a matrix das potências de [t1,...tn]
		M = ones(n,n);
		b = bcoefLegendre( n )';
		tpot = ones(1,n);
		for i = 2:n
			tpot = t.^(i-1);
			M(i,:) = tpot'; 
		end
		A(n,1:n) = (M\b)';
		A(n,n+1:nmax) = NaN; % preencher com valor 'vazio'
	end
end

