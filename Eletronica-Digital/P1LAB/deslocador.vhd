----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    15:03:59 03/26/2021 
-- Design Name: 
-- Module Name:    deslocador - Behavioral 
-- Project Name: 
-- Target Devices: 
-- Tool versions: 
-- Description: 
--
-- Dependencies: 
--
-- Revision: 
-- Revision 0.01 - File Created
-- Additional Comments: 
--
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity deslocador is
    Port ( x : in  std_logic_vector (3 downto 0);
			  SHR : in  std_logic;
			  ROTL : in  std_logic;
			  MUL : in  std_logic;
           z : out  std_logic_vector (3 downto 0));
end deslocador;


architecture behavioral of deslocador is
   signal c : std_logic_vector (1 downto 0);
begin

--=======================================================
-- Criando bloco de logica computacional - LC
--=======================================================
	c <= (SHR or ROTL) & (SHR or ((not ROTL)and MUL));

--=======================================================
-- Criando bloco para MUX 4x1 
--=======================================================
	process(x,c)
	begin
		if c = "11" then
			z <= "0" & x(3 downto 1); -- Deslocamento logico para a direita com insercao de 0 
		elsif c = "10" then
			z <= x(2 downto 0) & x(3); -- Rotacao a esquerda
		elsif c = "01" then
			z <= x(2 downto 0) & "0"; -- Multiplicacao por 2 = Deslocamento logico para a esquerda. O ultimo bit sempre sera 0, para todos os valores de x que serao multiplicados.
		else -- c = "00"
			z <= x; -- Sem deslocamento
		end if;
	end process;
	
end behavioral;