%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%              Segundo Trabalho de Algoritmos Numericos             %%%%%%%
%%%%%% Autores: Gabriel Boasquives, Gabriel Falcone e Gabrielly Cariman  %%%%%%%
%%%%%%                    Data: 10 de Setembro de 2021                   %%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%            1.4 Aquisicao de Dados Estatisticos Reais              %%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% -------------------------------- Tarefa 3 ---------------------------------- %
% Wind Speed == WSPD
fid = fopen ('rdda2h2020.txt');
linha = fgetl(fid);   % Pegando a primeira linha de texto
linha = fgetl(fid);   % Pegando a segunda linha de texto
out = textscan(fid,'%d%d%d%d%d%d%f%f%f%f%f%d%f%f%f%f%f%f','delimiter',' ');
fclose(fid);

velocidade_vento = out{7};
velocidade_vento = velocidade_vento';

% -------------------------------- Tarefa 4 ---------------------------------- %
velocidade_vento(velocidade_vento <= 0) = 0.1;
velocidade_vento(velocidade_vento > 50.0) = [];

save velocidade_vento.mat velocidade_vento;