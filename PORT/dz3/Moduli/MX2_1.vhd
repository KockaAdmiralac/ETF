library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity MX2_1 is
	port 
	(
		I1		: in std_logic_vector (6 downto 0);
		I0    : in std_logic_vector (6 downto 0);
		
		S0		: in std_logic;
		
		EN		: in std_logic;
		
		Y 		: out std_logic_vector (6 downto 0)
	);

end entity;

architecture rtl of MX2_1 is
begin
	process (I0,I1,S0, EN) is
	begin
	
		if EN='0' then
			Y <= (others=>'0');
		else
			if S0='0' then
				Y<=I0;
			else
				Y<=I1;
			end if;
		end if;
	end process;
end rtl;
