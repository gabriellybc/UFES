%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%              Segundo Trabalho de Algoritmos Numericos             %%%%%%%
%%%%%% Autores: Gabriel Boasquives, Gabriel Falcone e Gabrielly Cariman  %%%%%%%
%%%%%%                    Data: 03 de Setembro de 2021                   %%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%               1.6 Distribuicao de Pareto Generalizada             %%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% -------------------------------- Tarefa 1 ---------------------------------- %
FDP_Pareto = @(x, mi, sigma, xi) ((1/sigma).*(1+(xi.*(x-mi)./sigma)).^(-(1/xi)-1));

% -------------------------------- Tarefa 2 ---------------------------------- %
%%%%%%             G R A F I C O  P A R A M E T R I Z A D O              %%%%%%%
figure(5);
clf;
hold on;
grid on;
leg = {};
mi=0;

% Pares (sigma, xi)
param = {
  {1, 1},
  {1, 5},
  {1, 20},
  {2, 1},
  {2, 5},
  {2, 20}
};

x = 0:0.05:5;  % Intervalo

for i=1:length(param)
  sigma = param{i}{1};
  xi = param{i}{2};
  y = FDP_Pareto(x, mi, sigma,xi);
  plot(x, y,"linewidth",2);
  leg{end+1} = sprintf('\\sigma=%3.1f, \\xi=%3.1f', sigma, xi);
end
xlim( [0 5.0]);
ylim([0 1.0]);
xlabel('X');
ylabel('FDP(X)');
title('Probability Density Functions (PDFs)');
h = legend(leg);
set (h, 'interpreter', 'tex', 'location', 'northeastoutside');
hold off;

% -------------------------------- Tarefa 3 ---------------------------------- %
FDA_Pareto = @(x, mi, sigma, xi) ifelse(xi ~= 0,...       % Se xi diferente de 0, faca:
                                  1 - (1 + ((xi.*(x-mi))./sigma)).^(-(1/xi)),... % Se ele não for, faca:
                                  1 - exp(-((x-mi)./sigma)));
                                  
%%%%%%             G R A F I C O  P A R A M E T R I Z A D O              %%%%%%%
figure(6);
clf;
hold on;
grid on;
leg = {};
mi=0;

% Pares (sigma, xi)
param = {
  {1, 1},
  {1, 5},
  {1, 20},
  {2, 1},
  {2, 5},
  {2, 20}
};

x = 0:0.05:5;  % Intervalo

for i=1:length(param)
  sigma = param{i}{1};
  xi = param{i}{2};
  y = FDA_Pareto(x, mi, sigma,xi);
  plot(x, y,"linewidth",2);
  leg{end+1} = sprintf('\\sigma=%3.1f, \\xi=%3.1f', sigma, xi);
end
xlim([0 5.0]);
ylim([0 1.0]);
xlabel('X');
ylabel('FDA(X)');
title('Distribuição de Pareto Generalizada: FDA');
h = legend(leg);
set (h, 'interpreter', 'tex', 'location', 'northeastoutside');
hold off;

% -------------------------------- Tarefa 4 ---------------------------------- %
load velocidade_vento.mat;

% Derivada Verossimilhanca:
x = velocidade_vento;
LL = @(theta) ((length(x)^2*theta)*(-((sum(-x./(1-theta.*x)))/(length(x)*theta))+(sum(log(1-theta.*x)))/(length(x)*theta^2)))/sum(log(1-theta.*x))-(sum(-x./(1-theta.*x)));

eps = 1e-6;
maxiter = 50;
theta_chapeu = raizBisecPosFalsa(true, LL, -0.000000001,0.03 , eps, maxiter);

% Xi Chapeu:
soma_ln2 = @(x,i,theta) log(1 - (theta*x(i)));
somatorio_ln2 = @(x,theta) sum(soma_ln2(x,[1:length(x)],theta));
xi_chapeu = @(x,theta) -((1/length(x))*somatorio_ln2(x,theta));

xi_pareto = xi_chapeu(velocidade_vento,theta_chapeu);

% Sigma Chapeu:
sigma_pareto = xi_pareto/theta_chapeu;

fprintf('\n Tarefa 4: \n');
fprintf('Estimativas: sigma = %3.1f, xi = %3.1f \n', sigma_pareto, xi_pareto);

