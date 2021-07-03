----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    16:24:26 05/09/2021 
-- Design Name: 
-- Module Name:    fsm_control - Behavioral 
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

entity fsm_control is
	port ( clk : in  STD_LOGIC;
          reset : in  STD_LOGIC;
          timer_tick : in  STD_LOGIC;
			 c : in STD_LOGIC;
			 m : out STD_LOGIC;
			 cnt : out STD_LOGIC_VECTOR (1 downto 0);
			 
			 SRg : out STD_LOGIC;
			 SRy : out STD_LOGIC;
			 SRr : out STD_LOGIC;
			 
			 SAg : out STD_LOGIC;
			 SAy : out STD_LOGIC;
			 SAr : out STD_LOGIC );
end fsm_control;

architecture Behavioral of fsm_control is
	type state_type is (autopista_livre, autopista_atencao, contando_5s_1, estrada_rural_livre, contando_20s, estrada_rural_atencao, contando_5s_2);
	signal state_reg, state_next : state_type;
	
begin

 -- state register
	process(clk, reset)
	begin
		if reset = '1' then
			state_reg <= autopista_livre;
		elsif clk'event and clk = '1' then
			state_reg <= state_next; 
		end if;
	end process;
	
-- proximo estado / saida logica
	process(state_reg, timer_tick, c)
	begin
		state_next <= state_reg;
		SRg <= '0';
		SRy <= '0';
		SRr <= '0';
		SAg <= '0';
		SAy <= '0';
		SAr <= '0';
		m <= '0';
		case state_reg is
			when autopista_livre =>
				SAg <= '1';
				SRr <= '1';
				cnt <= "00";
				if c = '1' then
					state_next <= autopista_atencao;
				-- no else branch
				end if;
			when autopista_atencao =>
				SAy <= '1';
				SRr <= '1';
				m <= '1';
				cnt <= "01";
				state_next <= contando_5s_1;
			when contando_5s_1 =>
				SAy <= '1';
				SRr <= '1';
				cnt <= "10";
				if timer_tick = '1' then
					state_next <= estrada_rural_livre;
				-- no else branch
				end if;
			when estrada_rural_livre =>
				SAr <= '1';
				SRg <= '1';
				m <= '0';
				cnt <= "01";
				state_next <= contando_20s;
			when contando_20s =>
				SAr <= '1';
				Srg <= '1';
				cnt <= "11";
				if timer_tick = '1' then
					state_next <= estrada_rural_atencao;
				-- no else branch
				end if;
			when estrada_rural_atencao =>
				SAr <= '1';
				SRy <= '1';
				m <= '1';
				cnt <= "01";
				state_next <= contando_5s_2;
			when contando_5s_2 =>
				SAr <= '1';
				Sry <= '1';
				cnt <= "11";
				if timer_tick = '1' then
					state_next <= autopista_livre;
					-- no else branch
				end if;
		end case;
	end process;			
end Behavioral;

