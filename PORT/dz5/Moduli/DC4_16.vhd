library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity DC4_16 is

	port 
	(
		I0	   : in std_logic;
		I1	   : in std_logic;
		I2	   : in std_logic;
		I3	   : in std_logic;
		EN		: in std_logic;
		
		D0  : out std_logic;
		D1  : out std_logic;
		D2  : out std_logic;
		D3  : out std_logic;
		D4  : out std_logic;
		D5  : out std_logic;
		D6  : out std_logic;
		D7  : out std_logic;
		D8  : out std_logic;
		D9  : out std_logic;
		D10 : out std_logic;
		D11 : out std_logic;
		D12 : out std_logic;
		D13 : out std_logic;
		D14 : out std_logic;
		D15 : out std_logic
	);

end entity;

architecture rtl of DC4_16 is
begin

	D0<=EN and not (I3) and not(I2) and not(I1) and not(I0);
	D1<=EN and not (I3) and not(I2) and not(I1) and    (I0);
	D2<=EN and not (I3) and not(I2) and    (I1) and not(I0);
	D3<=EN and not (I3) and not(I2) and    (I1) and    (I0);
	D4<=EN and not (I3) and    (I2) and not(I1) and not(I0);
	D5<=EN and not (I3) and    (I2) and not(I1) and    (I0);
	D6<=EN and not (I3) and    (I2) and    (I1) and not(I0);
	D7<=EN and not (I3) and    (I2) and    (I1) and    (I0);
	D8<=EN and     (I3) and not(I2) and not(I1) and not(I0);
	D9<=EN and     (I3) and not(I2) and not(I1) and    (I0);
	D10<=EN and     (I3) and not(I2) and    (I1) and not(I0);
	D11<=EN and     (I3) and not(I2) and    (I1) and    (I0);
	D12<=EN and     (I3) and    (I2) and not(I1) and not(I0);
	D13<=EN and     (I3) and    (I2) and not(I1) and    (I0);
	D14<=EN and     (I3) and    (I2) and    (I1) and not(I0);
	D15<=EN and     (I3) and    (I2) and    (I1) and    (I0);

end rtl;
