library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity test_CMPx is
	generic (
		size:		integer := 6
	);
	port (
		clk:		in std_logic;
		a:			out std_logic_vector(size-1 downto 0);
		b:			out std_logic_vector(size-1 downto 0);
		g:			in std_logic;
		e:			in std_logic;
		l:			in std_logic;
		led:		out std_logic
	);
end test_CMPx;

architecture rtl of test_CMPx is
	signal cnt: unsigned(size*2-1 downto 0) := (others => '0');
	signal a_out: std_logic_vector(size-1 downto 0) := (others => '0');
	signal b_out: std_logic_vector(size-1 downto 0) := (others => '0');
	signal led_out: std_logic := '1';
	signal led_next: std_logic := '1';

	-- Because Modelsim is dumb.
	function u2slv(v: unsigned) return std_logic_vector is
	begin
		return std_logic_vector(v);
	end function;
begin

	process (clk)
		variable cnt_next: unsigned(size*2-1 downto 0) := (others => '0');
		constant all_ones: std_logic_vector(size*2-1 downto 0) := (others => '1');
	begin
		if (rising_edge(clk)) then
			cnt <= cnt_next;
			led_out <= led_out and led_next;
			if unsigned(all_ones xor std_logic_vector(cnt_next)) /= 0 then
				cnt_next := cnt_next + 1;
			end if;
		end if;
	end process;

	process (g, e, l, a_out, b_out)
		variable res_g, res_e, res_l: std_logic;
	begin
		res_g := '0';
		res_e := '0';
		res_l := '0';
		if (unsigned(a_out) < unsigned(b_out)) then
			res_l := '1';
		end if;
		if (unsigned(a_out) > unsigned(b_out)) then
			res_g := '1';
		end if;
		if (unsigned(a_out) = unsigned(b_out)) then
			res_e := '1';
		end if;
		
		if ((g = res_g) and (e = res_e) and (l = res_l)) then
			led_next <= '1';
		else
			led_next <= '0';
		end if;
	end process;
	
	a_out <= u2slv(cnt)(size-1 downto 0);
	b_out <= u2slv(cnt)(size*2-1 downto size);
	
	a <= u2slv(cnt)(size-1 downto 0);
	b <= u2slv(cnt)(size*2-1 downto size);

	led <= led_out;

end rtl;
