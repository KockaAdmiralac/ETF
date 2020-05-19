library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity SevenSegmentInterfaceDEC is
	port
	(
		-- Input ports
		x	: in std_logic_vector(3 downto 0);
		dot: in std_logic;
		en : in std_logic;

		-- Output ports
		a	: out std_logic;
		b	: out std_logic;
		c	: out std_logic;
		d	: out std_logic;
		e	: out std_logic;
		f	: out std_logic;
		g	: out std_logic;
		dp: out std_logic
	);
end;

architecture rtl of SevenSegmentInterfaceDEC is
	 signal bcat : std_logic_vector(4 downto 0);
begin
   bcat <= en & x(3) & x(2) & x(1) & x(0);

	process (bcat,dot) is
	begin
		case bcat is
			when "10000" => a <= '0'; b <= '0'; c <= '0'; d <= '0'; e <= '0'; f <= '0'; g <= '1';
			when "10001" => a <= '1'; b <= '0'; c <= '0'; d <= '1'; e <= '1'; f <= '1'; g <= '1';
			when "10010" => a <= '0'; b <= '0'; c <= '1'; d <= '0'; e <= '0'; f <= '1'; g <= '0';
			when "10011" => a <= '0'; b <= '0'; c <= '0'; d <= '0'; e <= '1'; f <= '1'; g <= '0';
			when "10100" => a <= '1'; b <= '0'; c <= '0'; d <= '1'; e <= '1'; f <= '0'; g <= '0';
			when "10101" => a <= '0'; b <= '1'; c <= '0'; d <= '0'; e <= '1'; f <= '0'; g <= '0';
			when "10110" => a <= '0'; b <= '1'; c <= '0'; d <= '0'; e <= '0'; f <= '0'; g <= '0';
			when "10111" => a <= '0'; b <= '0'; c <= '0'; d <= '1'; e <= '1'; f <= '1'; g <= '1';
			when "11000" => a <= '0'; b <= '0'; c <= '0'; d <= '0'; e <= '0'; f <= '0'; g <= '0';
			when "11001" => a <= '0'; b <= '0'; c <= '0'; d <= '0'; e <= '1'; f <= '0'; g <= '0';
			when others  => a <= '0'; b <= '1'; c <= '1'; d <= '0'; e <= '0'; f <= '0'; g <= '0';
	  end case;
	end process;
	
	dp<=not (en and dot);

end;

