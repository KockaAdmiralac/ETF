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
-- CREATED		"Fri Sep 03 23:46:59 2021"

LIBRARY ieee;
USE ieee.std_logic_1164.all; 

LIBRARY work;

ENTITY MX2_6 IS 
	PORT
	(
		S0 :  IN  STD_LOGIC;
		I0 :  IN  STD_LOGIC_VECTOR(5 DOWNTO 0);
		I1 :  IN  STD_LOGIC_VECTOR(5 DOWNTO 0);
		Y :  OUT  STD_LOGIC_VECTOR(5 DOWNTO 0)
	);
END MX2_6;

ARCHITECTURE bdf_type OF MX2_6 IS 

SIGNAL	SYNTHESIZED_WIRE_0 :  STD_LOGIC;
SIGNAL	SYNTHESIZED_WIRE_1 :  STD_LOGIC_VECTOR(5 DOWNTO 0);
SIGNAL	SYNTHESIZED_WIRE_2 :  STD_LOGIC_VECTOR(5 DOWNTO 0);


BEGIN 



SYNTHESIZED_WIRE_2 <= (S0 & S0 & S0 & S0 & S0 & S0) AND I1;


SYNTHESIZED_WIRE_1 <= I0 AND (SYNTHESIZED_WIRE_0 & SYNTHESIZED_WIRE_0 & SYNTHESIZED_WIRE_0 & SYNTHESIZED_WIRE_0 & SYNTHESIZED_WIRE_0 & SYNTHESIZED_WIRE_0);


SYNTHESIZED_WIRE_0 <= NOT(S0);



Y <= SYNTHESIZED_WIRE_1 OR SYNTHESIZED_WIRE_2;


END bdf_type;