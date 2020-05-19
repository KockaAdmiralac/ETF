library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity REG8 is
	port 
	(
		clk		: in std_logic;
		ld	      : in std_logic;
		input		: in std_logic_vector(7 downto 0);
		sr			: in std_logic;
		ir			: in std_logic;
		sl			: in std_logic;
		il			: in std_logic;
		inc		: in std_logic;
		dec		: in std_logic;
		cl			: in std_logic;
		output	: out std_logic_vector(7 downto 0)
	);

end entity;

architecture rtl of REG8 is
	signal v : std_logic_vector(7 downto 0):="00000000";
begin

	process (clk)
	begin
		if (rising_edge(clk)) then
			if (cl='1') then
				v<=(others=>'0');
			elsif (ld ='1') then
				v<= input;
			elsif (sr ='1') then
				v<= ir&v(7 downto 1);
			elsif (sl ='1') then
				v<= v(6 downto 0)&il;
			elsif (inc ='1') then
				v<= std_logic_vector( unsigned(v) + 1 );
			elsif (dec ='1') then
				v<= std_logic_vector( unsigned(v) - 1 );
			end if;
			
		end if;
	end process;

	output <= v;

end rtl;
