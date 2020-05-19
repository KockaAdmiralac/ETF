library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity CMP3 is

	port 
	(
		A	   : in std_logic_vector(2 downto 0);
		B	   : in std_logic_vector(2 downto 0);
		AgrB  : out std_logic;
		AeqB  : out std_logic;
		AloB  : out std_logic
	);

end entity;

architecture rtl of CMP3 is
begin
	process (A,B) is
	begin
		if unsigned(A)=unsigned(B) then
			AgrB<='0';
			AeqB<='1';
			AloB<='0';
		elsif unsigned(A)>unsigned(B) then
			AgrB<='1';
			AeqB<='0';
			AloB<='0';
		else
			AgrB<='0';
			AeqB<='0';
			AloB<='1';		
		end if;		
	end process;

end rtl;
