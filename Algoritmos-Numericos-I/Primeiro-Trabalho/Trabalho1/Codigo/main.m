
clear all;
clc;

is_octave = (exist('OCTAVE_VERSION','builtin')>1); % Octave ou Matlab
if is_octave
	available_graphics_toolkits();
	graphics_toolkit gnuplot;
	%graphics_toolkit qt;

	pkg load symbolic;
	%
	% Se o pacote 'symbolic' do Octave ainda n„o estiver instalado, pegue aqui:
	% https://octave.sourceforge.io/download.php?package=symbolic-2.7.0.tar.gz
	% instale com o comando dentro do Octave: pkg install symbolic-2.7.0.tar.gz
	%
end

fprintf('\n----------- EquaÁoes Diferenciais Ordinarias ----------\n')

x0 = 0; y0 = 1; x03 = 1;

fprintf('\n----------- Tarefa 1: ----------\n')
fprintf('\n ------------ a) -------------\n')
[f1,sol1,PVIstr1,yx1] = solveEDO('y*log(x+1)',x0,y0)			%%% y(x) = 

fprintf('\n ----------- b) --------------\n')
[f2,sol2,PVIstr2,yx2] = solveEDO('y*(x^2-1)',x0,y0)			%%% y(x) = 

fprintf('\n ------------- c) ------------\n')
[f3,sol3,PVIstr3,yx3] = solveEDO('1-y/x',x03,y0)					%%% y(x) = 


% -------------------------------- Tarefa 3 ------------------------------------
h = 1/10; n = 10;
x = 0:h/10:1;  %para o PVI A e B
x2 = 1:h/10:2; %para o PVI C

% -------------------------------- Tarefa 4 ------------------------------------

%MÈtodos para A

[X_euler_a,Y_euler_a] = Euler(f1,x0,y0,h,n);

[X_eulermelhorado_a,Y_eulermelhorado_a] = EulerMelhorado(f1,x0,y0,h,n);

[X_eulermodificado_a,Y_eulermodificado_a] = EulerModificado(f1,x0,y0,h,n);

[X_FRK12_a,Y_FRK12_a] = FehlbergRK12(f1,x0,y0,h,n);

[X_FRK45_a,Y_FRK45_a] = FehlbergRK45(f1,x0,y0,h,n);

passofixo = true;
[X_Dormand_Prince_passoFixo_a, Y_Dormand_Prince_passoFixo_a] = RungeKutta_Dormand_Prince_ode45(f1, x0, y0, h, n, passofixo );

passofixo = false;
[X_Dormand_Prince_passoAdaptativo_a, Y_Dormand_Prince_passoAdaptativo_a] = RungeKutta_Dormand_Prince_ode45(f1, x0, y0, h, n, passofixo );


%MÈtodos para B

[X_euler_b,Y_euler_b] = Euler(f2,x0,y0,h,n);

[X_eulermelhorado_b,Y_eulermelhorado_b] = EulerMelhorado(f2,x0,y0,h,n);

[X_eulermodificado_b,Y_eulermodificado_b] = EulerModificado(f2,x0,y0,h,n);

[X_FRK12_b,Y_FRK12_b] = FehlbergRK12(f2,x0,y0,h,n);

[X_FRK45_b,Y_FRK45_b] = FehlbergRK45(f2,x0,y0,h,n);

passofixo = true;
[X_Dormand_Prince_passoFixo_b, Y_Dormand_Prince_passoFixo_b] = RungeKutta_Dormand_Prince_ode45(f2, x0, y0, h, n, passofixo );

passofixo = false;
[X_Dormand_Prince_passoAdaptativo_b, Y_Dormand_Prince_passoAdaptativo_b] = RungeKutta_Dormand_Prince_ode45(f2, x0, y0, h, n, passofixo );


%MÈtodos para C
[X_euler_c,Y_euler_c] = Euler(f3,x03,y0,h,n);

[X_eulermelhorado_c,Y_eulermelhorado_c] = EulerMelhorado(f3,x03,y0,h,n);

[X_eulermodificado_c,Y_eulermodificado_c] = EulerModificado(f3,x03,y0,h,n);

[X_FRK12_c,Y_FRK12_c] = FehlbergRK12(f3,x03,y0,h,n);

[X_FRK45_c,Y_FRK45_c] = FehlbergRK45(f3,x03,y0,h,n);

passofixo = true;
[X_Dormand_Prince_passoFixo_c, Y_Dormand_Prince_passoFixo_c] = RungeKutta_Dormand_Prince_ode45(f3, x03, y0, h, n, passofixo );

