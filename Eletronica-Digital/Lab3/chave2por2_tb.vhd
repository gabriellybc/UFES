-- TestBench Chave2por2
--=============================
-- Eliete
--=============================
library ieee;
use ieee.std_logic_1164.all;

entity chave2por2_tb is
end chave2por2_tb;

architecture tb_arch of chave2por2_tb is
   signal test_in_ctrl: std_logic_vector(1 downto 0);
   signal test_in_x: std_logic_vector(1 downto 0);
   signal test_out_y_c,test_out_y_s,test_out_y_i,test_out_y_ca: std_logic_vector(1 downto 0);
begin
   -- instantiate the circuit under test
   uut_c: entity work.chave2por2 (cond_arch)
      port map( x=>test_in_x,ctrl=>test_in_ctrl, y=>test_out_y_c);
   -- instantiate the circuit under test
   uut_s: entity work.chave2por2 (sel_arch)
      port map( x=>test_in_x,ctrl=>test_in_ctrl, y=>test_out_y_s);
		   -- instantiate the circuit under test
   uut_i: entity work.chave2por2 (if_arch)
      port map( x=>test_in_x,ctrl=>test_in_ctrl, y=>test_out_y_i);
		   -- instantiate the circuit under test
   uut_ca: entity work.chave2por2 (case_arch)
      port map( x=>test_in_x,ctrl=>test_in_ctrl, y=>test_out_y_ca);

   -- test vector generator
   process
   begin
      test_in_ctrl <= "00";
		test_in_x <= "00";
      wait for 200 ns;
      test_in_ctrl <= "00";
		test_in_x <= "01";
      wait for 200 ns;
      test_in_ctrl <= "00";
		test_in_x <= "10";
      wait for 200 ns;
      test_in_ctrl <= "00";
		test_in_x <= "11";
      wait for 200 ns;
      test_in_ctrl <= "01";
		test_in_x <= "00";
      wait for 200 ns;
      test_in_ctrl <= "01";
		test_in_x <= "01";
      wait for 200 ns;
      test_in_ctrl <= "01";
		test_in_x <= "10";
      wait for 200 ns;
      test_in_ctrl <= "01";
		test_in_x <= "11";
      wait for 200 ns;
      test_in_ctrl <= "10";
		test_in_x <= "00";
      wait for 200 ns;
      test_in_ctrl <= "10";
		test_in_x <= "01";
      wait for 200 ns;
      test_in_ctrl <= "10";
		test_in_x <= "10";
      wait for 200 ns;
      test_in_ctrl <= "10";
		test_in_x <= "11";
      wait for 200 ns;
      test_in_ctrl <= "11";
		test_in_x <= "00";
      wait for 200 ns;
      test_in_ctrl <= "11";
		test_in_x <= "01";
      wait for 200 ns;
      test_in_ctrl <= "11";
		test_in_x <= "10";
      wait for 200 ns;
      test_in_ctrl <= "11";
		test_in_x <= "11";
      wait for 200 ns;
   end process;
	
   --monitor
   process
      variable error_status: boolean;
   begin
	   wait on test_in_x, test_in_ctrl;
      wait for 100 ns;
      if ((test_in_ctrl ="00" and test_in_x = "00" and (test_out_y_c = "00" and test_out_y_s = "00" and test_out_y_i = "00" and test_out_y_ca = "00")) or
          (test_in_ctrl ="00" and test_in_x = "01" and (test_out_y_c = "01" and test_out_y_s = "01" and test_out_y_i = "01" and test_out_y_ca = "01")) or 
          (test_in_ctrl ="00" and test_in_x = "10" and (test_out_y_c = "10" and test_out_y_s = "10" and test_out_y_i = "10" and test_out_y_ca = "10")) or
          (test_in_ctrl ="00" and test_in_x = "11" and (test_out_y_c = "11" and test_out_y_s = "11" and test_out_y_i = "11" and test_out_y_ca = "11")) or
          (test_in_ctrl ="01" and test_in_x = "00" and (test_out_y_c = "00" and test_out_y_s = "00" and test_out_y_i = "00" and test_out_y_ca = "00")) or
          (test_in_ctrl ="01" and test_in_x = "01" and (test_out_y_c = "10" and test_out_y_s = "10" and test_out_y_i = "10" and test_out_y_ca = "10")) or
          (test_in_ctrl ="01" and test_in_x = "10" and (test_out_y_c = "01" and test_out_y_s = "01" and test_out_y_i = "01" and test_out_y_ca = "01")) or 
          (test_in_ctrl ="01" and test_in_x = "11" and (test_out_y_c = "11" and test_out_y_s = "11" and test_out_y_i = "11" and test_out_y_ca = "11")) or 
          (test_in_ctrl ="10" and test_in_x = "00" and (test_out_y_c = "00" and test_out_y_s = "00" and test_out_y_i = "00" and test_out_y_ca = "00")) or 
          (test_in_ctrl ="10" and test_in_x = "01" and (test_out_y_c = "11" and test_out_y_s = "11" and test_out_y_i = "11" and test_out_y_ca = "11")) or 
          (test_in_ctrl ="10" and test_in_x = "10" and (test_out_y_c = "00" and test_out_y_s = "00" and test_out_y_i = "00" and test_out_y_ca = "00")) or 
          (test_in_ctrl ="10" and test_in_x = "11" and (test_out_y_c = "11" and test_out_y_s = "11" and test_out_y_i = "11" and test_out_y_ca = "11")) or 
          (test_in_ctrl ="11" and test_in_x = "00" and (test_out_y_c = "00" and test_out_y_s = "00" and test_out_y_i = "00" and test_out_y_ca = "00")) or 
          (test_in_ctrl ="11" and test_in_x = "01" and (test_out_y_c = "00" and test_out_y_s = "00" and test_out_y_i = "00" and test_out_y_ca = "00")) or 
          (test_in_ctrl ="11" and test_in_x = "10" and (test_out_y_c = "11" and test_out_y_s = "11" and test_out_y_i = "11" and test_out_y_ca = "11")) or 
          (test_in_ctrl ="11" and test_in_x = "11" and (test_out_y_c = "11" and test_out_y_s = "11" and test_out_y_i = "11" and test_out_y_ca = "11")) 
			 )
      then
         error_status := false;
      else
         error_status := true;
      end if;
      -- error reporting
      assert not error_status
         report "test failed."
         severity note;
   end process;
end tb_arch;