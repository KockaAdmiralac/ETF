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
-- CREATED		"Sat Sep 04 23:18:10 2021"

LIBRARY ieee;
USE ieee.std_logic_1164.all; 

LIBRARY work;

ENTITY REG1_LD_SL_SR_CL IS 
	PORT
	(
		CL :  IN  STD_LOGIC;
		clk :  IN  STD_LOGIC;
		LD :  IN  STD_LOGIC;
		SL :  IN  STD_LOGIC;
		IL :  IN  STD_LOGIC;
		SR :  IN  STD_LOGIC;
		IR :  IN  STD_LOGIC;
		I :  IN  STD_LOGIC;
		A :  OUT  STD_LOGIC
	);
END REG1_LD_SL_SR_CL;

ARCHITECTURE bdf_type OF REG1_LD_SL_SR_CL IS 

SIGNAL	A_ALTERA_SYNTHESIZED :  STD_LOGIC;
SIGNAL	D :  STD_LOGIC;
SIGNAL	notCL :  STD_LOGIC;
SIGNAL	notLD :  STD_LOGIC;
SIGNAL	notSL :  STD_LOGIC;
SIGNAL	notSR :  STD_LOGIC;
SIGNAL	one :  STD_LOGIC;
SIGNAL	SYNTHESIZED_WIRE_0 :  STD_LOGIC;
SIGNAL	SYNTHESIZED_WIRE_1 :  STD_LOGIC;
SIGNAL	SYNTHESIZED_WIRE_2 :  STD_LOGIC;
SIGNAL	SYNTHESIZED_WIRE_3 :  STD_LOGIC;


BEGIN 



PROCESS(clk)
BEGIN
IF (RISING_EDGE(clk)) THEN
	A_ALTERA_SYNTHESIZED <= D;
END IF;
END PROCESS;


SYNTHESIZED_WIRE_0 <= LD AND I;


notCL <= NOT(CL);



notLD <= NOT(LD);



notSL <= NOT(SL);



notSR <= NOT(SR);



D <= SYNTHESIZED_WIRE_0 OR SYNTHESIZED_WIRE_1 OR SYNTHESIZED_WIRE_2 OR SYNTHESIZED_WIRE_3;


SYNTHESIZED_WIRE_3 <= SL AND notLD AND IL;


SYNTHESIZED_WIRE_1 <= SR AND IR AND notLD AND notSL;


SYNTHESIZED_WIRE_2 <= notSR AND notLD AND notSL AND notCL AND A_ALTERA_SYNTHESIZED AND one;


A <= A_ALTERA_SYNTHESIZED;

one <= '1';
END bdf_type;