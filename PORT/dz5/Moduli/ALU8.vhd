library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity ALU8 is

	port 
	(
		A	   : in std_logic_vector  (7 downto 0);
		B	   : in std_logic_vector  (7 downto 0);
		Cin   : in std_logic;
		S0		: in std_logic;
		S1		: in std_logic;
		F		: out std_logic_vector (7 downto 0);
		Cout  : out std_logic
	);

end entity;

architecture rtl of ALU8 is
	
begin

	process (A,B,S1,S0,Cin) is
		variable varA,varB,varF: std_logic_vector (8 downto 0);
		variable op:std_logic_vector(2	downto 0);
	begin
			varA(8 downto 0):=A(7)&A(7 downto 0);
			varB(8 downto 0):=B(7)&B(7 downto 0);
			op:=S1 & S0 & Cin;
			case op is
				when "000" => varF := std_logic_vector(unsigned(varA)-unsigned(varB));
				when "001" => varF := std_logic_vector(unsigned(varA)-unsigned(varB));
				when "010" => varF := std_logic_vector(unsigned(varA)+unsigned(varB));
				when "011" => varF := std_logic_vector(unsigned(varA)+unsigned(varB));
				when "100" => varF := std_logic_vector(unsigned(varA));
				when "101" => varF := std_logic_vector(unsigned(varA)+1);
				when "110" => varF := std_logic_vector(unsigned(varA) and unsigned(varB));
				when "111" => varF := std_logic_vector(unsigned(varA) and unsigned(varB));
			end case;
			F(7 downto 0)<=varF(7 downto 0);
			Cout <=varF(8);
	end process;



end rtl;
