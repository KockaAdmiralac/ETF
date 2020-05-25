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

-- VENDOR "Altera"
-- PROGRAM "Quartus II 64-Bit"
-- VERSION "Version 13.0.1 Build 232 06/12/2013 Service Pack 1 SJ Web Edition"

-- DATE "05/23/2020 18:58:17"

-- 
-- Device: Altera EP3C16F484C6 Package FBGA484
-- 

-- 
-- This VHDL file should be used for ModelSim-Altera (VHDL) only
-- 

LIBRARY CYCLONEIII;
LIBRARY IEEE;
USE CYCLONEIII.CYCLONEIII_COMPONENTS.ALL;
USE IEEE.STD_LOGIC_1164.ALL;

ENTITY 	dz1 IS
    PORT (
	a : OUT std_logic;
	z3 : IN std_logic;
	z2 : IN std_logic;
	z1 : IN std_logic;
	z0 : IN std_logic;
	b : OUT std_logic;
	c : OUT std_logic;
	d : OUT std_logic;
	e : OUT std_logic;
	f : OUT std_logic;
	g : OUT std_logic
	);
END dz1;

-- Design Ports Information
-- a	=>  Location: PIN_E11,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- b	=>  Location: PIN_F11,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- c	=>  Location: PIN_H12,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- d	=>  Location: PIN_H13,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- e	=>  Location: PIN_G12,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- f	=>  Location: PIN_F12,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- g	=>  Location: PIN_F13,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- z2	=>  Location: PIN_H6,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- z0	=>  Location: PIN_J6,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- z3	=>  Location: PIN_G4,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- z1	=>  Location: PIN_H5,	 I/O Standard: 2.5 V,	 Current Strength: Default


ARCHITECTURE structure OF dz1 IS
SIGNAL gnd : std_logic := '0';
SIGNAL vcc : std_logic := '1';
SIGNAL unknown : std_logic := 'X';
SIGNAL devoe : std_logic := '1';
SIGNAL devclrn : std_logic := '1';
SIGNAL devpor : std_logic := '1';
SIGNAL ww_devoe : std_logic;
SIGNAL ww_devclrn : std_logic;
SIGNAL ww_devpor : std_logic;
SIGNAL ww_a : std_logic;
SIGNAL ww_z3 : std_logic;
SIGNAL ww_z2 : std_logic;
SIGNAL ww_z1 : std_logic;
SIGNAL ww_z0 : std_logic;
SIGNAL ww_b : std_logic;
SIGNAL ww_c : std_logic;
SIGNAL ww_d : std_logic;
SIGNAL ww_e : std_logic;
SIGNAL ww_f : std_logic;
SIGNAL ww_g : std_logic;
SIGNAL \a~output_o\ : std_logic;
SIGNAL \b~output_o\ : std_logic;
SIGNAL \c~output_o\ : std_logic;
SIGNAL \d~output_o\ : std_logic;
SIGNAL \e~output_o\ : std_logic;
SIGNAL \f~output_o\ : std_logic;
SIGNAL \g~output_o\ : std_logic;
SIGNAL \z3~input_o\ : std_logic;
SIGNAL \z2~input_o\ : std_logic;
SIGNAL \z0~input_o\ : std_logic;
SIGNAL \z1~input_o\ : std_logic;
SIGNAL \inst24~0_combout\ : std_logic;
SIGNAL \inst13~0_combout\ : std_logic;
SIGNAL \inst14~0_combout\ : std_logic;
SIGNAL \inst24~1_combout\ : std_logic;
SIGNAL \inst16~0_combout\ : std_logic;
SIGNAL \inst17~0_combout\ : std_logic;
SIGNAL \inst18~combout\ : std_logic;

BEGIN

a <= ww_a;
ww_z3 <= z3;
ww_z2 <= z2;
ww_z1 <= z1;
ww_z0 <= z0;
b <= ww_b;
c <= ww_c;
d <= ww_d;
e <= ww_e;
f <= ww_f;
g <= ww_g;
ww_devoe <= devoe;
ww_devclrn <= devclrn;
ww_devpor <= devpor;

-- Location: IOOBUF_X21_Y29_N23
\a~output\ : cycloneiii_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \inst24~0_combout\,
	devoe => ww_devoe,
	o => \a~output_o\);

-- Location: IOOBUF_X21_Y29_N30
\b~output\ : cycloneiii_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \inst13~0_combout\,
	devoe => ww_devoe,
	o => \b~output_o\);

-- Location: IOOBUF_X26_Y29_N2
\c~output\ : cycloneiii_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \inst14~0_combout\,
	devoe => ww_devoe,
	o => \c~output_o\);

-- Location: IOOBUF_X28_Y29_N30
\d~output\ : cycloneiii_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \inst24~1_combout\,
	devoe => ww_devoe,
	o => \d~output_o\);

-- Location: IOOBUF_X26_Y29_N9
\e~output\ : cycloneiii_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \inst16~0_combout\,
	devoe => ww_devoe,
	o => \e~output_o\);

