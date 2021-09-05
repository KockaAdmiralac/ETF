library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity test_REGx_LD_SL_SR_CL is
	generic (
		size:			integer := 1
	);
	port (
		clk:			in std_logic;
		ld:			out std_logic;
		i:				out std_logic_vector(size-1 downto 0);
		sl:			out std_logic;
		il:			out std_logic;
		sr:			out std_logic;
		ir:			out std_logic;
		cl:			out std_logic;
		a:				in std_logic_vector(size-1 downto 0);
		led:			out std_logic
	);
end entity;

architecture rtl of test_REGx_LD_SL_SR_CL is
	signal cnt:				unsigned(size+5 downto 0) := (others => '0');
	signal ld_out:			std_logic := '0';
	signal i_out:			std_logic_vector(size-1 downto 0) := (others => '0');
	signal sl_out:			std_logic := '0';
	signal il_out:			std_logic := '0';
	signal sr_out:			std_logic := '0';
	signal ir_out:			std_logic := '0';
	signal cl_out:			std_logic := '0';
	signal led_next: 		std_logic := '1';
	signal led_out: 		std_logic := '1';
	signal state:			std_logic_vector(size-1 downto 0) := (others => '0');
	signal state_next:	std_logic_vector(size-1 downto 0) := (others => '0');

	-- Because Modelsim is dumb.
	function u2slv(v: unsigned) return std_logic_vector is
	begin
		return std_logic_vector(v);
	end function;
begin

	process (clk)
		variable cnt_next: unsigned(size+5 downto 0) := (others => '0');
	begin
		if (rising_edge(clk)) then
			-- We skip first two ticks because Modelsim's flip-flop output is undefined.
			if cnt = to_unsigned(0, cnt'length) then
				-- Here, we INTENTIONALLY enable CL so the flip-flop output is no longer undefined.
				cnt <= to_unsigned(1, cnt'length);
			elsif cnt = to_unsigned(1, cnt'length) then
				cnt <= to_unsigned(2, cnt'length);
			else
				cnt <= cnt_next;
				led_out <= led_out and led_next;
			end if;
			state <= state_next;
			cnt_next := unsigned(u2slv(cnt * 1103515245 + 12345)(size+5 downto 0));
		end if;
	end process;
	
	process (a, state, ld_out, i_out, sl_out, il_out, sr_out, ir_out, cl_out) 
	begin
		if ld_out = '1' then
			state_next <= i_out;
		elsif sl_out = '1' then
			if size = 1 then
				state_next(0) <= il_out;
			else
				state_next <= state(size-2 downto 0) & il_out;
			end if;
		elsif sr_out = '1' then
			if size = 1 then
				state_next(0) <= ir_out;
			else
				state_next <= ir_out & state(size-1 downto 1);
			end if;
		elsif cl_out = '1' then
			state_next <= (others => '0');
		else
			state_next <= state;
		end if;
		
		if unsigned(a) = unsigned(state) then
			led_next <= '1';
		else
			led_next <= '0';
		end if;
	end process;

	ld_out <= u2slv(cnt)(size+5);
	i_out <= u2slv(cnt)(size+4 downto 5);
	sl_out <= u2slv(cnt)(4);
	il_out <= u2slv(cnt)(3);
	sr_out <= u2slv(cnt)(2);
	ir_out <= u2slv(cnt)(1);
	cl_out <= u2slv(cnt)(0);

	ld <= u2slv(cnt)(size+5);
	i <= u2slv(cnt)(size+4 downto 5);
	sl <= u2slv(cnt)(4);
	il <= u2slv(cnt)(3);
	sr <= u2slv(cnt)(2);
	ir <= u2slv(cnt)(1);
	cl <= u2slv(cnt)(0);
	
	led <= led_out;

end rtl;
