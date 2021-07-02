--------------------------------------------------------------------------------
-- Company: 
-- Engineer:
--
-- Create Date:   11:25:12 04/22/2021
-- Design Name:   
-- Module Name:   C:/Users/Desktop/Documents/UFES/Xilinx/contador_Johnson/johnsons_counter_8bits_tb.vhd
-- Project Name:  contador_Johnson
-- Target Device:  
-- Tool versions:  
-- Description:   
-- 
-- VHDL Test Bench Created by ISE for module: johnsons_counter_8bits
-- 
-- Dependencies:
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
--
-- Notes: 
-- This testbench has been automatically generated using types std_logic and
-- std_logic_vector for the ports of the unit under test.  Xilinx recommends
-- that these types always be used for the top-level I/O of a design in order
-- to guarantee that the testbench will bind correctly to the post-implementation 
-- simulation model.
--------------------------------------------------------------------------------
LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
 
-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--USE ieee.numeric_std.ALL;
 
ENTITY johnsons_counter_8bits_tb IS
END johnsons_counter_8bits_tb;
 
ARCHITECTURE arch OF johnsons_counter_8bits_tb IS 
 
   constant T: time := 10 ns; -- clk period
	-- Component Declaration for the Unit Under Test (UUT)
   --Inputs
   signal clk : std_logic;
   signal reset : std_logic;
   signal enable : std_logic;

 	--Outputs
   signal count : std_logic_vector(7 downto 0);
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
   uut: entity work.johnsons_counter_8bits(arch)
	PORT MAP (
          clk => clk,
          reset => reset,
          enable => enable,
          count => count
        );

   -- 20 ns clock running forever
   process
   begin
		clk <= '0';
		wait for T/2;
		clk <= '1';
		wait for T/2;
   end process;
	
	-- reset asserted for clk_period/2
	reset <= '1', '0' after T/2;
 

   -- Stimulus process
   process
   begin		
      -- Valor inicial com contagem desabilitada
		enable <= '0';
      wait until falling_edge(clk);
		wait until falling_edge(clk);
		-- Habilita contagem
		enable <= '1'; 
		wait until falling_edge(clk);
		wait until falling_edge(clk);
		-- Contagem circular por todos os valores 
		for i in 1 to 16 loop -- count 16 clocks
			wait until falling_edge(clk);
		end loop;
		-- terminate simulation
		assert false
			report "Simulation Completed"
			severity failure;
		end process;
END arch;
