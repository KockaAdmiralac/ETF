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
-- CREATED		"Sun Sep 05 16:07:05 2021"

LIBRARY ieee;
USE ieee.std_logic_1164.all; 

LIBRARY work;

ENTITY REG6_LD_SL_SR_CL IS 
	PORT
	(
		CL :  IN  STD_LOGIC;
		clk :  IN  STD_LOGIC;
		LD :  IN  STD_LOGIC;
		SL :  IN  STD_LOGIC;
		IL :  IN  STD_LOGIC;
		SR :  IN  STD_LOGIC;
		IR :  IN  STD_LOGIC;
		I :  IN  STD_LOGIC_VECTOR(5 DOWNTO 0);
		A :  OUT  STD_LOGIC_VECTOR(5 DOWNTO 0)
	);
END REG6_LD_SL_SR_CL;

ARCHITECTURE bdf_type OF REG6_LD_SL_SR_CL IS 

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

SIGNAL	A_ALTERA_SYNTHESIZED :  STD_LOGIC_VECTOR(5 DOWNTO 0);


BEGIN 



b2v_inst : reg1_ld_sl_sr_cl
PORT MAP(LD => LD,
		 I => I(0),
		 SL => SL,
		 IL => IL,
		 SR => SR,
		 IR => A_ALTERA_SYNTHESIZED(1),
		 CL => CL,
		 clk => clk,
		 A => A_ALTERA_SYNTHESIZED(0));


b2v_inst1 : reg1_ld_sl_sr_cl
PORT MAP(LD => LD,
		 I => I(1),
		 SL => SL,
		 IL => A_ALTERA_SYNTHESIZED(0),
		 SR => SR,
		 IR => A_ALTERA_SYNTHESIZED(2),
		 CL => CL,
		 clk => clk,
		 A => A_ALTERA_SYNTHESIZED(1));


b2v_inst2 : reg1_ld_sl_sr_cl
PORT MAP(LD => LD,
		 I => I(2),
		 SL => SL,
		 IL => A_ALTERA_SYNTHESIZED(1),
		 SR => SR,
		 IR => A_ALTERA_SYNTHESIZED(3),
		 CL => CL,
		 clk => clk,
		 A => A_ALTERA_SYNTHESIZED(2));


b2v_inst3 : reg1_ld_sl_sr_cl
PORT MAP(LD => LD,
		 I => I(3),
		 SL => SL,
		 IL => A_ALTERA_SYNTHESIZED(2),
		 SR => SR,
		 IR => A_ALTERA_SYNTHESIZED(4),
		 CL => CL,
		 clk => clk,
		 A => A_ALTERA_SYNTHESIZED(3));


b2v_inst4 : reg1_ld_sl_sr_cl
PORT MAP(LD => LD,
		 I => I(4),
		 SL => SL,
		 IL => A_ALTERA_SYNTHESIZED(3),
		 SR => SR,
		 IR => A_ALTERA_SYNTHESIZED(5),
		 CL => CL,
		 clk => clk,
		 A => A_ALTERA_SYNTHESIZED(4));


b2v_inst5 : reg1_ld_sl_sr_cl
PORT MAP(LD => LD,
		 I => I(5),
		 SL => SL,
		 IL => A_ALTERA_SYNTHESIZED(4),
		 SR => SR,
		 IR => IR,
		 CL => CL,
		 clk => clk,
		 A => A_ALTERA_SYNTHESIZED(5));

A <= A_ALTERA_SYNTHESIZED;

END bdf_type;