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
-- CREATED		"Fri Sep 03 22:00:49 2021"

LIBRARY ieee;
USE ieee.std_logic_1164.all; 

LIBRARY work;

ENTITY CMP6 IS 
	PORT
	(
		A :  IN  STD_LOGIC_VECTOR(5 DOWNTO 0);
		B :  IN  STD_LOGIC_VECTOR(5 DOWNTO 0);
		G :  OUT  STD_LOGIC;
		E :  OUT  STD_LOGIC;
		L :  OUT  STD_LOGIC
	);
END CMP6;

ARCHITECTURE bdf_type OF CMP6 IS 

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

SIGNAL	one :  STD_LOGIC;
SIGNAL	zero :  STD_LOGIC;
SIGNAL	SYNTHESIZED_WIRE_0 :  STD_LOGIC;
SIGNAL	SYNTHESIZED_WIRE_1 :  STD_LOGIC;
SIGNAL	SYNTHESIZED_WIRE_2 :  STD_LOGIC;
SIGNAL	SYNTHESIZED_WIRE_3 :  STD_LOGIC;
SIGNAL	SYNTHESIZED_WIRE_4 :  STD_LOGIC;
SIGNAL	SYNTHESIZED_WIRE_5 :  STD_LOGIC;
SIGNAL	SYNTHESIZED_WIRE_6 :  STD_LOGIC;
SIGNAL	SYNTHESIZED_WIRE_7 :  STD_LOGIC;
SIGNAL	SYNTHESIZED_WIRE_8 :  STD_LOGIC;
SIGNAL	SYNTHESIZED_WIRE_9 :  STD_LOGIC;
SIGNAL	SYNTHESIZED_WIRE_10 :  STD_LOGIC;
SIGNAL	SYNTHESIZED_WIRE_11 :  STD_LOGIC;
SIGNAL	SYNTHESIZED_WIRE_12 :  STD_LOGIC;
SIGNAL	SYNTHESIZED_WIRE_13 :  STD_LOGIC;
SIGNAL	SYNTHESIZED_WIRE_14 :  STD_LOGIC;


BEGIN 



b2v_inst : cmp1
PORT MAP(A => A(0),
		 B => B(0),
		 Gi1 => zero,
		 Ei1 => one,
		 Li1 => zero,
		 G => SYNTHESIZED_WIRE_0,
		 E => SYNTHESIZED_WIRE_1,
		 L => SYNTHESIZED_WIRE_2);


b2v_inst1 : cmp1
PORT MAP(A => A(1),
		 B => B(1),
		 Gi1 => SYNTHESIZED_WIRE_0,
		 Ei1 => SYNTHESIZED_WIRE_1,
		 Li1 => SYNTHESIZED_WIRE_2,
		 G => SYNTHESIZED_WIRE_3,
		 E => SYNTHESIZED_WIRE_4,
		 L => SYNTHESIZED_WIRE_5);


b2v_inst2 : cmp1
PORT MAP(A => A(2),
		 B => B(2),
		 Gi1 => SYNTHESIZED_WIRE_3,
		 Ei1 => SYNTHESIZED_WIRE_4,
		 Li1 => SYNTHESIZED_WIRE_5,
		 G => SYNTHESIZED_WIRE_6,
		 E => SYNTHESIZED_WIRE_7,
		 L => SYNTHESIZED_WIRE_8);


b2v_inst3 : cmp1
PORT MAP(A => A(3),
		 B => B(3),
		 Gi1 => SYNTHESIZED_WIRE_6,
		 Ei1 => SYNTHESIZED_WIRE_7,
		 Li1 => SYNTHESIZED_WIRE_8,
		 G => SYNTHESIZED_WIRE_9,
		 E => SYNTHESIZED_WIRE_10,
		 L => SYNTHESIZED_WIRE_11);


b2v_inst4 : cmp1
PORT MAP(A => A(4),
		 B => B(4),
		 Gi1 => SYNTHESIZED_WIRE_9,
		 Ei1 => SYNTHESIZED_WIRE_10,
		 Li1 => SYNTHESIZED_WIRE_11,
		 G => SYNTHESIZED_WIRE_12,
		 E => SYNTHESIZED_WIRE_13,
		 L => SYNTHESIZED_WIRE_14);




b2v_inst7 : cmp1
PORT MAP(A => A(5),
		 B => B(5),
		 Gi1 => SYNTHESIZED_WIRE_12,
		 Ei1 => SYNTHESIZED_WIRE_13,
		 Li1 => SYNTHESIZED_WIRE_14,
		 G => G,
		 E => E,
		 L => L);


one <= '1';
zero <= '0';
END bdf_type;