passofixo = false;
[X_Dormand_Prince_passoAdaptativo_c, Y_Dormand_Prince_passoAdaptativo_c] = RungeKutta_Dormand_Prince_ode45(f3, x03, y0, h, n, passofixo );


% -------------------------------- Tarefa 5 ------------------------------------

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%       T A B E L A      %%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% ------------------------------ Tarefa 7 e 8 ----------------------------------

% Gerando uma tabela
x = 0:h:1;
x2 = 1:h:2;
xadp = 1:0.05:2;

%Tabela A
fprintf('\n\n%10s\n\n',PVIstr1)
fprintf('FunÁ„o =  %10s\n\n',func2str(yx1))
fprintf('%10s | %10s | %10s | %10s | %10s | %10s | %10s | %10s\n', 'x', 'Valor Exato', 'Euler', 'Euler Mel.', 'Euler Mod.', 'Fehlb12', 'Fehlb45', 'ODE45 fixo' );
fprintf('=======================================================================================================\n');
for i=1:length(x)
	fprintf('%10.6f | %10.6f | %10.6f | %10.6f | %10.6f | %10.6f | %10.6f | %10.6f\n', x(i), yx1(x(i)) , Y_euler_a(i), Y_eulermelhorado_a(i), Y_eulermodificado_a(i), Y_FRK12_a(i), Y_FRK45_a(i), Y_Dormand_Prince_passoFixo_a(i));
end
%Tabela de Erros A
fprintf('\nErros:\n')
fprintf('=======================================================================================================\n');
for i=1:length(x)
	fprintf('%10.6f | %10.6f | %10.6e | %10.6e | %10.6e | %10.6e | %10.6e | %10.6e\n', x(i), yx1(x(i))-yx1(x(i)) , abs(Y_euler_a(i)-yx1(x(i))), abs(Y_eulermelhorado_a(i)-yx1(x(i))), abs(Y_eulermodificado_a(i)-yx1(x(i))), abs(Y_FRK12_a(i)-yx1(x(i))), abs(Y_FRK45_a(i)-yx1(x(i))), abs(Y_Dormand_Prince_passoFixo_a(i)-yx1(x(i))));
end


%Tabela B
fprintf('\n\n%10s\n\n',PVIstr2)
fprintf('FunÁ„o =  %10s\n\n',func2str(yx2))
fprintf('%10s | %10s | %10s | %10s | %10s | %10s | %10s | %10s\n', 'x', 'Valor Exato', 'Euler', 'Euler Mel.', 'Euler Mod.', 'Fehlb12', 'Fehlb45', 'ODE45 fixo' );
fprintf('=======================================================================================================\n');
for i=1:length(x)
	fprintf('%10.6f | %10.6f | %10.6f | %10.6f | %10.6f | %10.6f | %10.6f | %10.6f\n', x(i), yx2(x(i)) , Y_euler_b(i), Y_eulermelhorado_b(i), Y_eulermodificado_b(i), Y_FRK12_b(i), Y_FRK45_b(i), Y_Dormand_Prince_passoFixo_b(i));
end
%Tabela de Erros B
fprintf('\nErros:\n')
fprintf('=======================================================================================================\n');
for i=1:length(x)
	fprintf('%10.6f | %10.6f | %10.6e | %10.6e | %10.6e | %10.6e | %10.6e | %10.6e\n', x(i), yx2(x(i))-yx2(x(i)) , abs(Y_euler_b(i)-yx2(x(i))), abs(Y_eulermelhorado_b(i)-yx2(x(i))), abs(Y_eulermodificado_b(i)-yx2(x(i))), abs(Y_FRK12_b(i)-yx2(x(i))), abs(Y_FRK45_b(i)-yx2(x(i))), abs(Y_Dormand_Prince_passoFixo_b(i)-yx2(x(i))));
end


%Tabela C
fprintf('\n\n%10s\n\n',PVIstr3)
fprintf('FunÁ„o =  %10s\n\n',func2str(yx3))
fprintf('%10s | %10s | %10s | %10s | %10s | %10s | %10s | %10s\n', 'x', 'Valor Exato', 'Euler', 'Euler Mel.', 'Euler Mod.', 'Fehlb12', 'Fehlb45', 'ODE45 fixo' );
fprintf('=======================================================================================================\n');
for i=1:length(x2)
	fprintf('%10.6f | %10.6f | %10.6f | %10.6f | %10.6f | %10.6f | %10.6f | %10.6f\n', x2(i), yx3(x2(i)) , Y_euler_c(i), Y_eulermelhorado_c(i), Y_eulermodificado_c(i), Y_FRK12_c(i), Y_FRK45_c(i), Y_Dormand_Prince_passoFixo_c(i));
