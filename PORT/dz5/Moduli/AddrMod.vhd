library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity AddrMod is
	port 
	(
		wr	   : in std_logic;
		rst   : in std_logic;
		clk	: in std_logic;
		addrWr: out std_logic_vector(3 downto 0);
		cnt	: out std_logic_vector(4 downto 0)
	);

end entity;

architecture rtl of AddrMod is
	signal vAddr : std_logic_vector(3 downto 0):="0000";
	signal vCnt : std_logic_vector(4 downto 0):="00000";
begin

	process (clk)
	begin
		if (rising_edge(clk)) then
			if (rst='1') then
				vAddr<=(others=>'0');
				vCnt<=(others=>'0');
			elsif (wr ='1') then
				vAddr <= std_logic_vector(unsigned(vAddr) + 1);
				if(unsigned(vCnt) < 16) then
					vCnt <= std_logic_vector(unsigned(vCnt) + 1);
				end if;
			end if;
		end if;
	end process;

	addrWr <= vAddr;
	cnt <= vCnt;
end rtl;