% -------------------------------- Tarefa 5 ---------------------------------- %
%%%%%%             G R A F I C O  P A R A M E T R I Z A D O              %%%%%%%
figure(7);
clf;
%%%%%%%%%%%%%%%
%%%%  S U B P L O T  1
subplot(3, 1, 1);	% (rows, cols, index)
%%%%%%%%%%%%%%%
grid on;
leg = {};
xmin = 0; xmax = 50; ymin = 0; ymax = 8000;

nbins = 50;

% Intervalo
x = xmin:0.1:xmax; 

% Histograma
[counts,centers] = hist(velocidade_vento, nbins);
hist(velocidade_vento, nbins)
largura_bins = centers(end) - centers(end-1);
leg{end+1} = sprintf('Velocidade do vento');

hold on;

% Gaussiana
mi = mean(velocidade_vento); sigma = std(velocidade_vento);
y_gaussiana = largura_bins*sum(counts).*FDP_Normal(x, mi, sigma^2);
plot(x, y_gaussiana,"linewidth",2);
leg{end+1} = sprintf('Gaussiana: \\mu=%3.1f, \\sigma=%3.1f', mi, sigma^2);

% Weibull
lambda = lambda; k =  k_novo;
y_weibull = largura_bins*sum(counts).*FDP_Weibull(x, lambda, k);
plot(x, y_weibull,"linewidth",2);
leg{end+1} = sprintf('Weibull: \\lambda=%3.1f, \\k=%3.1f', lambda, k);

%Pareto generalizado
mi = 0;
y_pareto = largura_bins*sum(counts).*FDP_Pareto(x, mi, sigma_pareto,xi_pareto);
plot(x, y_pareto,"linewidth",2);
leg{end+1} = sprintf('Pareto generalizado: \\mu=%3.1f, \\sigma=%3.1f, \\xi=%3.1f', mi, sigma_pareto, xi_pareto);

ylabel('Qtd','FontSize',7);
title('Histograma com 50 bins','FontSize',8);
le = legend(leg);
set (le, 'interpreter', 'tex','FontSize',7);
hold off;

%%%%%%%%%%%%%%%
%%%%  S U B P L O T  2
subplot(3, 1, 2);	% (rows, cols, index)
%%%%%%%%%%%%%%%
grid on;
hold on;
leg = {};
ymin = -250000; ymax = 100000;
theta_min = 0; theta_max = 0.030; qntPontos = 50;

% Intervalo
theta = linspace(theta_min, theta_max, qntPontos);

% Verossimilhanca
L = [];
for i = 1:length(theta)
  L(end+1) = verossimilhanca(velocidade_vento, theta(i));
endfor
L(1) = L(2);
plot(theta, L, "linewidth", 2);
leg{end+1} = sprintf('L(theta)');

% Derivado da verossimilhanca
deri = [];
for i = 1:length(theta)
  deri(end+1) = LL(theta(i));
endfor
deri(1) = deri(2);
plot(theta, deri, "linewidth", 2);
leg{end+1} = sprintf('dL(theta)');

% Zeros
zerados = zeros(1,qntPontos);
plot(theta, zerados,"linewidth",1,'k--');
leg{end+1} = sprintf('0');

% Ponto Theta Max
dL = LL(theta_chapeu);
plot(theta_chapeu, dL,"linewidth",5,'r.');
leg{end+1} = sprintf('(theta, dL(theta))=(%1.3f, %1.3f)', theta_chapeu, dL);

ylabel('L --- d(L)','FontSize',7);
title('Verossimilhança','FontSize',8);
le = legend(leg);
set (le, 'interpreter', 'tex','FontSize', 7)%, 'location', 'northeastoutside');
hold off;

%%%%%%%%%%%%%%%
%%%%  S U B P L O T  3
subplot(3, 1, 3);	% (rows, cols, index)
%%%%%%%%%%%%%%%
grid on;
leg = {};

x = 1:length(velocidade_vento); % Intervalo

plot(x, velocidade_vento,"linewidth",2);
leg{end+1} = sprintf('Vh: início=01/01/2020 00h:00m --- final=31/12/2020 23h:54m ');

ylabel('m/s','FontSize',7);
title('Velocidade do vento','FontSize',8);
le = legend(leg);
set (le, 'interpreter', 'tex','FontSize',7);
hold off;
