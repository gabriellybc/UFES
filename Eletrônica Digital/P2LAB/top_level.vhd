----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    18:08:10 05/09/2021 
-- Design Name: 
-- Module Name:    top_level - Behavioral 
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

entity top_level is
	Port ( clk : in  STD_LOGIC;
          reset : in  STD_LOGIC;
			 c : in  STD_LOGIC;
			 
			 SRg : out STD_LOGIC;
			 SRy : out STD_LOGIC;
			 SRr : out STD_LOGIC;
			 
			 SAg : out STD_LOGIC;
			 SAy : out STD_LOGIC;
			 SAr : out STD_LOGIC );
end top_level;

architecture Behavioral of top_level is
	signal timer_tick: std_logic;
	signal d: std_logic_vector(14 downto 0);
	signal cnt: std_logic_vector(1 downto 0);
	signal m: std_logic;
begin

	-- instancia o fsm_control
	fsm_control_unit: entity work.fsm_control (Behavioral)
						port map ( clk => clk, 
						reset => reset, 
						timer_tick => timer_tick,
						c => c,
						m => m,
						cnt => cnt,
						SRg => SRg,
						SRy => SRy,
						SRr => SRr,
						SAg => SAg,
						SAy => SAy,
						SAr => SAr);
						
	-- instancia o timer
	timer_unit: entity work.timer (Behavioral)
						port map ( clk => clk, 
						reset => reset,
						d => d,
						cnt => cnt,
						timer_tick => timer_tick);
						
	-- instancia o mux2_1
	mux2_1_unit: entity work.mux2_1 (Behavioral)
						port map ( m => m,
						d => d); 

end Behavioral;

