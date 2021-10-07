%%
%% Integração numérica usando a regra 1/3 de Simpson repetida
%%
%% Input: a função a ser integrada, os limites inferior 'a' e superior 'b' de integração
%%        o número 'n' de subdivisões (=número de nós menos 1). 
%% 
%% Output: Integral numérica
%% Restrições: número 'n' de subdivisões tem que ser par
%%
function ISR = integralSimpsonRepetidaFunc( func, a, b, n, verbose  )

	%% Decide se número é impar: Uso de uma função anônima
	% http://www.mathworks.com/help/matlab/matlab_prog/anonymous-functions.html
	isodd = @(x) x-2*floor(x/2);

	if isodd( n )
		fprintf('Numero de subdivisoes n=%d. Tem que ser numero par !\n', n); % wait();
		ISR = NaN;
		return;
	end
	if verbose
		fprintf('Integracao pela Regra 1/3 de Simpson ');
		if n >=4 fprintf('repetida '), end;
		fprintf('no intervalo [%.2f,%.2f] com %d nos\n', a, b, n+1 );
	end
	h = (b-a)/n;
	nos = a:h:b;


	limits = func(a) + func(b);
	x = a + h;
	sumodd = 0.0; sumeven = 0.0;
	n2 = n/2; h2 = h*2;
	for i=1:n2
		sumodd = sumodd + func(x);
		x = x + h2;
	end
	x = a + h2;
	for i=1:n2-1
		sumeven = sumeven + func(x);
		x = x + h2;
	end
	ISR = h/3 * (limits + 4 * sumodd + 2 * sumeven);

    if ~verbose
      return;
    end
	% Explicitação didática
	fprintf('I_SR%d = h/3[ f(x0)+f(x%d) + 4{ ', n, n );
	for i=1:n2
		fprintf('f(x%d)', 2*i-1 ); if i==n2 fprintf(' }'); else fprintf('+'); end;
	end
	if n2 > 1 fprintf(' + 2{ '), end;
	for i=1:n2-1
		fprintf('f(x%d)', 2*i ); if i==n2-1 fprintf(' }'); else fprintf('+'); end;
	end
	fprintf(' ]\n');
	
	fprintf('       = %.2f/3[ f(%.2f)+f(%.2f) + 4{ ', h, a, b );
	for i=1:n2
		fprintf('f(%.2f)', a+h*(2*i-1) ); if i==n2 fprintf(' }'); else fprintf('+'); end;
	end
	if n2 > 1 fprintf(' + 2{ '), end;
	for i=1:n2-1
		fprintf('f(%.2f)', a+h*(2*i) ); if i==n2-1 fprintf(' }'); else fprintf('+'); end;
	end
	fprintf(' ]\n');
	
	fprintf('       = %.3f[ %.3f+%.3f + 4{ ', h/3, func(a), func(b) );
	for i=1:n2
		fprintf('%.3f', func(a+h*(2*i-1)) ); if i==n2 fprintf(' }'); else fprintf('+'); end;
	end
	if n2 > 1 fprintf(' + 2{ '), end;
	for i=1:n2-1
		fprintf('%.3f', func(a+h*(2*i)) ); if i==n2-1 fprintf(' }'); else fprintf('+'); end;
	end
	fprintf(' ] = %.10f\n', ISR);
	
	numcasas = 6;
	
	fprintf('       = %s [ %s + %s + 4{ ', dec2fracstr(h/3,numcasas),...
			dec2fracstr(func(a),numcasas),...
			dec2fracstr(func(b),numcasas) );
	for i=1:n2
		fprintf('%s', dec2fracstr( func(a+h*(2*i-1)), numcasas) ); if i==n2 fprintf(' }'); else fprintf('+'); end;
	end
	if n2 > 1 fprintf(' + 2{ '), end;
	for i=1:n2-1
		fprintf('%s', dec2fracstr(func(a+h*(2*i)), numcasas) ); if i==n2-1 fprintf(' }'); else fprintf('+'); end;
	end
	fprintf(' ] = '); printdecandfrac( ISR, true );
end

