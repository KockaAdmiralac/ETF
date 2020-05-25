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

-- DATE "05/24/2020 02:17:21"

-- 
-- Device: Altera EP3C16F484C6 Package FBGA484
-- 

-- 
-- This VHDL file should be used for ModelSim-Altera (VHDL) only
-- 

LIBRARY ALTERA;
LIBRARY CYCLONEIII;
LIBRARY IEEE;
USE ALTERA.ALTERA_PRIMITIVES_COMPONENTS.ALL;
USE CYCLONEIII.CYCLONEIII_COMPONENTS.ALL;
USE IEEE.STD_LOGIC_1164.ALL;

ENTITY 	dz2 IS
    PORT (
	HEX0_0 : OUT std_logic;
	BTN1 : IN std_logic;
	BTN0 : IN std_logic;
	CLK : IN std_logic;
	HEX0_1 : OUT std_logic;
	HEX0_2 : OUT std_logic;
	HEX0_3 : OUT std_logic;
	HEX0_4 : OUT std_logic;
	HEX0_5 : OUT std_logic;
	HEX0_6 : OUT std_logic;
	HEX0_DP : OUT std_logic
	);
END dz2;

-- Design Ports Information
-- HEX0_0	=>  Location: PIN_E11,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- HEX0_1	=>  Location: PIN_F11,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- HEX0_2	=>  Location: PIN_H12,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- HEX0_3	=>  Location: PIN_H13,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- HEX0_4	=>  Location: PIN_G12,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- HEX0_5	=>  Location: PIN_F12,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- HEX0_6	=>  Location: PIN_F13,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- HEX0_DP	=>  Location: PIN_D13,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- BTN1	=>  Location: PIN_G3,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- BTN0	=>  Location: PIN_H2,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- CLK	=>  Location: PIN_G21,	 I/O Standard: 2.5 V,	 Current Strength: Default


ARCHITECTURE structure OF dz2 IS
SIGNAL gnd : std_logic := '0';
SIGNAL vcc : std_logic := '1';
SIGNAL unknown : std_logic := 'X';
SIGNAL devoe : std_logic := '1';
SIGNAL devclrn : std_logic := '1';
SIGNAL devpor : std_logic := '1';
SIGNAL ww_devoe : std_logic;
SIGNAL ww_devclrn : std_logic;
SIGNAL ww_devpor : std_logic;
SIGNAL ww_HEX0_0 : std_logic;
SIGNAL ww_BTN1 : std_logic;
SIGNAL ww_BTN0 : std_logic;
SIGNAL ww_CLK : std_logic;
SIGNAL ww_HEX0_1 : std_logic;
SIGNAL ww_HEX0_2 : std_logic;
SIGNAL ww_HEX0_3 : std_logic;
SIGNAL ww_HEX0_4 : std_logic;
SIGNAL ww_HEX0_5 : std_logic;
SIGNAL ww_HEX0_6 : std_logic;
SIGNAL ww_HEX0_DP : std_logic;
SIGNAL \CLK~inputclkctrl_INCLK_bus\ : std_logic_vector(3 DOWNTO 0);
SIGNAL \inst107|inst25~0_combout\ : std_logic;
SIGNAL \inst107|inst26~1_combout\ : std_logic;
SIGNAL \CLK~input_o\ : std_logic;
SIGNAL \CLK~inputclkctrl_outclk\ : std_logic;
SIGNAL \HEX0_0~output_o\ : std_logic;
SIGNAL \HEX0_1~output_o\ : std_logic;
SIGNAL \HEX0_2~output_o\ : std_logic;
SIGNAL \HEX0_3~output_o\ : std_logic;
SIGNAL \HEX0_4~output_o\ : std_logic;
SIGNAL \HEX0_5~output_o\ : std_logic;
SIGNAL \HEX0_6~output_o\ : std_logic;
SIGNAL \HEX0_DP~output_o\ : std_logic;
SIGNAL \BTN0~input_o\ : std_logic;
SIGNAL \inst103|state[1]~0_combout\ : std_logic;
SIGNAL \inst105~0_combout\ : std_logic;
SIGNAL \BTN1~input_o\ : std_logic;
SIGNAL \inst104|state[1]~0_combout\ : std_logic;
SIGNAL \inst106~combout\ : std_logic;
SIGNAL \inst107|inst35~0_combout\ : std_logic;
SIGNAL \inst107|inst35~1_combout\ : std_logic;
SIGNAL \inst107|inst35~q\ : std_logic;
SIGNAL \inst107|inst28~0_combout\ : std_logic;
SIGNAL \inst107|inst31~0_combout\ : std_logic;
SIGNAL \inst107|inst31~q\ : std_logic;
SIGNAL \inst107|inst29~0_combout\ : std_logic;
SIGNAL \inst107|inst33~0_combout\ : std_logic;
SIGNAL \inst107|inst33~q\ : std_logic;
SIGNAL \inst107|inst26~0_combout\ : std_logic;
SIGNAL \inst107|inst9~1_combout\ : std_logic;
SIGNAL \inst107|inst26~2_combout\ : std_logic;
SIGNAL \inst107|inst27~0_combout\ : std_logic;
SIGNAL \inst107|inst27~1_combout\ : std_logic;
SIGNAL \inst107|inst25~1_combout\ : std_logic;
SIGNAL \inst107|inst9~0_combout\ : std_logic;
SIGNAL \inst107|inst25~2_combout\ : std_logic;
SIGNAL \inst108|Mux0~0_combout\ : std_logic;
SIGNAL \inst108|Mux1~0_combout\ : std_logic;
SIGNAL \inst108|Mux2~0_combout\ : std_logic;
SIGNAL \inst108|Mux3~0_combout\ : std_logic;
SIGNAL \inst108|Mux4~0_combout\ : std_logic;
SIGNAL \inst108|Mux5~0_combout\ : std_logic;
SIGNAL \inst108|Mux6~0_combout\ : std_logic;
SIGNAL \inst104|state\ : std_logic_vector(1 DOWNTO 0);
SIGNAL \inst103|state\ : std_logic_vector(1 DOWNTO 0);

