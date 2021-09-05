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
-- CREATED		"Sun Sep 05 01:51:39 2021"

LIBRARY ieee;
USE ieee.std_logic_1164.all; 

LIBRARY work;

ENTITY FallingEdge IS 
	PORT
	(
		clk :  IN  STD_LOGIC;
		input :  IN  STD_LOGIC;
		output :  OUT  STD_LOGIC
	);
END FallingEdge;

ARCHITECTURE bdf_type OF FallingEdge IS 

SIGNAL	SYNTHESIZED_WIRE_0 :  STD_LOGIC := '0';
SIGNAL	SYNTHESIZED_WIRE_3 :  STD_LOGIC := '0';
SIGNAL	SYNTHESIZED_WIRE_1 :  STD_LOGIC := '0';
SIGNAL	SYNTHESIZED_WIRE_2 :  STD_LOGIC := '0';
SIGNAL	SRFF_inst1 :  STD_LOGIC := '0';


BEGIN 



PROCESS(clk)
VARIABLE synthesized_var_for_SYNTHESIZED_WIRE_3 : STD_LOGIC;
BEGIN
IF (RISING_EDGE(clk)) THEN
	synthesized_var_for_SYNTHESIZED_WIRE_3 := (NOT(synthesized_var_for_SYNTHESIZED_WIRE_3) AND input) OR (synthesized_var_for_SYNTHESIZED_WIRE_3 AND (NOT(SYNTHESIZED_WIRE_0)));
END IF;
	SYNTHESIZED_WIRE_3 <= synthesized_var_for_SYNTHESIZED_WIRE_3;
END PROCESS;


PROCESS(clk)
VARIABLE synthesized_var_for_SRFF_inst1 : STD_LOGIC;
BEGIN
IF (RISING_EDGE(clk)) THEN
	synthesized_var_for_SRFF_inst1 := (NOT(synthesized_var_for_SRFF_inst1) AND SYNTHESIZED_WIRE_3) OR (synthesized_var_for_SRFF_inst1 AND (NOT(SYNTHESIZED_WIRE_1)));
END IF;
	SRFF_inst1 <= synthesized_var_for_SRFF_inst1;
END PROCESS;


SYNTHESIZED_WIRE_0 <= NOT(input);



SYNTHESIZED_WIRE_1 <= NOT(SYNTHESIZED_WIRE_3);



output <= SYNTHESIZED_WIRE_2 AND SRFF_inst1;


SYNTHESIZED_WIRE_2 <= NOT(SYNTHESIZED_WIRE_3);



END bdf_type;