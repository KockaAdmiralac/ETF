library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity MX4_1 is
	port 
	(
		I3	   : in std_logic_vector (6 downto 0);
		I2	   : in std_logic_vector (6 downto 0);
		I1		: in std_logic_vector (6 downto 0);
		I0    : in std_logic_vector (6 downto 0);
		
		S1		: in std_logic;
		S0		: in std_logic;
		
		EN		: in std_logic;
		
		Y 		: out std_logic_vector (6 downto 0)
	);

end entity;

architecture rtl of MX4_1 is
begin
	process (I0,I1,I2,I3,S1,S0, EN) is
	variable tmp : std_logic_vector(1 downto 0);
	begin
		tmp(1 downto 0):=S1&S0;
		if EN='0' then
			Y <= (others=>'0');
		else
			case tmp is
				when "00" =>   Y <= I0;
				when "01" =>   Y <= I1;
				when "10" =>   Y <= I2;
				when "11" =>   Y <= I3;
				when others => Y <= (others=>'0');
			end case;
		end if;
	end process;
end rtl;