BEGIN

HEX0_0 <= ww_HEX0_0;
ww_BTN1 <= BTN1;
ww_BTN0 <= BTN0;
ww_CLK <= CLK;
HEX0_1 <= ww_HEX0_1;
HEX0_2 <= ww_HEX0_2;
HEX0_3 <= ww_HEX0_3;
HEX0_4 <= ww_HEX0_4;
HEX0_5 <= ww_HEX0_5;
HEX0_6 <= ww_HEX0_6;
HEX0_DP <= ww_HEX0_DP;
ww_devoe <= devoe;
ww_devclrn <= devclrn;
ww_devpor <= devpor;

\CLK~inputclkctrl_INCLK_bus\ <= (vcc & vcc & vcc & \CLK~input_o\);

-- Location: LCCOMB_X23_Y26_N26
\inst107|inst25~0\ : cycloneiii_lcell_comb
-- Equation(s):
-- \inst107|inst25~0_combout\ = (\inst105~0_combout\ & (\inst107|inst31~q\ & ((\inst104|state\(0)) # (!\inst104|state\(1)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100010000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \inst104|state\(1),
	datab => \inst105~0_combout\,
	datac => \inst104|state\(0),
	datad => \inst107|inst31~q\,
	combout => \inst107|inst25~0_combout\);

-- Location: LCCOMB_X24_Y26_N6
\inst107|inst26~1\ : cycloneiii_lcell_comb
-- Equation(s):
-- \inst107|inst26~1_combout\ = (\inst107|inst31~q\ & !\inst107|inst35~q\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000010101010",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \inst107|inst31~q\,
	datad => \inst107|inst35~q\,
	combout => \inst107|inst26~1_combout\);

-- Location: IOIBUF_X41_Y15_N1
\CLK~input\ : cycloneiii_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_CLK,
	o => \CLK~input_o\);

-- Location: CLKCTRL_G9
\CLK~inputclkctrl\ : cycloneiii_clkctrl
-- pragma translate_off
GENERIC MAP (
	clock_type => "global clock",
	ena_register_mode => "none")
-- pragma translate_on
PORT MAP (
	inclk => \CLK~inputclkctrl_INCLK_bus\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	outclk => \CLK~inputclkctrl_outclk\);

-- Location: IOOBUF_X21_Y29_N23
\HEX0_0~output\ : cycloneiii_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \inst108|Mux0~0_combout\,
	devoe => ww_devoe,
	o => \HEX0_0~output_o\);

-- Location: IOOBUF_X21_Y29_N30
\HEX0_1~output\ : cycloneiii_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \inst108|Mux1~0_combout\,
	devoe => ww_devoe,
	o => \HEX0_1~output_o\);

