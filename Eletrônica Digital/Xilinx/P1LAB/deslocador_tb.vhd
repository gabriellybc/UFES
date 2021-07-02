-- TestBench Deslocador
--=============================
-- Gabrielly Barcelos Cariman
--=============================

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
 
-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
USE ieee.numeric_std.ALL;
 
ENTITY deslocador_tb IS
END deslocador_tb;
 
ARCHITECTURE behavior_tb OF deslocador_tb IS 
 
   signal x : std_logic_vector(3 downto 0);
   signal SHR, ROTL, MUL : std_logic;
   signal z : std_logic_vector(3 downto 0);
	signal controle : std_logic_vector(2 downto 0);
 
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
	uut: entity work.deslocador(behavioral) 
	port map (x=>x, SHR=>SHR, ROTL=>ROTL, MUL=>MUL, z=>z);


	--  Test Bench Statements
	
	process
   begin
--	x <= "0000";
	-- Metodo com otimizaçao do tempo da simulacao:
--	for i in 1 to 16 loop
--			SHR <= '1';
--			ROTL <= '1';
--			MUL <= '1';
--		wait for 200 ns;
--			SHR <= '1';
--			ROTL <= '1';
--			MUL <= '0';
--		wait for 200 ns;
--			SHR <= '1';
--			ROTL <= '0';
--			MUL <= '1';
--		wait for 200 ns;
--			SHR <= '1';
--			ROTL <= '0';
--			MUL <= '0';
--		wait for 200 ns;
--			SHR <= '0';
--			ROTL <= '1';
--			MUL <= '1';
--		wait for 200 ns;
--			SHR <= '0';
--			ROTL <= '1';
--			MUL <= '0';
--		wait for 200 ns;
--			SHR <= '0';
--			ROTL <= '0';
--			MUL <= '1';
--		wait for 200 ns;
--			SHR <= '0';
--			ROTL <= '0';
--			MUL <= '0';
--		wait for 200 ns;
--		x <= std_logic_vector(unsigned(x)+1);
--	end loop;
	
		
		-- Metodo mais otimizado em relacao a linhas de codigos:
	x <= "0000";
	for i in 1 to 16 loop
		SHR <= '1';
		ROTL <= '1';
		MUL <= '1';
		controle <= "111";
		wait for 200 ns;
		
		for a in 1 to 8 loop
			MUL <= controle(0);
			ROTL <= controle(1);
			SHR <= controle(2);
			controle <= std_logic_vector(unsigned(controle)-1);
			wait for 200 ns;
		end loop;
		
		x <= std_logic_vector(unsigned(x)+1);
	end loop;

	assert false
         report "Simulation Completed"
         severity failure;		
   end process;
  --  Test Bench Statements
end behavior_tb;
