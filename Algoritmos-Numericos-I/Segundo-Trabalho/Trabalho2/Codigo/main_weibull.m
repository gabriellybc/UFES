%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%              Segundo Trabalho de Algoritmos Numericos             %%%%%%%
%%%%%%  Autores: Gabriel Boasquives, Gabriel Falcone e Gabrielly Cariman %%%%%%%
%%%%%%                    Data: 03 de Setembro de 2021                   %%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%                   1.5 Distribuicao de Weibull                     %%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% -------------------------------- Tarefa 1 ---------------------------------- %
FDP_Weibull = @(x, lambda, k) (((k/lambda).*((x./lambda).^(k-1))).*(exp(-(x./lambda).^k)));

% -------------------------------- Tarefa 2 ---------------------------------- %
x = 0.1:0.5:2.5; lambda = 1; k = 0.5;

fdp_5 = wblpdf(x, lambda, k);
my_fdp_5 = FDP_Weibull(x, lambda, k);

diferenca = fdp_5 - my_fdp_5;
fprintf(' Tarefa 2: \n');
printTabX( diferenca, 'diferenca', '%0.2f', 'Difença entre a minha implementaç˜ao de FDP com a do sistema wblpdf');

% -------------------------------- Tarefa 3 ---------------------------------- %
%%%%%%             G R A F I C O  P A R A M E T R I Z A D O              %%%%%%%
figure(3);
clf;
hold on;
grid on;
leg = {};

% Pares (lambda, k)
param = {
  {1, 0.5},
  {1, 1},
  {1, 1.5},
  {1, 5},
};

x = 0:0.01:2.5;  % Intervalo

for i=1:length(param)
  lambda = param{i}{1};
  k = param{i}{2};
  y = FDP_Weibull(x, lambda, k);
  plot(x,y,"linewidth",2)%, 'iterpreter', 'tex');
  leg{end+1} = sprintf('\\lambda=%3.1f, \\k=%3.1f', lambda, k);
end

ylim([0 2.5]);
xlabel('X');
ylabel('FDP(X)');
title('Probability density function');
h = legend(leg);
set (h, 'interpreter', 'tex', 'location', 'northeastoutside');
hold off;

% -------------------------------- Tarefa 4 ---------------------------------- %
FDA_Weibull = @(x, lambda, k) (1-(exp(-((x./lambda).^k))));

x = 0:0.5:2.5; lambda = 1; k = 0.5;

fda_5 = wblcdf(x, lambda, k);
my_fda_5 = FDA_Weibull(x, lambda, k);

diferenca_fda_5 = fda_5 - my_fda_5;
fprintf(' Tarefa 4: \n');
printTabX( diferenca_fda_5, 'diferenca', '%0.2f', 'Difença entre a minha implementaç˜ao de FDA com a do sistema wblcdf');

figure(4);
clf;
hold on;
grid on;
leg1 = {}; 

% Pares (lambda, k)
param = {
  {1, 0.5},
  {1, 1},
  {1, 1.5},
  {1, 5},
};

x = 0:0.01:2.5;  % Intervalo

for i=1:length(param)
  lambda = param{i}{1};
  k = param{i}{2};
  y = FDA_Weibull(x, lambda, k);
  plot(x,y, "linewidth",2)%, 'iterpreter', 'tex');
  leg1{end+1} = sprintf('\\lambda=%3.1f, \\k=%3.1f', lambda, k);
end

ylim([0 1.0]);
xlabel('X');
ylabel('FDA(X)');
title('Função de distribuição acumulada');
h = legend(leg1);
set (h, 'interpreter', 'tex', 'location', 'northeastoutside');
hold off;

% -------------------------------- Tarefa 5 ---------------------------------- %
load velocidade_vento.mat;
x = velocidade_vento;
k_velho = 1;
phi = @(k) 1/((mean((x.^k).*log(x))/mean(x.^k)) - mean(log(x)));
cont = 0;

for j = 1 : length(x)
  k_novo = phi(k_velho);
  k_velho = k_novo;
  
  if k_novo == k_velho
    cont++;
    if cont == 50
      break
    endif
  elseif k_novo!=k_velho
    cont = 0;   
  endif
 end

lambda = (mean(x.^k_novo))^(1/k_novo);
fprintf(' Tarefa 5: \n');
printf("Parametro k = %d e Parametro lambda = %d\n",k_novo,lambda);
 