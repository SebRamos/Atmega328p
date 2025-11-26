// @file:	delay.cpp
// @author: sramos
// @brief:	Delay function implementation with TIMER1 setups

#include "interrupt.h"
#include "delay.h"
#include <stdint.h>

namespace delay
{
static volatile bool delayFlag;

// Address Inits
uint8_t* tccr1b = (uint8_t*)mem_map::TCCR1B;
uint8_t* timsk1 = (uint8_t*)mem_map::TIMSK1;
uint8_t* sreg   = (uint8_t*)mem_map::SREG;
uint8_t* ocr1ah = (uint8_t*)mem_map::OCR1AH;
uint8_t* ocr1al = (uint8_t*)mem_map::OCR1AL;
uint8_t* tcnt1h = (uint8_t*)mem_map::TCNT1H;
uint8_t* tcnt1l = (uint8_t*)mem_map::TCNT1L;

ISR(TIMER1_COMPA_vect)
{
	delayFlag = false;
}

void init()
{
	mem::writeReg(tccr1b, 0x08);
	mem::writeReg(timsk1, 0x02);
	sei();
}

void delayTicks(uint16_t ticks)
{
	delayFlag = true;
	mem::writeReg(ocr1ah, ((ticks & 0xff00) >> 8), mem::Write_mode_e::SET);
	mem::writeReg(ocr1al, (ticks & 0x00ff), mem::Write_mode_e::SET);
	mem::clearReg(tcnt1h);
	mem::clearReg(tcnt1l);

	// Enable clock source so the timer starts
	mem::writeReg(tccr1b, 0x05);
	
	while(delayFlag)
	{
		// do nothing until isr resets the flag
	}
	
	// Clear clock source so that the timer stops
	mem::clearReg(tccr1b, 0x05, mem::Clear_mode_e::PARTIAL);
}	

void delayMS(uint16_t ms)
{
	// 0x3d09 ticks / second
	static const uint16_t TICKS_PER_MS = 0x000f;
	uint16_t ticks = TICKS_PER_MS * ms;
	delayTicks(ticks);
}

} // end namespace delay