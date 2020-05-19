library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity Number is
	port
	(
		up		  : in std_logic;
		down		  : in std_logic;
		rst		  : in std_logic;
		number	  : out std_logic_vector(4 downto 0);
		clk		  : in std_logic
	);

end entity;

architecture rtl of Number is
	signal v : std_logic_vector(4 downto 0):="00000";
begin

process (clk)
	begin
		if (rising_edge(clk)) then
			if (rst='1') then
				v<=(others=>'0');
			elsif (up ='1') then
				v<= std_logic_vector( unsigned(v) + 1 );
			elsif (down ='1') then
				v<= std_logic_vector( unsigned(v) - 1 );
			end if;
			
		end if;
	end process;

	number <= v;
	
end rtl;
