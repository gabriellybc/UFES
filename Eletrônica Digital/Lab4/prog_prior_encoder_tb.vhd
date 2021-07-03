-- TestBench Template 

  library ieee;
  use ieee.std_logic_1164.all;
  use ieee.numeric_std.all;

  entity testbench IS
  end testbench;

  architecture behavior_tb of testbench is 

	 signal r:  std_logic_vector(7 downto 0);
	 signal c, code: std_logic_vector(2 downto 0);
	 signal active: std_logic;
  begin

  -- Component Instantiation
  uut: entity work.prog_prior_encoder(behavioral) 
  port map (r=>r, c=>c,code=>code, active=>active);

  --  Test Bench Statements
   process
   begin
      r <= "11011011";
      c <= "111";
		wait for 200 ns;
      c <= "110";
      wait for 200 ns;
      c <= "101";
      wait for 200 ns;
      c <= "100";
      wait for 200 ns;
      c <= "011";
      wait for 200 ns;
      c <= "010";
      wait for 200 ns;
      c <= "001";
      wait for 200 ns;
      c <= "000";
      wait for 200 ns;

      r <= "11110000";
      c <= "111";
		wait for 200 ns;
      c <= "110";
      wait for 200 ns;
      c <= "101";
      wait for 200 ns;
      c <= "100";
      wait for 200 ns;
      c <= "011";
      wait for 200 ns;
      c <= "010";
      wait for 200 ns;
      c <= "001";
      wait for 200 ns;
      c <= "000";
      wait for 200 ns;

      r <= "00001111";
      c <= "111";
		wait for 200 ns;
      c <= "110";
      wait for 200 ns;
      c <= "101";
      wait for 200 ns;
      c <= "100";
      wait for 200 ns;
      c <= "011";
      wait for 200 ns;
      c <= "010";
      wait for 200 ns;
      c <= "001";
      wait for 200 ns;
      c <= "000";
      wait for 200 ns;
		
      r <= "00000000";
      c <= "111";
		wait for 200 ns;
      c <= "110";
      wait for 200 ns;
      c <= "101";
      wait for 200 ns;
      c <= "100";
      wait for 200 ns;
      c <= "011";
      wait for 200 ns;
      c <= "010";
      wait for 200 ns;
      c <= "001";
      wait for 200 ns;
      c <= "000";
      wait for 200 ns;

      assert false
         report "Simulation Completed"
         severity failure;		
   end process;
  --  Test Bench Statements
end behavior_tb;