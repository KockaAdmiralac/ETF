-- Copyright (C) 1991-2013 Altera Corporation
-- Your use of Altera Corporation's design tools, logic functions 
-- and other software and tools, and its AMPP partner logic 
-- functions, and any output files from any of the foregoing 
-- (including device programming or simulation files), and any 
-- associated documentation or information are expressly subject 
-- to the terms and conditions of the Altera Program License 
-- Subscription Agreement, Altera MegaCore Function License 
-- Agreement, or other applicable license agreement, including, 
-- without limitation, that your use is for the sole purpose of 
-- programming logic devices manufactured by Altera and sold by 
-- Altera or its authorized distributors.  Please refer to the 
-- applicable agreement for further details.

-- PROGRAM		"Quartus II 32-bit"
-- VERSION		"Version 13.1.0 Build 162 10/23/2013 SJ Web Edition"
-- CREATED		"Sat Sep 04 23:58:44 2021"

LIBRARY ieee;
USE ieee.std_logic_1164.all; 

LIBRARY work;

ENTITY testing IS 
	PORT
	(
		clk :  IN  STD_LOGIC;
		led :  OUT  STD_LOGIC_VECTOR(6 DOWNTO 0)
	);
END testing;

ARCHITECTURE bdf_type OF testing IS 

COMPONENT cmp6
	PORT(A : IN STD_LOGIC_VECTOR(5 DOWNTO 0);
		 B : IN STD_LOGIC_VECTOR(5 DOWNTO 0);
		 G : OUT STD_LOGIC;
		 E : OUT STD_LOGIC;
		 L : OUT STD_LOGIC
	);
END COMPONENT;

COMPONENT test_cmp1
	PORT(clk : IN STD_LOGIC;
		 g : IN STD_LOGIC;
		 e : IN STD_LOGIC;
		 l : IN STD_LOGIC;
		 a : OUT STD_LOGIC;
		 b : OUT STD_LOGIC;
		 gi1 : OUT STD_LOGIC;
		 ei1 : OUT STD_LOGIC;
		 li1 : OUT STD_LOGIC;
		 led : OUT STD_LOGIC
	);
END COMPONENT;

COMPONENT test_mx4_x
GENERIC (has_enable : STD_LOGIC;
			size : INTEGER
			);
	PORT(clk : IN STD_LOGIC;
		 y : IN STD_LOGIC_VECTOR(5 DOWNTO 0);
		 s0 : OUT STD_LOGIC;
		 s1 : OUT STD_LOGIC;
		 e : OUT STD_LOGIC;
		 led : OUT STD_LOGIC;
		 i0 : OUT STD_LOGIC_VECTOR(5 DOWNTO 0);
		 i1 : OUT STD_LOGIC_VECTOR(5 DOWNTO 0);
		 i2 : OUT STD_LOGIC_VECTOR(5 DOWNTO 0);
		 i3 : OUT STD_LOGIC_VECTOR(5 DOWNTO 0)
	);
END COMPONENT;

COMPONENT mx4_6
	PORT(S0 : IN STD_LOGIC;
		 S1 : IN STD_LOGIC;
		 I0 : IN STD_LOGIC_VECTOR(5 DOWNTO 0);
		 I1 : IN STD_LOGIC_VECTOR(5 DOWNTO 0);
		 I2 : IN STD_LOGIC_VECTOR(5 DOWNTO 0);
		 I3 : IN STD_LOGIC_VECTOR(5 DOWNTO 0);
		 Y : OUT STD_LOGIC_VECTOR(5 DOWNTO 0)
	);
END COMPONENT;

COMPONENT fallingedge
	PORT(input : IN STD_LOGIC;
		 clk : IN STD_LOGIC;
		 output : OUT STD_LOGIC
	);
END COMPONENT;

COMPONENT test_fallingedge
	PORT(clk : IN STD_LOGIC;
		 y : IN STD_LOGIC;
		 x : OUT STD_LOGIC;
		 led : OUT STD_LOGIC
	);
END COMPONENT;

COMPONENT reg1_ld_sl_sr_cl
	PORT(LD : IN STD_LOGIC;
		 I : IN STD_LOGIC;
		 SL : IN STD_LOGIC;
		 IL : IN STD_LOGIC;
		 SR : IN STD_LOGIC;
		 IR : IN STD_LOGIC;
		 CL : IN STD_LOGIC;
		 clk : IN STD_LOGIC;
		 A : OUT STD_LOGIC
	);
END COMPONENT;

