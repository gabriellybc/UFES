%%=========================================================%%
%% Determinação de raiz de função: Bissecção e Posição Falsa
%% R.-L. p. 41 e p. 47
%% Autor: Thomas W. Rauber trauber@gmail.com , 2008 a 2012
%%
%% Input:
%%		1)	Variável lógica 'posfalsa'. Se for verdadeira,
%%			use Posição Falsa, caso contrário, use Bissecção
%%		2)	Função de qual se quer obter (um)a raiz
%%		3)	Intervalo inicial [a,b]
%%		4)	Precisão de aproximação. Se for atingida, pare a execução
%%		5)	Número máximo de iterações
%%
%% Output:
%%		1)	raiz
%%
%%=========================================================

function r = raizBisecPosFalsa( posfalsa, func, a, b, eps, maxiter )
	if posfalsa
		fprintf('Determinacao de raiz pelo metodo de Posicao Falsa no intervalo [%.2f,%.2f]\n',a,b);
	else
		fprintf('Determinacao de raiz pelo metodo da Bisseccao no intervalo [%.2f,%.2f]\n',a,b);
	end
	fprintf('Eps = %e  --- Numero maximo de iteracoes = %d\n', eps, maxiter );
	fa = func(a);
	fb = func(b);
	trocaSinal = fa * fb < 0.0;
	fprintf('Valor da funcao no limite inferior = %f\n', fa );
	fprintf('Valor da funcao no limite superior = %f\n', fb );
	if trocaSinal
		fprintf('Ha troca de sinal, entao tem raiz.\n');
	else
		fprintf('Nao ha troca de sinal, talvez tenha raiz. ');
		fprintf('Nao posso aplicar biseccao. Saindo...\n'); r = -Inf;
		return;
	end

	k = 0; d = eps + 1; fx = fa;
	while k < maxiter && d > eps && abs(fx) > eps
		if ~posfalsa
			x = (a+b) / 2.0;			%%% BISSECÇÂO
		else
			x = (a*fb - b*fa) / (fb - fa);		%%% POSIÇÂO FALSA
		end
		fx = func(x);
		d = b-a;
		%fprintf('Iter=%3d  a(%3d)=%11.7f  b(%3d)=%11.7f  dist=%11.7e  x(%3d)=%11.7f  f(a)=%11.7f  f(b)=%11.7f  f(x)=%11.7f ==> ',...
		%					k+1, k, a, k,b, d, k,x, fa, fb, fx );
		%wait();
		if fa * fx < 0.0  % Troca de sinal acontece no subintervalo esquerdo
			b = x;
			%fprintf('a(%3d)=a(%3d)=%11.7f b(%3d)=x(%3d)=%11.7f\n',k+1,k,a,k+1,k,b);
			fb = fx;
		else
			a = x;
			%fprintf('a(%3d)=x(%3d)=%11.7f b(%3d)=b(%3d)=%11.7f\n',k+1,k,a,k+1,k,b);
			fa = fx;
		end
		k = k + 1;
	end
	r = x;


	fprintf('Razao(oes) de parada apos %d iteracoes:\n', k);
	if k >= maxiter , fprintf('\t\tNumero maximo de iteracoes %d atingido\n', k); end;
	if d <= eps , fprintf('\t\tDistancia %e menor ou igual que limite %e apos %d iteracoes\n', d, eps, k ); end;
	if abs(fx) <= eps, fprintf('\t\tValor absoluto da funcao %e pequeno\n', abs(fx)); end;
	if (abs(x) == Inf || abs(x) == -Inf), fprintf('\t\tDivergencia\n', x ); end;
	if fx == 0.0 , fprintf('\t\tValor zero da funcao em x=%.20e\n', x ); end;

	fprintf('Raiz calculada=%.20e  --- Verificando: f(raiz)=%.20e\n', r, fx );
end


