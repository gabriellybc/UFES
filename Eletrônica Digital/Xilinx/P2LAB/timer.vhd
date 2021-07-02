----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    18:05:45 05/09/2021 
-- Design Name: 
-- Module Name:    timer - Behavioral 
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

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity timer is
	port ( clk : in  STD_LOGIC;
          reset : in  STD_LOGIC;
			 d : in STD_LOGIC_VECTOR (14 downto 0);
			 cnt : in STD_LOGIC_VECTOR (1 downto 0);
          timer_tick : out  STD_LOGIC);
end timer;

architecture Behavioral of timer is
	signal r_reg, r_next: unsigned(14 downto 0);
begin
 -- register
	process(clk, reset)
	begin
		if reset = '1' then
			r_reg <= (others => '0');
		elsif clk'event and clk = '1' then
			r_reg <= r_next; 
		end if;
	end process;

-- proximo estado / saida logica
	r_next <= r_reg when cnt = "00" else
				 unsigned(d) when cnt = "01" else
				 r_reg +1;
				 
	timer_tick <= '1' when r_reg = "100111000011111" else
					  '0';
					  
end Behavioral;

