%%
%% Integração numérica usando a regra dos Trapézios repetida
%%
%% Input: a função a ser integrada, os limites inferior 'a' e superior 'b' de integração
%%        o número 'n' de subdivisões. Variável lógica, se solução deve ser explicada
%% 
%% Output: Integral numérica
%%
function ITR = integralTrapeziosRepetidaFunc( func, a, b, n, verbose )

	if mod(n,1) ~= 0
		error('Quantidade de nos ''n'' tem que ser inteiro');
	end

	if verbose
		fprintf('Integracao pela Regra dos Trapezios ');
		if n >=2 fprintf('repetida '), end;
		fprintf('no intervalo [%.2e,%.2e] com %d nos (%d subdivisoes)\n', a, b, n+1, n );
	end
	h = (b-a)/n;
	nos = a:h:b;


	limits = func(a) + func(b);
	x = a + h;
	ITR = 0.0;
	for i=1:n-1
		ITR = ITR + func(x);
		x = x + h;
	end
	ITR = h/2 * (limits + 2 * ITR);

	if ~verbose
		return;
	end
	% Explicitação didática
	fprintf('I_TR%d = h/2[ f(x0)+f(x%d)', n, n );
	if n>1 fprintf(' + 2{ '); end
	for i=1:n-1
		fprintf('f(x%d)', i ); if i==n-1 fprintf(' }'); else fprintf('+'); end;
	end
	fprintf(' ]\n    = %.2f/2[ f(%.2f)+f(%.2f)', h, a, b );
	if n>1 fprintf(' + 2{ '); end
	for i=1:n-1
		fprintf('f(%.2f)', a+h*i ); if i==n-1 fprintf(' }'); else fprintf('+'); end;
	end
	fprintf(' ]\n    = %.3f[ %.3f+%.3f', h/2, func(a), func(b) );
	if n>1 fprintf(' + 2{ '); end
	for i=1:n-1
		fprintf('%.3f', func(a+h*i) ); if i==n-1 fprintf(' }'); else fprintf('+'); end;
	end
	fprintf(' ]\n = ', ITR);
  	printdecandfrac( ITR, true );
end