-- Location: IOOBUF_X26_Y29_N2
\HEX0_2~output\ : cycloneiii_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \inst108|Mux2~0_combout\,
	devoe => ww_devoe,
	o => \HEX0_2~output_o\);

-- Location: IOOBUF_X28_Y29_N30
\HEX0_3~output\ : cycloneiii_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \inst108|Mux3~0_combout\,
	devoe => ww_devoe,
	o => \HEX0_3~output_o\);

-- Location: IOOBUF_X26_Y29_N9
\HEX0_4~output\ : cycloneiii_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \inst108|Mux4~0_combout\,
	devoe => ww_devoe,
	o => \HEX0_4~output_o\);

-- Location: IOOBUF_X28_Y29_N23
\HEX0_5~output\ : cycloneiii_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \inst108|Mux5~0_combout\,
	devoe => ww_devoe,
	o => \HEX0_5~output_o\);

-- Location: IOOBUF_X26_Y29_N16
\HEX0_6~output\ : cycloneiii_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \inst108|Mux6~0_combout\,
	devoe => ww_devoe,
	o => \HEX0_6~output_o\);

-- Location: IOOBUF_X23_Y29_N9
\HEX0_DP~output\ : cycloneiii_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => VCC,
	devoe => ww_devoe,
	o => \HEX0_DP~output_o\);

-- Location: IOIBUF_X0_Y21_N8
\BTN0~input\ : cycloneiii_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_BTN0,
	o => \BTN0~input_o\);

-- Location: LCCOMB_X23_Y26_N10
\inst103|state[1]~0\ : cycloneiii_lcell_comb
-- Equation(s):
-- \inst103|state[1]~0_combout\ = !\BTN0~input_o\

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000111100001111",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datac => \BTN0~input_o\,
	combout => \inst103|state[1]~0_combout\);

-- Location: FF_X23_Y26_N11
\inst103|state[1]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \CLK~inputclkctrl_outclk\,
	d => \inst103|state[1]~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \inst103|state\(1));

-- Location: FF_X23_Y26_N5
\inst103|state[0]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \CLK~inputclkctrl_outclk\,
	asdata => \inst103|state\(1),
	sload => VCC,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \inst103|state\(0));

-- Location: LCCOMB_X23_Y26_N4
\inst105~0\ : cycloneiii_lcell_comb
-- Equation(s):
-- \inst105~0_combout\ = (\BTN1~input_o\ & (((\inst103|state\(0)) # (!\inst103|state\(1))))) # (!\BTN1~input_o\ & (\BTN0~input_o\ & ((\inst103|state\(0)) # (!\inst103|state\(1)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1110000011101110",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \BTN1~input_o\,
	datab => \BTN0~input_o\,
	datac => \inst103|state\(0),
	datad => \inst103|state\(1),
	combout => \inst105~0_combout\);

-- Location: IOIBUF_X0_Y23_N15
\BTN1~input\ : cycloneiii_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_BTN1,
	o => \BTN1~input_o\);

-- Location: LCCOMB_X23_Y26_N20
\inst104|state[1]~0\ : cycloneiii_lcell_comb
-- Equation(s):
-- \inst104|state[1]~0_combout\ = !\BTN1~input_o\

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000011111111",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datad => \BTN1~input_o\,
	combout => \inst104|state[1]~0_combout\);

-- Location: FF_X23_Y26_N21
\inst104|state[1]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \CLK~inputclkctrl_outclk\,
	d => \inst104|state[1]~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \inst104|state\(1));

-- Location: FF_X23_Y26_N27
\inst104|state[0]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \CLK~inputclkctrl_outclk\,
	asdata => \inst104|state\(1),
	sload => VCC,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \inst104|state\(0));

-- Location: LCCOMB_X23_Y26_N28
inst106 : cycloneiii_lcell_comb
-- Equation(s):
-- \inst106~combout\ = (\BTN1~input_o\ & (((!\inst104|state\(0) & \inst104|state\(1))))) # (!\BTN1~input_o\ & (((!\inst104|state\(0) & \inst104|state\(1))) # (!\BTN0~input_o\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0001111100010001",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \BTN1~input_o\,
	datab => \BTN0~input_o\,
	datac => \inst104|state\(0),
	datad => \inst104|state\(1),
	combout => \inst106~combout\);

