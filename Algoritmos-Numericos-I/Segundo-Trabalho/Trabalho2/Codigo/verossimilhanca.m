%% Verossimilhanca da distribuicao de Pareto Generalizada
%% 
%% Autores: Gabriel Boasquives, Gabriel Falcone e Gabrielly Carim, 2021
%%
%% Input:
%%		1)	Vetor x com n amostras
%%		2)	Theta
%%
%% Output:
%%		1)	Verossimilhanca
%%
function l = verossimilhanca(x, theta)
  
  if theta < (1/max(x))
    
    soma = 0; n = length(x);
    
    for i = 1:length(x)
      soma = soma + log(1 - (theta*x(i)));
    endfor
    
    l = -n - soma - n*log(-((n*theta)^-1)*soma);
    
  else
    fprintf('INVALIDO A VEROSSIMILHANCA');
    l = 0.01;
  endif
endfunction