library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.math_real.all;

package porttest is
component testing is
	port
	(
		clk: in std_logic;
		led: out std_logic_vector(6 downto 0)
	);
end component;

end package;

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.math_real.all;
use work.porttest.all;

entity testbench is
end testbench;

architecture testbench of testbench is
	signal clk: std_logic := '0';
	signal led: std_logic_vector(6 downto 0) := (others => '0');
	constant clk_period: time := 10 ns;
begin
	t:testing port map(clk, led);
	process
	begin
		clk <= '0';
		wait for clk_period/2;
		clk <= '1';
		wait for clk_period/2;
	end process;
end testbench;
