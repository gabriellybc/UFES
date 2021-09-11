----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    20:05:58 11/17/2020 
-- Design Name: 
-- Module Name:    johnsons_counter_8bits - arch 
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
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity johnsons_counter_8bits is
    Port ( clk : in  STD_LOGIC;
           reset : in  STD_LOGIC;
			  enable: in STD_LOGIC;
           count : out  STD_LOGIC_VECTOR (7 downto 0));
end johnsons_counter_8bits;

architecture arch of johnsons_counter_8bits is
	signal count_reg, count_next: std_logic_vector(7 downto 0);
begin
	
	-- register
	process (clk, reset)
	begin
		if (reset = '1') then 
			count_reg <= (others => '0');
		elsif (clk'event and clk = '1') then
			count_reg <= count_next;
		end if;
	end process;
	
	-- logica de proximo estado (Contador Johnson de 8 bits)
	count_next <= '1' & count_reg(7 downto 1) when enable = '1' and count_reg(0) = '0' else
					  '0' & count_reg(7 downto 1) when enable = '1' and count_reg(0) = '1' else
					  count_reg;  -- enable = '0'
					  
	-- logica da saida
	count <= count_reg;

end arch;