COMPONENT test_regx_ld_sl_sr_cl
GENERIC (size : INTEGER
			);
	PORT(clk : IN STD_LOGIC;
		 a : IN STD_LOGIC_VECTOR(size-1 DOWNTO 0);
		 ld : OUT STD_LOGIC;
		 sl : OUT STD_LOGIC;
		 il : OUT STD_LOGIC;
		 sr : OUT STD_LOGIC;
		 ir : OUT STD_LOGIC;
		 cl : OUT STD_LOGIC;
		 led : OUT STD_LOGIC;
		 i : OUT STD_LOGIC_VECTOR(size-1 DOWNTO 0)
	);
END COMPONENT;

COMPONENT reg6_ld_sl_sr_cl
	PORT(LD : IN STD_LOGIC;
		 SL : IN STD_LOGIC;
		 IL : IN STD_LOGIC;
		 SR : IN STD_LOGIC;
		 IR : IN STD_LOGIC;
		 CL : IN STD_LOGIC;
		 clk : IN STD_LOGIC;
		 I : IN STD_LOGIC_VECTOR(5 DOWNTO 0);
		 A : OUT STD_LOGIC_VECTOR(5 DOWNTO 0)
	);
END COMPONENT;

COMPONENT cmp1
	PORT(A : IN STD_LOGIC;
		 B : IN STD_LOGIC;
		 Gi1 : IN STD_LOGIC;
		 Ei1 : IN STD_LOGIC;
		 Li1 : IN STD_LOGIC;
		 G : OUT STD_LOGIC;
		 E : OUT STD_LOGIC;
		 L : OUT STD_LOGIC
	);
END COMPONENT;

COMPONENT test_cmpx
GENERIC (size : INTEGER
			);
	PORT(clk : IN STD_LOGIC;
		 g : IN STD_LOGIC;
		 e : IN STD_LOGIC;
		 l : IN STD_LOGIC;
		 led : OUT STD_LOGIC;
		 a : OUT STD_LOGIC_VECTOR(5 DOWNTO 0);
		 b : OUT STD_LOGIC_VECTOR(5 DOWNTO 0)
	);
END COMPONENT;

COMPONENT mx2_6
	PORT(S0 : IN STD_LOGIC;
		 I0 : IN STD_LOGIC_VECTOR(5 DOWNTO 0);
		 I1 : IN STD_LOGIC_VECTOR(5 DOWNTO 0);
		 Y : OUT STD_LOGIC_VECTOR(5 DOWNTO 0)
	);
END COMPONENT;

COMPONENT test_mx2_x
GENERIC (has_enable : STD_LOGIC;
			size : INTEGER
			);
	PORT(clk : IN STD_LOGIC;
		 y : IN STD_LOGIC_VECTOR(5 DOWNTO 0);
		 s0 : OUT STD_LOGIC;
		 e : OUT STD_LOGIC;
		 led : OUT STD_LOGIC;
		 i0 : OUT STD_LOGIC_VECTOR(5 DOWNTO 0);
		 i1 : OUT STD_LOGIC_VECTOR(5 DOWNTO 0)
	);
END COMPONENT;

