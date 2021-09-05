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
-- CREATED		"Fri Sep 03 20:24:59 2021"

LIBRARY ieee;
USE ieee.std_logic_1164.all; 

LIBRARY work;

ENTITY CMP1 IS 
	PORT
	(
		A :  IN  STD_LOGIC;
		B :  IN  STD_LOGIC;
		Gi1 :  IN  STD_LOGIC;
		Ei1 :  IN  STD_LOGIC;
		Li1 :  IN  STD_LOGIC;
		G :  OUT  STD_LOGIC;
		E :  OUT  STD_LOGIC;
		L :  OUT  STD_LOGIC
	);
END CMP1;

ARCHITECTURE bdf_type OF CMP1 IS 

SIGNAL	AeqB :  STD_LOGIC;
SIGNAL	nA :  STD_LOGIC;
SIGNAL	nB :  STD_LOGIC;
SIGNAL	SYNTHESIZED_WIRE_0 :  STD_LOGIC;
SIGNAL	SYNTHESIZED_WIRE_1 :  STD_LOGIC;
SIGNAL	SYNTHESIZED_WIRE_2 :  STD_LOGIC;
SIGNAL	SYNTHESIZED_WIRE_3 :  STD_LOGIC;


BEGIN 



nB <= NOT(B);



nA <= NOT(A);



E <= AeqB AND Ei1;


SYNTHESIZED_WIRE_1 <= A AND nB;


G <= SYNTHESIZED_WIRE_0 OR SYNTHESIZED_WIRE_1;


AeqB <= NOT(nA XOR nB);


SYNTHESIZED_WIRE_0 <= Gi1 AND AeqB;


SYNTHESIZED_WIRE_3 <= nA AND B;


SYNTHESIZED_WIRE_2 <= Li1 AND AeqB;


L <= SYNTHESIZED_WIRE_2 OR SYNTHESIZED_WIRE_3;


END bdf_type;