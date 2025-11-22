// @file:	delay.h
// @author: sramos
// @brief:	Delay function implementation with TIMER1 setups

#pragma once

#include "mem.h"
#include "interrupt.h"

namespace delay
{
	
// Address Inits
uint8_t* tccr1b = (uint8_t*)mem_map::TCCR1B;
uint8_t* timsk1 = (uint8_t*)mem_map::TIMSK1;
uint8_t* sreg   = (uint8_t*)mem_map::SREG;
uint8_t* ocr1ah = (uint8_t*)mem_map::OCR1AH;
uint8_t* ocr1al = (uint8_t*)mem_map::OCR1AL;
uint8_t* tcnt1h = (uint8_t*)mem_map::TCNT1H;
uint8_t* tcnt1l = (uint8_t*)mem_map::TCNT1L;

volatile bool delayFlag;

ISR(TIMER1_COMPA_vect)
{
	delayFlag = false;
}

void init()
{
	*tccr1b |= 0x08;
	*timsk1 |= 0x02;
	sei();
}

void delayTicks(uint16_t ticks)
{
	delayFlag = true;
	*ocr1ah = (ticks & 0xff00) >> 8;
	*ocr1al = (ticks & 0x00ff);
	*tcnt1h = 0x00;
	*tcnt1l = 0x00;
	*tccr1b |= 0x05;
	
	while(delayFlag)
	{
		// do nothing until isr resets the flag
	}
	
	*tccr1b &= 0xf8;
}	

void delayMS(uint16_t ms)
{
	// 0x3d09 ticks / second
	static const uint16_t TICKS_PER_MS = 0x000f;
	uint16_t ticks = TICKS_PER_MS * ms;
	delayTicks(ticks);
}

} // end namespace delay
