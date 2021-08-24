%
% Dormand-Prince --- Método padrão da função 'ode45' do Matlab/Octave
%
% Veja a tabela de Butcher em
% https://pt.wikipedia.org/wiki/M%C3%A9todo_de_Dormand-Prince
% 
%
%
function [X, Y] = RungeKutta_Dormand_Prince_ode45(f, x0, y0, h, n, passofixo )
    xn = x0 + n*h;
    if passofixo
        x = (x0:h:xn)';
        [X, Y] = ode45(f, x, [y0] );
    else
        [X, Y] = ode45(f, [x0,xn], [y0] );
    end
    X = X';
    Y = Y';
end
