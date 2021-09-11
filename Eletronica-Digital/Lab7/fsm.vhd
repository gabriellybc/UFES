----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    19:08:09 04/15/2021 
-- Design Name: 
-- Module Name:    fsm - Behavioral 
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

entity fsm is
    port ( clk : in  STD_LOGIC;
           reset : in  STD_LOGIC;
           timer_tick : in  STD_LOGIC;
			  dig : out  STD_LOGIC_VECTOR (1 downto 0);
			  letter : out  STD_LOGIC_VECTOR (7 downto 0));
end fsm;

architecture Behavioral of fsm is
	type state_type is (s0, s1, s2, s3);
	signal state_reg, state_next : state_type;

begin

 -- state register
	process(clk, reset)
	begin
		if reset = '1' then
			state_reg <= s0;
		elsif clk'event and clk = '1' then
			state_reg <= state_next; 
		end if;
	end process;
	
 -- proximo estado / saida logica
	process(state_reg, timer_tick)
	begin
		state_next <= state_reg;
		dig <= "11";
		letter <= "00000000";
		case state_reg is
			when s0 =>
				dig <= "11";
				letter <= "01000111";
				if timer_tick = '1' then
					state_next <= s1;
				-- no else branch
				end if;
			when s1 =>
				dig <= "10";
				letter <= "01000001";
				if timer_tick = '1' then
					state_next <= s2;
				-- no else branch
				end if;
			when s2 =>
				dig <= "01";
				letter <= "01000010";
				if timer_tick = '1' then
					state_next <= s3;
				-- no else branch
				end if;
			when s3 =>
				dig <= "00";
				letter <= "01001001";
				if timer_tick = '1' then
					state_next <= s0;
				-- no else branch
				end if;
		end case;
	end process;
end Behavioral;