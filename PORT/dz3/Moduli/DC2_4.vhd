library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity DC2_4 is

	port 
	(
		I0	   : in std_logic;
		I1	   : in std_logic;
		EN		: in std_logic;
		
		D0 : out std_logic;
		D1 : out std_logic;
		D2 : out std_logic;
		D3 : out std_logic
	);

end entity;

architecture rtl of DC2_4 is
begin

	D0<=EN and not(I1) and not(I0);
	D1<=EN and not(I1) and (I0);
	D2<=EN and (I1) and not(I0);
	D3<=EN and (I1) and (I0);

end rtl;