-- Location: LCCOMB_X23_Y26_N6
\inst107|inst35~0\ : cycloneiii_lcell_comb
-- Equation(s):
-- \inst107|inst35~0_combout\ = (\inst107|inst35~q\ & ((\inst105~0_combout\ & ((\inst107|inst31~q\) # (!\inst106~combout\))) # (!\inst105~0_combout\ & ((\inst106~combout\))))) # (!\inst107|inst35~q\ & (((\inst105~0_combout\ & \inst106~combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1101101010100000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \inst107|inst35~q\,
	datab => \inst107|inst31~q\,
	datac => \inst105~0_combout\,
	datad => \inst106~combout\,
	combout => \inst107|inst35~0_combout\);

-- Location: LCCOMB_X23_Y26_N2
\inst107|inst35~1\ : cycloneiii_lcell_comb
-- Equation(s):
-- \inst107|inst35~1_combout\ = (\inst107|inst35~0_combout\ & ((\inst107|inst33~q\) # (\inst107|inst35~q\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111110000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => \inst107|inst33~q\,
	datac => \inst107|inst35~q\,
	datad => \inst107|inst35~0_combout\,
	combout => \inst107|inst35~1_combout\);

-- Location: FF_X23_Y26_N3
\inst107|inst35\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \CLK~inputclkctrl_outclk\,
	d => \inst107|inst35~1_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \inst107|inst35~q\);

-- Location: LCCOMB_X23_Y26_N8
\inst107|inst28~0\ : cycloneiii_lcell_comb
-- Equation(s):
-- \inst107|inst28~0_combout\ = (\inst107|inst31~q\ & (!\inst107|inst35~q\)) # (!\inst107|inst31~q\ & ((!\inst107|inst33~q\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011000000111111",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => \inst107|inst35~q\,
	datac => \inst107|inst31~q\,
	datad => \inst107|inst33~q\,
	combout => \inst107|inst28~0_combout\);

-- Location: LCCOMB_X23_Y26_N14
\inst107|inst31~0\ : cycloneiii_lcell_comb
-- Equation(s):
-- \inst107|inst31~0_combout\ = (\inst106~combout\ & (\inst107|inst31~q\ $ (((!\inst107|inst28~0_combout\ & \inst105~0_combout\))))) # (!\inst106~combout\ & (((\inst107|inst31~q\ & \inst105~0_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1101001010100000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \inst106~combout\,
	datab => \inst107|inst28~0_combout\,
	datac => \inst107|inst31~q\,
	datad => \inst105~0_combout\,
	combout => \inst107|inst31~0_combout\);

-- Location: FF_X23_Y26_N15
\inst107|inst31\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \CLK~inputclkctrl_outclk\,
	d => \inst107|inst31~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \inst107|inst31~q\);

-- Location: LCCOMB_X23_Y26_N12
\inst107|inst29~0\ : cycloneiii_lcell_comb
-- Equation(s):
-- \inst107|inst29~0_combout\ = (\inst107|inst33~q\ & ((\inst107|inst35~q\) # (!\inst107|inst31~q\))) # (!\inst107|inst33~q\ & ((\inst107|inst31~q\) # (!\inst107|inst35~q\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111110000111111",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => \inst107|inst33~q\,
	datac => \inst107|inst31~q\,
	datad => \inst107|inst35~q\,
	combout => \inst107|inst29~0_combout\);

-- Location: LCCOMB_X23_Y26_N24
\inst107|inst33~0\ : cycloneiii_lcell_comb
-- Equation(s):
-- \inst107|inst33~0_combout\ = (\inst106~combout\ & (\inst107|inst33~q\ $ (((\inst105~0_combout\ & \inst107|inst29~0_combout\))))) # (!\inst106~combout\ & (\inst105~0_combout\ & (\inst107|inst33~q\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0110100011100000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \inst106~combout\,
	datab => \inst105~0_combout\,
	datac => \inst107|inst33~q\,
	datad => \inst107|inst29~0_combout\,
	combout => \inst107|inst33~0_combout\);

-- Location: FF_X23_Y26_N25
\inst107|inst33\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \CLK~inputclkctrl_outclk\,
	d => \inst107|inst33~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \inst107|inst33~q\);

