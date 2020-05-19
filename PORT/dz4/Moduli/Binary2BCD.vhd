library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
 
entity Binary2BCD is
   Port ( 
      input   : in  std_logic_vector (7 downto 0);
      bcd_units     : out std_logic_vector (3 downto 0);
      bcd_tens     : out std_logic_vector (3 downto 0);
		bcd_hundreds : out std_logic_vector (3 downto 0)
 
   );
end Binary2BCD;
 

architecture Behavioral of Binary2BCD is
 
begin
 
   bin_to_bcd : process (input)
      -- Internal variable for storing bits
      variable shift : unsigned(19 downto 0);
      
	  -- Alias for parts of shift register
      alias num is shift(7 downto 0);
      alias one is shift(11 downto 8);
      alias ten is shift(15 downto 12);
      alias hun is shift(19 downto 16);
   begin
      -- Clear previous number and store new number in shift register
      num := unsigned(input);
      one := X"0";
      ten := X"0";
      hun := X"0";
      
	  -- Loop eight times
      for i in 1 to num'Length loop
	     -- Check if any digit is greater than or equal to 5
         if one >= 5 then
            one := one + 3;
         end if;
         
         if ten >= 5 then
            ten := ten + 3;
         end if;
         
         if hun >= 5 then
            hun := hun + 3;
         end if;
         
		 -- Shift entire register left once
         shift := shift_left(shift, 1);
      end loop;
      
	  -- Push decimal numbers to output
      bcd_hundreds <= std_logic_vector(hun);
      bcd_tens     <= std_logic_vector(ten);
      bcd_units     <= std_logic_vector(one);
   end process;
 
end Behavioral;