end
%Tabela de Erros c
fprintf('\nErros:\n')
fprintf('=======================================================================================================\n');
for i=1:length(x2)
	fprintf('%10.6f | %10.6f | %10.6e | %10.6e | %10.6e | %10.6e | %10.6e | %10.6e\n', x2(i), yx3(x2(i))-yx3(x2(i)) , abs(Y_euler_c(i)-yx3(x2(i))), abs(Y_eulermelhorado_c(i)-yx3(x2(i))), abs(Y_eulermodificado_c(i)-yx3(x2(i))), abs(Y_FRK12_c(i)-yx3(x2(i))), abs(Y_FRK45_c(i)-yx3(x2(i))), abs(Y_Dormand_Prince_passoFixo_c(i)-yx3(x2(i))));
end

warning('off', 'all');
%Gr·fico de A
xgraf = 1:length(x);

figure(1);
legenda = {};   % Inicializa c√©lula que cont√©m os r√≥tulos dos objetos gr√°ficos
hold on
grid on

plot(x, yx1(x), '-r*');
legenda{end+1} = 'Valor Exato';    % Insere r√≥tulo no final das c√©lulas dos r√≥tulos

plot(x, Y_euler_a(xgraf), '-gx');
legenda{end+1} = 'Euler';    

plot(x, Y_eulermelhorado_a(xgraf), '-b+');
legenda{end+1} = 'Euler Melhorado'; 

plot(x, Y_eulermodificado_a(xgraf), '-ys');
legenda{end+1} = 'Euler Modificado'; 

plot(x, Y_FRK12_a(xgraf), '-mh');
legenda{end+1} = 'Felhberg 1(2)'; 

plot(x, Y_FRK45_a(xgraf), '-cd');
legenda{end+1} = 'Felhberg 4(5)';

plot(x, Y_Dormand_Prince_passoFixo_a(xgraf), '-mo');
legenda{end+1} = 'Dormand Prince fixo';  

plot(X_Dormand_Prince_passoAdaptativo_a,Y_Dormand_Prince_passoAdaptativo_a, '-k^');
legenda{end+1} = 'Dormand Prince adapt';

xlabel('x');
ylabel('y');
title(PVIstr1)
legend(legenda,'location','northwest');
hold off

##pngfilename1 = 'GraficoA';
##fprintf('Gerando grafico png em arquivo ''%s''...\n', pngfilename1 );
##print(pngfilename1, '-dpng');

%Erros A
figure(2);
legenda_erros = {};

semilogy(x,abs(Y_euler_a(xgraf)-yx1(x)), '-gd');
legenda_erros{end+1} = 'Erro Euler';

grid on
hold on

semilogy(x,abs(Y_eulermelhorado_a(xgraf)-yx1(x)),'-ro');
legenda_erros{end+1} = 'Erro EulerMelhorado';

semilogy(x,abs(Y_eulermodificado_a(xgraf)-yx1(x)),'-ks');
legenda_erros{end+1} = 'Erro Modificado';

semilogy(x,abs(Y_FRK12_a(xgraf)-yx1(x)),'-y^');
legenda_erros{end+1} = 'Erro FRK12';

semilogy(x,abs(Y_FRK45_a(xgraf)-yx1(x)),'-c+');
legenda_erros{end+1} = 'Erro FRK45';

semilogy(x,abs(Y_Dormand_Prince_passoFixo_a(xgraf)-yx1(x)),'-mh');
legenda_erros{end+1} = 'Erro DPfix';

semilogy(X_Dormand_Prince_passoAdaptativo_a,abs(Y_Dormand_Prince_passoAdaptativo_a-yx1(X_Dormand_Prince_passoAdaptativo_a)),'-m*');
legenda_erros{end+1} = 'Erro DPadapt';

xlabel('x');
ylabel('ln(Erro)');
title('Erros A, Escala Log')
legend(legenda_erros,'location','east');
hold off

##pngfilename_erroA = 'ErroA';
##fprintf('Gerando grafico png em arquivo ''%s''...\n', pngfilename_erroA );
##print(pngfilename_erroA, '-dpng');


%Gr·fico de B
figure(3);
hold on
grid on

