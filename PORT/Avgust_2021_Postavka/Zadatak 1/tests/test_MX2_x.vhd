library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity test_MX2_x is
	generic (
		size:			integer := 1;
		has_enable:	std_logic := '0'
	);
	port (
		clk:			in std_logic;
		i0:			out std_logic_vector(size-1 downto 0);
		i1:			out std_logic_vector(size-1 downto 0);
		s0:			out std_logic;
		e:				out std_logic;
		y:				in std_logic_vector(size-1 downto 0);
		led:			out std_logic
	);
end test_MX2_x;

architecture rtl of test_MX2_x is
	signal cnt:			unsigned(size*2+1 downto 0) := (others => '0');
	signal i0_out:		std_logic_vector(size-1 downto 0) := (others=>'0');
	signal i1_out:		std_logic_vector(size-1 downto 0) := (others=>'0');
	signal s0_out:		std_logic := '0';
	signal e_out:		std_logic := '0';
	signal led_next: 	std_logic := '1';
	signal led_out: 	std_logic := '1';

	-- Because Modelsim is dumb.
	function u2slv(v: unsigned) return std_logic_vector is
	begin
		return std_logic_vector(v);
	end function;
begin

	process (clk)
		variable cnt_next: unsigned(size*2+1 downto 0) := (others => '0');
		constant all_ones: std_logic_vector(size*2+1 downto 0) := (others => '1');
	begin
		if (rising_edge(clk)) then
			cnt <= cnt_next;
			led_out <= led_out and led_next;
			if unsigned(all_ones xor std_logic_vector(cnt_next)) /= 0 then
				cnt_next := cnt_next + 1;
			end if;
		end if;
	end process;
	
	process (y, i0_out, i1_out, s0_out, e_out) 
		variable res: std_logic_vector(size-1 downto 0);
	begin
		if (e_out = '0') and (has_enable = '1') then
			res := (others => '0');
		else
			if (s0_out = '1') then
				res := i1_out;
			else
				res := i0_out;
			end if;
			if (unsigned(y) = unsigned(res)) then
				led_next <= '1';
			else
				led_next <= '0';
			end if;
		end if;
	end process;
	
	i0_out <= u2slv(cnt)(size-1 downto 0);
	i1_out <= u2slv(cnt)(2*size-1 downto size);
	s0_out <= u2slv(cnt)(2*size);
	e_out <= u2slv(cnt)(2*size+1);
	
	i0 <= u2slv(cnt)(size-1 downto 0);
	i1 <= u2slv(cnt)(2*size-1 downto size);
	s0 <= u2slv(cnt)(2*size);
	e <= u2slv(cnt)(2*size+1);
	
	led <= led_out;

end rtl;
