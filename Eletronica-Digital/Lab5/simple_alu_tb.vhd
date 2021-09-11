-- TestBench ALU
--=============================
-- Gabrielly Barcelos Cariman
--=============================

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
 
-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
USE ieee.numeric_std.ALL;
 
ENTITY simple_alu_tb IS
END simple_alu_tb;
 
ARCHITECTURE behavior OF simple_alu_tb IS 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
   --Inputs
   signal ctrl : std_logic_vector(2 downto 0);
   signal src0, src1 : std_logic_vector(7 downto 0);

 	--Outputs
   signal result_c, result_s, result_i, result_ca  : std_logic_vector(7 downto 0);
   -- No clocks detected in port list. Replace <clock> below with 
   -- appropriate port name 
 
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
	uut_c: entity work.simple_alu(cond_arch)
		port map(ctrl=>ctrl, src0=>src0, src1=>src1, result => result_c);
		
	-- Instantiate the Unit Under Test (UUT)
	uut_s: entity work.simple_alu(sel_arch)
		port map(ctrl=>ctrl, src0=>src0, src1=>src1, result => result_s);
	
	-- Instantiate the Unit Under Test (UUT)
	uut_i: entity work.simple_alu(if_arch)
		port map(ctrl=>ctrl, src0=>src0, src1=>src1, result => result_i);
	
	-- Instantiate the Unit Under Test (UUT)
	uut_ca: entity work.simple_alu(case_arch)
		port map(ctrl=>ctrl, src0=>src0, src1=>src1, result => result_ca);

   -- test vector generator
   process
   begin
	ctrl <= "000";
	for i in 1 to 8 loop
			src0 <= "00010101"; -- 21
			src1 <= "00011011"; -- 27
		wait for 200 ns;
			src0 <= "00010101"; -- 21
			src1 <= "11100101"; -- -27
		wait for 200 ns;
			src0 <= "11101011"; -- -21
			src1 <= "00011011"; -- 27
		wait for 200 ns;
			src0 <= "11101011"; -- -21
			src1 <= "11100101"; -- -27
		wait for 200 ns;
		ctrl <= std_logic_vector(unsigned(ctrl)+1);
	end loop;
	
	assert false
         report "Simulation Completed"
         severity failure;		
   end process;
  --  Test Bench Statements
end behavior;