plot(x, yx2(x), '-r*');
plot(x, Y_euler_b(xgraf), '-g+');
plot(x, Y_eulermelhorado_b(xgraf), '-bo');
plot(x, Y_eulermodificado_b(xgraf), '-yd');
plot(x, Y_FRK12_b(xgraf), '-mh');
plot(x, Y_FRK45_b(xgraf), '-c^');
plot(x, Y_Dormand_Prince_passoFixo_b(xgraf), '-mx');
plot(X_Dormand_Prince_passoAdaptativo_b, Y_Dormand_Prince_passoAdaptativo_b, '-ks');

xlabel('x');
ylabel('y');
title(PVIstr2)
legend(legenda,'location','southwest');
hold off

##pngfilename2 = 'GraficoB';
##fprintf('Gerando grafico png em arquivo ''%s''...\n', pngfilename2 );
##print(pngfilename2, '-dpng');


%Erros B
figure(4);

semilogy(x,abs(Y_euler_b(xgraf)-yx2(x)), '-gh');
grid on
hold on
semilogy(x,abs(Y_eulermelhorado_b(xgraf)-yx2(x)),'-ro');
semilogy(x,abs(Y_eulermodificado_b(xgraf)-yx2(x)),'-k+');
semilogy(x,abs(Y_FRK12_b(xgraf)-yx2(x)),'-yx');
semilogy(x,abs(Y_FRK45_b(xgraf)-yx2(x)),'-cs');
semilogy(x,abs(Y_Dormand_Prince_passoFixo_b(xgraf)-yx2(x)),'-m^');
semilogy(X_Dormand_Prince_passoAdaptativo_b,abs(Y_Dormand_Prince_passoAdaptativo_b-yx2(X_Dormand_Prince_passoAdaptativo_b)),'-m*');

xlabel('x');
ylabel('ln(Erro)');
title('Erros B, Escala Log')
legend(legenda_erros,'location','east');
hold off

##pngfilename_erroB = 'ErroB';
##fprintf('Gerando grafico png em arquivo ''%s''...\n', pngfilename_erroB );
##print(pngfilename_erroB, '-dpng');

%Grafico C
figure(5);
hold on
grid on
xc = 1:0.1:2;
plot(xc, yx3(xc), '-r*');
plot(xc, Y_euler_c(xgraf), '-g+');
plot(xc, Y_eulermelhorado_c(xgraf), '-bh');
plot(xc, Y_eulermodificado_c(xgraf), '-ys');
plot(xc, Y_FRK12_c(xgraf), '-m^');
plot(xc, Y_FRK45_c(xgraf), '-cd');
plot(xc, Y_Dormand_Prince_passoFixo_c(xgraf), '-mx');
plot(X_Dormand_Prince_passoAdaptativo_c, Y_Dormand_Prince_passoAdaptativo_c, '-k');

xlabel('x');
ylabel('y');
title(PVIstr3)
legend(legenda,'location','northwest');
hold off

##pngfilename3 = 'GraficoC';
##fprintf('Gerando grafico png em arquivo ''%s''...\n', pngfilename3 );
##print(pngfilename3, '-dpng');

%Erros C
figure(6);

semilogy(xc,abs(Y_euler_c(xgraf)-yx3(xc)), '-gh');
grid on
hold on
semilogy(xc,abs(Y_eulermelhorado_c(xgraf)-yx3(xc)),'-rx');
semilogy(xc,abs(Y_eulermodificado_c(xgraf)-yx3(xc)),'-kd');
semilogy(xc,abs(Y_FRK12_c(xgraf)-yx3(xc)),'-yh');
semilogy(xc,abs(Y_FRK45_c(xgraf)-yx3(xc)),'-co');
semilogy(xc,abs(Y_Dormand_Prince_passoFixo_c(xgraf)-yx3(xc)),'-ms');
semilogy(X_Dormand_Prince_passoAdaptativo_c,abs(Y_Dormand_Prince_passoAdaptativo_c-yx3(X_Dormand_Prince_passoAdaptativo_c)),'-m*');

xlabel('x');
ylabel('ln(Erro)');
title('Erros C, Escala Log')
legend(legenda_erros,'location','east');
hold off

##pngfilename_erroC = 'ErroC';
##fprintf('Gerando grafico png em arquivo ''%s''...\n', pngfilename_erroC );
##print(pngfilename_erroC, '-dpng');

%----------------------------------- PARTE 2 ---------------------------%
parte2