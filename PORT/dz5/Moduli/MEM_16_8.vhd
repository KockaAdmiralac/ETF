library ieee;
use ieee.std_logic_1164.all;

entity MEM_16_8 is

	port 
	(
		clk	: in std_logic;
		addr	: in natural range 0 to 15;
		data	: in std_logic_vector(7 downto 0);
		wr		: in std_logic := '0';
		cs		: in std_logic := '0';
		q		: out std_logic_vector(7 downto 0)
	);

end entity;

architecture rtl of MEM_16_8 is

	subtype word_t is std_logic_vector(7 downto 0);
	type memory_t is array(15 downto 0) of word_t;

	signal ram : memory_t;
	signal addr_reg : natural range 0 to 15;

begin

	process(clk)
	begin
	if(rising_edge(clk)) then
		if(wr = '1' and cs='1') then
			ram(addr) <= data;
		end if;

		addr_reg <= addr;
	end if;
	end process;

	process (cs,ram,addr_reg)
	begin
	if cs='1' then
		q <= ram(addr_reg);
	else
		q <= (others=>'Z');
	end if;
	end process;
end rtl;
