.cpu cortex-m3
.fpu softvfp
.syntax unified
.thumb

.section .vector_table, "a"

.extern main
.extern systick_handler
.extern test5
.extern test6_irq0
.extern test6_irq1
.extern test6_irq2

.word 0x20002800
.word main
.rept 12
	.word infinite_loop
.endr
.word test5
.word systick_handler
.word test6_irq0
.word test6_irq1
.word test6_irq2
.rept 65
	.word infinite_loop
.endr

.text
infinite_loop:
	b infinite_loop
