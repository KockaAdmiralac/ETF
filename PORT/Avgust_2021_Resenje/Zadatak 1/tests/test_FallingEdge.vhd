-- Quartus II VHDL Template
-- Binary Counter

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity test_FallingEdge is
	port (
		clk:		in std_logic;
		x:			out std_logic;
		y:			in std_logic;
		led:		out std_logic
	);
end entity;

architecture rtl of test_FallingEdge is
	signal   cnt: unsigned(13 downto 0) := (others => '0');
	signal	x_out: std_logic := '0';
	signal	led_next: std_logic := '1';
	signal	led_out: std_logic := '1';
	signal	state: std_logic_vector(1 downto 0) := (others => '0');
	signal	state_next: std_logic_vector(1 downto 0) := (others => '0');

	-- Because Modelsim is dumb.
	function u2slv(v: unsigned) return std_logic_vector is
	begin
		return std_logic_vector(v);
	end function;
begin

	process (clk)
		variable cnt_next: unsigned(13 downto 0) := (others => '0');
	begin
		if (rising_edge(clk)) then
			-- We skip first two ticks because Modelsim's SRFF output is undefined.
			if cnt = to_unsigned(0, cnt'length) then
				cnt <= to_unsigned(1, cnt'length);
			elsif cnt = to_unsigned(1, cnt'length) then
				cnt <= to_unsigned(2, cnt'length);
			else
				cnt <= cnt_next;
				led_out <= led_out and led_next;
			end if;
			state <= state_next;
			cnt_next := unsigned(u2slv(cnt * 1103515245 + 12345)(13 downto 0));
		end if;
	end process;
	
	process (y, x_out, state)
	begin
		state_next <= x_out & state(1);
		if y = (state(0) and not state(1)) then
			led_next <= '1';
		else
			led_next <= '0';
		end if;
	end process;
	
	x <= u2slv(cnt)(3);
	x_out <= u2slv(cnt)(3);
	
	led <= led_out;

end rtl;
