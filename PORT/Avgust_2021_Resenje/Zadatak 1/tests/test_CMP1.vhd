library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity test_CMP1 is
port (
	clk:		in std_logic;
	a:			out std_logic;
	b:			out std_logic;
	gi1:		out std_logic;
	ei1:		out std_logic;
	li1:		out std_logic;
	g:			in std_logic;
	e:			in std_logic;
	l:			in std_logic;
	led:		out std_logic
);
end test_CMP1;

architecture rtl of test_CMP1 is
	signal cnt: integer range 0 to 31 := 0;
	signal a_out: std_logic := '0';
	signal b_out: std_logic := '0';
	signal gi1_out: std_logic := '0';
	signal ei1_out: std_logic := '0';
	signal li1_out: std_logic := '0';
	signal led_out: std_logic := '1';
	signal led_next: std_logic := '1';
begin

	process (clk)
		variable cnt_next: integer range 0 to 31;
	begin
		if (rising_edge(clk)) then
			cnt <= cnt_next;
			led_out <= led_out and led_next;
			if (cnt_next < 31) then
				cnt_next := cnt_next + 1;
			end if;
		end if;
	end process;

	process (g, e, l, a_out, b_out, gi1_out, ei1_out, li1_out)
		variable res_g, res_e, res_l: std_logic;
	begin
		res_g := '0';
		res_e := '0';
		res_l := '0';
		if (a_out < b_out) then
			res_l := '1';
		end if;
		if (a_out > b_out) then
			res_g := '1';
		end if;
		if (a_out = b_out) then
			if (gi1_out = '1') then
				res_g := '1';
			end if;
			if (ei1_out = '1') then
				res_e := '1';
			end if;
			if (li1_out = '1') then
				res_l := '1';
			end if;
		end if;
		
		if (
			(((gi1_out = '1') and (ei1_out = '1')) or ((ei1_out = '1') and (li1_out = '1')) or ((li1_out = '1') and (gi1_out = '1'))) or
			((g = res_g) and (e = res_e) and (l = res_l))
		) then
			led_next <= '1';
		else
			led_next <= '0';
		end if;
	end process;
	
	a_out <= to_unsigned(cnt, 5)(0);
	b_out <= to_unsigned(cnt, 5)(1);
	gi1_out <= to_unsigned(cnt, 5)(2);
	ei1_out <= to_unsigned(cnt, 5)(3);
	li1_out <= to_unsigned(cnt, 5)(4);
	
	a <= to_unsigned(cnt, 5)(0);
	b <= to_unsigned(cnt, 5)(1);
	gi1 <= to_unsigned(cnt, 5)(2);
	ei1 <= to_unsigned(cnt, 5)(3);
	li1 <= to_unsigned(cnt, 5)(4);

	led <= led_out;

end rtl;