SIGNAL	led_ALTERA_SYNTHESIZED :  STD_LOGIC_VECTOR(6 DOWNTO 0);
SIGNAL	SYNTHESIZED_WIRE_0 :  STD_LOGIC_VECTOR(5 DOWNTO 0);
SIGNAL	SYNTHESIZED_WIRE_1 :  STD_LOGIC_VECTOR(5 DOWNTO 0);
SIGNAL	SYNTHESIZED_WIRE_2 :  STD_LOGIC;
SIGNAL	SYNTHESIZED_WIRE_3 :  STD_LOGIC;
SIGNAL	SYNTHESIZED_WIRE_4 :  STD_LOGIC;
SIGNAL	SYNTHESIZED_WIRE_5 :  STD_LOGIC_VECTOR(5 DOWNTO 0);
SIGNAL	SYNTHESIZED_WIRE_6 :  STD_LOGIC;
SIGNAL	SYNTHESIZED_WIRE_7 :  STD_LOGIC;
SIGNAL	SYNTHESIZED_WIRE_8 :  STD_LOGIC_VECTOR(5 DOWNTO 0);
SIGNAL	SYNTHESIZED_WIRE_9 :  STD_LOGIC_VECTOR(5 DOWNTO 0);
SIGNAL	SYNTHESIZED_WIRE_10 :  STD_LOGIC_VECTOR(5 DOWNTO 0);
SIGNAL	SYNTHESIZED_WIRE_11 :  STD_LOGIC_VECTOR(5 DOWNTO 0);
SIGNAL	SYNTHESIZED_WIRE_12 :  STD_LOGIC;
SIGNAL	SYNTHESIZED_WIRE_13 :  STD_LOGIC;
SIGNAL	SYNTHESIZED_WIRE_14 :  STD_LOGIC;
SIGNAL	SYNTHESIZED_WIRE_15 :  STD_LOGIC;
SIGNAL	SYNTHESIZED_WIRE_16 :  STD_LOGIC;
SIGNAL	SYNTHESIZED_WIRE_17 :  STD_LOGIC;
SIGNAL	SYNTHESIZED_WIRE_18 :  STD_LOGIC;
SIGNAL	SYNTHESIZED_WIRE_19 :  STD_LOGIC;
SIGNAL	SYNTHESIZED_WIRE_20 :  STD_LOGIC;
SIGNAL	SYNTHESIZED_WIRE_21 :  STD_LOGIC_VECTOR(5 DOWNTO 0);
SIGNAL	SYNTHESIZED_WIRE_22 :  STD_LOGIC;
SIGNAL	SYNTHESIZED_WIRE_23 :  STD_LOGIC;
SIGNAL	SYNTHESIZED_WIRE_24 :  STD_LOGIC;
SIGNAL	SYNTHESIZED_WIRE_25 :  STD_LOGIC;
SIGNAL	SYNTHESIZED_WIRE_26 :  STD_LOGIC;
SIGNAL	SYNTHESIZED_WIRE_27 :  STD_LOGIC;
SIGNAL	SYNTHESIZED_WIRE_28 :  STD_LOGIC_VECTOR(5 DOWNTO 0);
SIGNAL	SYNTHESIZED_WIRE_29 :  STD_LOGIC;
SIGNAL	SYNTHESIZED_WIRE_30 :  STD_LOGIC;
SIGNAL	SYNTHESIZED_WIRE_31 :  STD_LOGIC;
SIGNAL	SYNTHESIZED_WIRE_32 :  STD_LOGIC;
SIGNAL	SYNTHESIZED_WIRE_33 :  STD_LOGIC;
SIGNAL	SYNTHESIZED_WIRE_34 :  STD_LOGIC;
SIGNAL	SYNTHESIZED_WIRE_35 :  STD_LOGIC;
SIGNAL	SYNTHESIZED_WIRE_36 :  STD_LOGIC;
SIGNAL	SYNTHESIZED_WIRE_37 :  STD_LOGIC;
SIGNAL	SYNTHESIZED_WIRE_38 :  STD_LOGIC_VECTOR(5 DOWNTO 0);
SIGNAL	SYNTHESIZED_WIRE_39 :  STD_LOGIC_VECTOR(5 DOWNTO 0);
SIGNAL	SYNTHESIZED_WIRE_40 :  STD_LOGIC;
SIGNAL	SYNTHESIZED_WIRE_41 :  STD_LOGIC_VECTOR(5 DOWNTO 0);


BEGIN 



b2v_inst : cmp6
PORT MAP(A => SYNTHESIZED_WIRE_0,
		 B => SYNTHESIZED_WIRE_1,
		 G => SYNTHESIZED_WIRE_34,
		 E => SYNTHESIZED_WIRE_35,
		 L => SYNTHESIZED_WIRE_36);


b2v_inst1 : test_cmp1
PORT MAP(clk => clk,
		 g => SYNTHESIZED_WIRE_2,
		 e => SYNTHESIZED_WIRE_3,
		 l => SYNTHESIZED_WIRE_4,
		 a => SYNTHESIZED_WIRE_29,
		 b => SYNTHESIZED_WIRE_30,
		 gi1 => SYNTHESIZED_WIRE_31,
		 ei1 => SYNTHESIZED_WIRE_32,
		 li1 => SYNTHESIZED_WIRE_33,
		 led => led_ALTERA_SYNTHESIZED(0));


b2v_inst10 : test_mx4_x
GENERIC MAP(has_enable => '0',
			size => 6
			)
PORT MAP(clk => clk,
		 y => SYNTHESIZED_WIRE_5,
		 s0 => SYNTHESIZED_WIRE_6,
		 s1 => SYNTHESIZED_WIRE_7,
		 led => led_ALTERA_SYNTHESIZED(3),
		 i0 => SYNTHESIZED_WIRE_8,
		 i1 => SYNTHESIZED_WIRE_9,
		 i2 => SYNTHESIZED_WIRE_10,
		 i3 => SYNTHESIZED_WIRE_11);


b2v_inst11 : mx4_6
PORT MAP(S0 => SYNTHESIZED_WIRE_6,
		 S1 => SYNTHESIZED_WIRE_7,
		 I0 => SYNTHESIZED_WIRE_8,
		 I1 => SYNTHESIZED_WIRE_9,
		 I2 => SYNTHESIZED_WIRE_10,
		 I3 => SYNTHESIZED_WIRE_11,
		 Y => SYNTHESIZED_WIRE_5);


