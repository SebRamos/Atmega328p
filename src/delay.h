// @file:	delay.h
// @author: sramos
// @brief:	Delay function declarations with TIMER1 setups

#pragma once

#include "mem.h"
#include "interrupt.h"

namespace delay
{
	
// Address Inits
extern uint8_t* tccr1b;
extern uint8_t* timsk1;
extern uint8_t* sreg;
extern uint8_t* ocr1ah;
extern uint8_t* ocr1al;
extern uint8_t* tcnt1h;
extern uint8_t* tcnt1l;

ISR_SIG(TIMER1_COMPA_vect)

void init();
void delayTicks(uint16_t ticks);
void delayMS(uint16_t ms);

} // end namespace delay