-- Location: LCCOMB_X24_Y26_N24
\inst107|inst26~0\ : cycloneiii_lcell_comb
-- Equation(s):
-- \inst107|inst26~0_combout\ = (\inst106~combout\ & (!\inst107|inst33~q\ & ((\inst107|inst31~q\) # (!\inst107|inst35~q\)))) # (!\inst106~combout\ & (\inst107|inst33~q\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0110010001100110",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \inst106~combout\,
	datab => \inst107|inst33~q\,
	datac => \inst107|inst31~q\,
	datad => \inst107|inst35~q\,
	combout => \inst107|inst26~0_combout\);

-- Location: LCCOMB_X24_Y26_N20
\inst107|inst9~1\ : cycloneiii_lcell_comb
-- Equation(s):
-- \inst107|inst9~1_combout\ = (\inst106~combout\ & \inst107|inst33~q\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100110000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => \inst106~combout\,
	datad => \inst107|inst33~q\,
	combout => \inst107|inst9~1_combout\);

-- Location: LCCOMB_X24_Y26_N12
\inst107|inst26~2\ : cycloneiii_lcell_comb
-- Equation(s):
-- \inst107|inst26~2_combout\ = (\inst105~0_combout\ & ((\inst107|inst26~0_combout\) # ((\inst107|inst26~1_combout\ & \inst107|inst9~1_combout\)))) # (!\inst105~0_combout\ & (((\inst107|inst9~1_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1110111111000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \inst107|inst26~1_combout\,
	datab => \inst107|inst26~0_combout\,
	datac => \inst105~0_combout\,
	datad => \inst107|inst9~1_combout\,
	combout => \inst107|inst26~2_combout\);

-- Location: LCCOMB_X24_Y26_N4
\inst107|inst27~0\ : cycloneiii_lcell_comb
-- Equation(s):
-- \inst107|inst27~0_combout\ = (\inst105~0_combout\ & ((\inst106~combout\ & (\inst107|inst33~q\ & !\inst107|inst35~q\)) # (!\inst106~combout\ & ((\inst107|inst35~q\)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000101010000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \inst105~0_combout\,
	datab => \inst107|inst33~q\,
	datac => \inst106~combout\,
	datad => \inst107|inst35~q\,
	combout => \inst107|inst27~0_combout\);

-- Location: LCCOMB_X24_Y26_N8
\inst107|inst27~1\ : cycloneiii_lcell_comb
-- Equation(s):
-- \inst107|inst27~1_combout\ = (\inst107|inst27~0_combout\) # ((!\inst107|inst9~0_combout\ & (\inst107|inst35~q\ & \inst106~combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111010011110000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \inst107|inst9~0_combout\,
	datab => \inst107|inst35~q\,
	datac => \inst107|inst27~0_combout\,
	datad => \inst106~combout\,
	combout => \inst107|inst27~1_combout\);

-- Location: LCCOMB_X24_Y26_N18
\inst107|inst25~1\ : cycloneiii_lcell_comb
-- Equation(s):
-- \inst107|inst25~1_combout\ = (\inst106~combout\ & (\inst107|inst31~q\ & ((!\inst107|inst35~q\) # (!\inst105~0_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000100010001000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \inst106~combout\,
	datab => \inst107|inst31~q\,
	datac => \inst105~0_combout\,
	datad => \inst107|inst35~q\,
	combout => \inst107|inst25~1_combout\);

-- Location: LCCOMB_X24_Y26_N26
\inst107|inst9~0\ : cycloneiii_lcell_comb
-- Equation(s):
-- \inst107|inst9~0_combout\ = (\inst105~0_combout\ & !\inst107|inst31~q\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000011110000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datac => \inst105~0_combout\,
	datad => \inst107|inst31~q\,
	combout => \inst107|inst9~0_combout\);

-- Location: LCCOMB_X24_Y26_N10
\inst107|inst25~2\ : cycloneiii_lcell_comb
-- Equation(s):
-- \inst107|inst25~2_combout\ = (\inst107|inst25~0_combout\) # ((\inst107|inst25~1_combout\) # ((\inst107|inst9~0_combout\ & \inst107|inst9~1_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111111011101110",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \inst107|inst25~0_combout\,
	datab => \inst107|inst25~1_combout\,
	datac => \inst107|inst9~0_combout\,
	datad => \inst107|inst9~1_combout\,
	combout => \inst107|inst25~2_combout\);

-- Location: LCCOMB_X24_Y26_N2
\inst108|Mux0~0\ : cycloneiii_lcell_comb
-- Equation(s):
-- \inst108|Mux0~0_combout\ = (!\inst107|inst26~2_combout\ & (\inst107|inst27~1_combout\ $ (\inst107|inst25~2_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000010101010000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \inst107|inst26~2_combout\,
	datac => \inst107|inst27~1_combout\,
	datad => \inst107|inst25~2_combout\,
	combout => \inst108|Mux0~0_combout\);

-- Location: LCCOMB_X24_Y26_N28
\inst108|Mux1~0\ : cycloneiii_lcell_comb
-- Equation(s):
-- \inst108|Mux1~0_combout\ = (\inst107|inst25~2_combout\ & (\inst107|inst26~2_combout\ $ (\inst107|inst27~1_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101101000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \inst107|inst26~2_combout\,
	datac => \inst107|inst27~1_combout\,
	datad => \inst107|inst25~2_combout\,
	combout => \inst108|Mux1~0_combout\);

-- Location: LCCOMB_X24_Y26_N22
\inst108|Mux2~0\ : cycloneiii_lcell_comb
-- Equation(s):
-- \inst108|Mux2~0_combout\ = (\inst107|inst26~2_combout\ & (!\inst107|inst27~1_combout\ & !\inst107|inst25~2_combout\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000000001010",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \inst107|inst26~2_combout\,
	datac => \inst107|inst27~1_combout\,
	datad => \inst107|inst25~2_combout\,
	combout => \inst108|Mux2~0_combout\);

-- Location: LCCOMB_X24_Y26_N16
\inst108|Mux3~0\ : cycloneiii_lcell_comb
-- Equation(s):
-- \inst108|Mux3~0_combout\ = (\inst107|inst26~2_combout\ & (\inst107|inst27~1_combout\ & \inst107|inst25~2_combout\)) # (!\inst107|inst26~2_combout\ & (\inst107|inst27~1_combout\ $ (\inst107|inst25~2_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1010010101010000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \inst107|inst26~2_combout\,
	datac => \inst107|inst27~1_combout\,
	datad => \inst107|inst25~2_combout\,
	combout => \inst108|Mux3~0_combout\);

-- Location: LCCOMB_X24_Y26_N14
\inst108|Mux4~0\ : cycloneiii_lcell_comb
-- Equation(s):
-- \inst108|Mux4~0_combout\ = (\inst107|inst27~1_combout\) # ((!\inst107|inst26~2_combout\ & \inst107|inst25~2_combout\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111010111110000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \inst107|inst26~2_combout\,
	datac => \inst107|inst27~1_combout\,
	datad => \inst107|inst25~2_combout\,
	combout => \inst108|Mux4~0_combout\);

-- Location: LCCOMB_X24_Y26_N0
\inst108|Mux5~0\ : cycloneiii_lcell_comb
-- Equation(s):
-- \inst108|Mux5~0_combout\ = (\inst107|inst26~2_combout\ & ((\inst107|inst27~1_combout\) # (!\inst107|inst25~2_combout\))) # (!\inst107|inst26~2_combout\ & (\inst107|inst27~1_combout\ & !\inst107|inst25~2_combout\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1010000011111010",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \inst107|inst26~2_combout\,
	datac => \inst107|inst27~1_combout\,
	datad => \inst107|inst25~2_combout\,
	combout => \inst108|Mux5~0_combout\);

-- Location: LCCOMB_X24_Y26_N30
\inst108|Mux6~0\ : cycloneiii_lcell_comb
-- Equation(s):
-- \inst108|Mux6~0_combout\ = (\inst107|inst26~2_combout\ & (\inst107|inst27~1_combout\ & \inst107|inst25~2_combout\)) # (!\inst107|inst26~2_combout\ & ((!\inst107|inst25~2_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1010000001010101",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \inst107|inst26~2_combout\,
	datac => \inst107|inst27~1_combout\,
	datad => \inst107|inst25~2_combout\,
	combout => \inst108|Mux6~0_combout\);

ww_HEX0_0 <= \HEX0_0~output_o\;

ww_HEX0_1 <= \HEX0_1~output_o\;

ww_HEX0_2 <= \HEX0_2~output_o\;

ww_HEX0_3 <= \HEX0_3~output_o\;

ww_HEX0_4 <= \HEX0_4~output_o\;

ww_HEX0_5 <= \HEX0_5~output_o\;

ww_HEX0_6 <= \HEX0_6~output_o\;

ww_HEX0_DP <= \HEX0_DP~output_o\;
END structure;