-- Location: IOOBUF_X28_Y29_N23
\f~output\ : cycloneiii_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \inst17~0_combout\,
	devoe => ww_devoe,
	o => \f~output_o\);

-- Location: IOOBUF_X26_Y29_N16
\g~output\ : cycloneiii_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \inst18~combout\,
	devoe => ww_devoe,
	o => \g~output_o\);

-- Location: IOIBUF_X0_Y23_N8
\z3~input\ : cycloneiii_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_z3,
	o => \z3~input_o\);

-- Location: IOIBUF_X0_Y25_N22
\z2~input\ : cycloneiii_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_z2,
	o => \z2~input_o\);

-- Location: IOIBUF_X0_Y24_N1
\z0~input\ : cycloneiii_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_z0,
	o => \z0~input_o\);

-- Location: IOIBUF_X0_Y27_N1
\z1~input\ : cycloneiii_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_z1,
	o => \z1~input_o\);

-- Location: LCCOMB_X27_Y28_N24
\inst24~0\ : cycloneiii_lcell_comb
-- Equation(s):
-- \inst24~0_combout\ = (!\z3~input_o\ & (!\z1~input_o\ & (\z2~input_o\ $ (\z0~input_o\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000000010100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \z3~input_o\,
	datab => \z2~input_o\,
	datac => \z0~input_o\,
	datad => \z1~input_o\,
	combout => \inst24~0_combout\);

-- Location: LCCOMB_X27_Y28_N26
\inst13~0\ : cycloneiii_lcell_comb
-- Equation(s):
-- \inst13~0_combout\ = (\z3~input_o\ & ((\z2~input_o\) # ((\z1~input_o\)))) # (!\z3~input_o\ & ((\z0~input_o\ & ((!\z1~input_o\))) # (!\z0~input_o\ & (\z2~input_o\ & \z1~input_o\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1010111011011000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \z3~input_o\,
	datab => \z2~input_o\,
	datac => \z0~input_o\,
	datad => \z1~input_o\,
	combout => \inst13~0_combout\);

-- Location: LCCOMB_X27_Y28_N12
\inst14~0\ : cycloneiii_lcell_comb
-- Equation(s):
-- \inst14~0_combout\ = (\z2~input_o\ & (\z3~input_o\)) # (!\z2~input_o\ & (\z1~input_o\ $ (((!\z3~input_o\ & \z0~input_o\)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1010101110011000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \z3~input_o\,
	datab => \z2~input_o\,
	datac => \z0~input_o\,
	datad => \z1~input_o\,
	combout => \inst14~0_combout\);

-- Location: LCCOMB_X27_Y28_N6
\inst24~1\ : cycloneiii_lcell_comb
-- Equation(s):
-- \inst24~1_combout\ = (!\z3~input_o\ & ((\z2~input_o\ & (\z0~input_o\ $ (!\z1~input_o\))) # (!\z2~input_o\ & (\z0~input_o\ & !\z1~input_o\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0100000000010100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \z3~input_o\,
	datab => \z2~input_o\,
	datac => \z0~input_o\,
	datad => \z1~input_o\,
	combout => \inst24~1_combout\);

-- Location: LCCOMB_X27_Y28_N0
\inst16~0\ : cycloneiii_lcell_comb
-- Equation(s):
-- \inst16~0_combout\ = (\z3~input_o\ & (!\z2~input_o\ & (\z0~input_o\ & !\z1~input_o\))) # (!\z3~input_o\ & ((\z1~input_o\ & ((\z0~input_o\))) # (!\z1~input_o\ & (\z2~input_o\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101000001100100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \z3~input_o\,
	datab => \z2~input_o\,
	datac => \z0~input_o\,
	datad => \z1~input_o\,
	combout => \inst16~0_combout\);

-- Location: LCCOMB_X27_Y28_N10
\inst17~0\ : cycloneiii_lcell_comb
-- Equation(s):
-- \inst17~0_combout\ = (!\z3~input_o\ & (\z1~input_o\ & ((\z0~input_o\) # (!\z2~input_o\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101000100000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \z3~input_o\,
	datab => \z2~input_o\,
	datac => \z0~input_o\,
	datad => \z1~input_o\,
	combout => \inst17~0_combout\);

-- Location: LCCOMB_X27_Y28_N4
inst18 : cycloneiii_lcell_comb
-- Equation(s):
-- \inst18~combout\ = (!\z3~input_o\ & ((\z2~input_o\ & (\z0~input_o\ & \z1~input_o\)) # (!\z2~input_o\ & ((!\z1~input_o\)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0100000000010001",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \z3~input_o\,
	datab => \z2~input_o\,
	datac => \z0~input_o\,
	datad => \z1~input_o\,
	combout => \inst18~combout\);

ww_a <= \a~output_o\;

ww_b <= \b~output_o\;

ww_c <= \c~output_o\;

ww_d <= \d~output_o\;

ww_e <= \e~output_o\;

ww_f <= \f~output_o\;

ww_g <= \g~output_o\;
END structure;


