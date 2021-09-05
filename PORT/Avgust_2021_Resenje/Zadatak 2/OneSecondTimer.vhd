library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity OneSecondTimer is
port (
	clk:		in std_logic;
	output: 	out std_logic
);
end OneSecondTimer;

architecture rtl of OneSecondTimer is
	signal cnt: integer range 0 to 50000000 := 0;
begin

	process (clk)
		variable cnt_next: integer range 0 to 50000000 := 0;
	begin
		if (rising_edge(clk)) then
			cnt <= cnt_next;
			if cnt = 50000000 then
				cnt <= 0;
				cnt_next := 1;
				output <= '0';
			else
				cnt_next := cnt_next + 1;
				output <= '1';
			end if;
		end if;
	end process;

end rtl;
