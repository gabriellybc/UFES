function [f, sol, PVIstr, yx, yxstr] = solveEDO( RHS, x0_sym, y0_sym )
%SOLVE_EDO - Solução simbólica de uma equação diferencial ordinária EDO
%
% Syntax:  [f, sol, PVIstr, yx, yxstr] = solveEDO( RHS, x0_sym, y0_sym )
%
% Entradas:
%    RHS - Lado direito da EDO em forma de string, tem que ser formada
%          com o nome 'x' para a variável independente, e 'y' para a
%          variável dependente
%    x0_sym - Valor x inicial, definido preferencialmente como simbólico
%    y0_sym - Valor y inicial, definido preferencialmente como simbólico
%
% Saídas:
%    f   - O lado direito f(x, y(x)) da ODE como funcção numérica
%    sol - Solução simbólica do problema do valor inicial
%    PVIstr - Descrição textual do PVI
%    yx - Solução numérica do PVI
%    yxstr - Descrição textual da função que é solução do PVI
%
% Exemplos: 
%    [f, sol, PVIstr, yx, yxstr] = solveEDO('y', 0, 1) gera
%       [@(x,y)y, exp(x), 'PVI: y''=y, y(0.00)=1.00', @(x)exp(x), 'y(x)=exp(x)']
%
%    [f, sol, PVIstr, yx, yxstr] = solveEDO( 'exp(-x) - 4*y', 0, 1) gera
%       [ @(x,y)exp(-x)-4*y,  exp(-x).*(1.0./3.0)+exp(x.*-4.0).*(2.0./3.0),
%         'PVI: y'=exp(-x) - 4*y, y(0.00)=1.00',
%         @(x)exp(-x).*(1.0./3.0)+exp(x.*-4.0).*(2.0./3.0),
%         'y(x)=exp(-x).*(1.0./3.0)+exp(x.*-4.0).*(2.0./3.0)' ]
%
% Veja também: OUTRA_FUNCAO1,OUTRA_FUNCAO2

% Author: Thomas W. Rauber
% Departamento de Informática, Universidade Federal do Espírito Santo
% email: thomas.rauber@ufes.br
% Website: http://www.inf.ufes.br
% Novembro de 2020; Última revisão: 01/11/2020


if ~ischar(RHS)
   error('Argumento tem que ser string com especificacao do lado direito da EDO');
end

is_octave = (exist('OCTAVE_VERSION','builtin')>1); % Octave ou Matlab
if is_octave
	pkg load symbolic;
end;

syms y(x) 
 
PVIstr = sprintf('PVI: y''=%s, y(%.2f)=%.2f', RHS, double(x0_sym), double(y0_sym));
f = @(x, y) eval(RHS);
ode = diff(y) == f(x, y);
cond = y(x0_sym) == y0_sym;
sol = dsolve(ode, cond);
sol = simplify(sol);
if iscell(sol);
  Eq = sol{1};
else
  Eq = sol;
end
if is_octave
  F = rhs(Eq);
else
  F = Eq;
end
yx = matlabFunction(F);
fprintf('Versao numerica da solucao: '); yx
yxstr = func2str(yx);
yxstr = ['y(x)=' yxstr(5:end)];

fprintf('Verificacao da solucao analitica: Resultado tem que ser verdadeiro:\n');
verificacao_igualdade = 0 == diff(F,x) - f(x,F)  % y' = f(x, y(x)) ?

end
