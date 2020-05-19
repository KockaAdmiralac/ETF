library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity CD4_2 is

	port 
	(
		C0 : in std_logic;
		C1 : in std_logic;
		C2 : in std_logic;
		C3 : in std_logic;
	
		Z0	   : out std_logic;
		Z1	   : out std_logic;
		
		W		: out std_logic;
		
		EN		: in std_logic
		
	);

end entity;

architecture rtl of CD4_2 is
begin

	Z0<=EN and (C3 or C1);
	Z1<=EN and (C3 or C2);
	W <=EN and (C0 or C1 or C2 or C3);

end rtl;
