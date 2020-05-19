library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity ADD7 is

	port 
	(
		A	   : in std_logic_vector  (6 downto 0);
		B	   : in std_logic_vector  (6 downto 0);
		Cin   : in std_logic;
		F		: out std_logic_vector (6 downto 0);
		Cout  : out std_logic
	);

end entity;

architecture rtl of ADD7 is
	
begin

	process (A,B,Cin) is
		variable varA,varB,varF: std_logic_vector (7 downto 0);
	begin
			varA(7 downto 0):=A(6)&A(6 downto 0);
			varB(7 downto 0):=B(6)&B(6 downto 0);
			if Cin='1' then
				varF := std_logic_vector(unsigned(varA)+unsigned(varB)+1);
			else
				varF := std_logic_vector(unsigned(varA)+unsigned(varB));
			end if;

			F(6 downto 0)<=varF(6 downto 0);
			Cout <=varF(7);
			
	end process;



end rtl;
