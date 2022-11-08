#include "nvic.h"
#include "scb.h"
#include "stk.h"
#include "test.h"

uint32_t millis;

void start() {
	millis = 0;
	STK->VAL = 0;
	STK->LOAD = 8000 - 1;
	STK->CTRL |= STK_CTRL_CLKSOURCE | STK_CTRL_ENABLE | STK_CTRL_TICKINT;
}

uint32_t stop() {
	STK->CTRL &= ~(STK_CTRL_CLKSOURCE | STK_CTRL_ENABLE | STK_CTRL_TICKINT);
	return millis;
}

void systick_handler() {
	++millis;
}

extern char _vma_data_start;
extern char _vma_data_end;
extern char _lma_data_start;

int main() {
	// Kopiranje podataka
	for (char *data_src = &_lma_data_start, *data_dst = &_vma_data_start; data_dst != &_vma_data_end; *(data_dst++) = *(data_src++));
	// Poziv test funkcije kako je receno
	test4();
	// Podesavanje prioriteta: xx.yy (x - grupa, y - podgrupa)
	SCB->AIRCR = (0x5FA << 16) | (5 << 8);
	// Postavljanje prioriteta za PendSV
	SCB->SHPR3 = (0xF0 << 16);
	// Postavljanje pending bita za PendSV
	SCB->ICSR |= 0x10000000;
	// Omogucavanje IRQ2..0
	NVIC->ISER[0] |= 0x7;
	// Postavljanje prioriteta za IRQ2..0
	NVIC->IPR[0] = (0b10000000 << 16) | (0b10110000 << 8) | (0b10010000 << 0);
	// Postavljanje pending bita za IRQ2..0
	NVIC->ISPR[0] |= 0x7;
	// STK testiranje
	test7();
	while (1);
}