b2v_inst12 : fallingedge
PORT MAP(input => SYNTHESIZED_WIRE_12,
		 clk => clk,
		 output => SYNTHESIZED_WIRE_13);


b2v_inst13 : test_fallingedge
PORT MAP(clk => clk,
		 y => SYNTHESIZED_WIRE_13,
		 x => SYNTHESIZED_WIRE_12,
		 led => led_ALTERA_SYNTHESIZED(4));


b2v_inst14 : reg1_ld_sl_sr_cl
PORT MAP(LD => SYNTHESIZED_WIRE_14,
		 I => SYNTHESIZED_WIRE_15,
		 SL => SYNTHESIZED_WIRE_16,
		 IL => SYNTHESIZED_WIRE_17,
		 SR => SYNTHESIZED_WIRE_18,
		 IR => SYNTHESIZED_WIRE_19,
		 CL => SYNTHESIZED_WIRE_20,
		 clk => clk,
		 A => SYNTHESIZED_WIRE_40);


b2v_inst15 : test_regx_ld_sl_sr_cl
GENERIC MAP(size => 6
			)
PORT MAP(clk => clk,
		 a => SYNTHESIZED_WIRE_21,
		 ld => SYNTHESIZED_WIRE_22,
		 sl => SYNTHESIZED_WIRE_23,
		 il => SYNTHESIZED_WIRE_24,
		 sr => SYNTHESIZED_WIRE_25,
		 ir => SYNTHESIZED_WIRE_26,
		 cl => SYNTHESIZED_WIRE_27,
		 led => led_ALTERA_SYNTHESIZED(6),
		 i => SYNTHESIZED_WIRE_28);


b2v_inst16 : reg6_ld_sl_sr_cl
PORT MAP(LD => SYNTHESIZED_WIRE_22,
		 SL => SYNTHESIZED_WIRE_23,
		 IL => SYNTHESIZED_WIRE_24,
		 SR => SYNTHESIZED_WIRE_25,
		 IR => SYNTHESIZED_WIRE_26,
		 CL => SYNTHESIZED_WIRE_27,
		 clk => clk,
		 I => SYNTHESIZED_WIRE_28,
		 A => SYNTHESIZED_WIRE_21);


b2v_inst2 : cmp1
PORT MAP(A => SYNTHESIZED_WIRE_29,
		 B => SYNTHESIZED_WIRE_30,
		 Gi1 => SYNTHESIZED_WIRE_31,
		 Ei1 => SYNTHESIZED_WIRE_32,
		 Li1 => SYNTHESIZED_WIRE_33,
		 G => SYNTHESIZED_WIRE_2,
		 E => SYNTHESIZED_WIRE_3,
		 L => SYNTHESIZED_WIRE_4);


b2v_inst3 : test_cmpx
GENERIC MAP(size => 6
			)
PORT MAP(clk => clk,
		 g => SYNTHESIZED_WIRE_34,
		 e => SYNTHESIZED_WIRE_35,
		 l => SYNTHESIZED_WIRE_36,
		 led => led_ALTERA_SYNTHESIZED(1),
		 a => SYNTHESIZED_WIRE_0,
		 b => SYNTHESIZED_WIRE_1);


b2v_inst7 : mx2_6
PORT MAP(S0 => SYNTHESIZED_WIRE_37,
		 I0 => SYNTHESIZED_WIRE_38,
		 I1 => SYNTHESIZED_WIRE_39,
		 Y => SYNTHESIZED_WIRE_41);


b2v_inst8 : test_regx_ld_sl_sr_cl
GENERIC MAP(size => 1
			)
PORT MAP(clk => clk,
		 a(0) => SYNTHESIZED_WIRE_40,
		 ld => SYNTHESIZED_WIRE_14,
		 sl => SYNTHESIZED_WIRE_16,
		 il => SYNTHESIZED_WIRE_17,
		 sr => SYNTHESIZED_WIRE_18,
		 ir => SYNTHESIZED_WIRE_19,
		 cl => SYNTHESIZED_WIRE_20,
		 led => led_ALTERA_SYNTHESIZED(5),
		 i(0) => SYNTHESIZED_WIRE_15);


b2v_inst9 : test_mx2_x
GENERIC MAP(has_enable => '0',
			size => 6
			)
PORT MAP(clk => clk,
		 y => SYNTHESIZED_WIRE_41,
		 s0 => SYNTHESIZED_WIRE_37,
		 led => led_ALTERA_SYNTHESIZED(2),
		 i0 => SYNTHESIZED_WIRE_38,
		 i1 => SYNTHESIZED_WIRE_39);

led <= led_ALTERA_SYNTHESIZED;

END bdf_type;