library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity RandomGenerator is
	port
	(
		NXT  	   : in std_logic;
		RST	  	: in std_logic;
		CLK		: in std_logic;
		
		Z2		  	: out std_logic;
		Z1		  	: out std_logic;
		Z0		  	: out std_logic
	);

end entity;

architecture rtl of RandomGenerator is
	signal   v        : integer range 0 to 7;
 
begin

	process (CLK)
	variable   v_next   : integer range 0 to 7;  	
	begin
 
		if (rising_edge(CLK)) then
		   	v_next := v;
		  if (RST='0' AND NXT='1') then
			case v is
              when 0      => v_next := 2;
              when 1      => v_next := 0;
              when 2      => v_next := 5;
              when 3      => v_next := 4;
              when 4      => v_next := 6;
              when 5      => v_next := 3;
              when 6      => v_next := 7;
              when 7      => v_next := 1;
       		 end case;
			elsif (RST='1' AND NXT='0') then
				v_next:= 0;
         end if;
            v<=v_next;
		end if;
     
	end process;

	 Z2 <= to_unsigned(v,3)(2);
	 Z1 <= to_unsigned(v,3)(1);
	 Z0 <= to_unsigned(v,3)(0);

end rtl;