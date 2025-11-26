// @file:	mem.h
// @author: sramos
// @brief:	Declaration of memory utilities and memory map of registers in ATMEGA328P

#pragma once

#include <stdint.h>

namespace mem
{
	enum class Write_mode_e
	{
		AND,	// Value gets AND'd into current register value
		OR,		// Value gets OR'd into current register value
		SET		// Will overwrite previous value
	};

	enum class Clear_mode_e
	{
		ALL,		// Entire value in the register is cleared
		PARTIAL		// Only specified bits in the register are cleared
	};

	void writeReg(uint8_t* reg, uint8_t value, Write_mode_e wr_mode = Write_mode_e::OR);
	void clearReg(uint8_t* reg, uint8_t clear_val = 0, Clear_mode_e clr_mode = Clear_mode_e::ALL);
} // endnamespace mem

namespace mem_map
{
	const uint8_t UDR0		= 0xc6;
	const uint8_t UBRR0H	= 0xc5;
	const uint8_t UBRR0L	= 0xc4;
	// ...
	const uint8_t UCSR0C	= 0xc2;
	const uint8_t UCSR0B	= 0xc1;
	const uint8_t UCSR0A	= 0xc0;
	// ...
	const uint8_t OCR1BH	= 0x8b;
	const uint8_t OCR1BL	= 0x8a;
	const uint8_t OCR1AH	= 0x89;
	const uint8_t OCR1AL	= 0x88;
	const uint8_t ICR1H		= 0x87;
	const uint8_t ICR1L		= 0x86;
	const uint8_t TCNT1H	= 0x85;
	const uint8_t TCNT1L	= 0x84;
	// ...
	const uint8_t TCCR1C	= 0x82;
	const uint8_t TCCR1B	= 0x81;
	const uint8_t TCCR1A	= 0x80;
	// ...
	const uint8_t TIMSK2	= 0x70;
	const uint8_t TIMSK1	= 0x6f;
	const uint8_t TIMSK0	= 0x6e;
	// ... 
	const uint8_t SREG		= 0x5f;
	// ...
	const uint8_t TIFR2		= 0x37;
	const uint8_t TIFR1		= 0x36;
	const uint8_t TIFR0		= 0x35;
	// ...
	const uint8_t PORTD		= 0x2b;
	const uint8_t DDRD		= 0x2a;
	const uint8_t PIND		= 0x29;
	const uint8_t PORTC		= 0x28;
	const uint8_t DDRC		= 0x27;
	const uint8_t PINC		= 0x26;
	const uint8_t PORTB		= 0x25;
	const uint8_t DDRB		= 0x24;
	const uint8_t PINB		= 0x23;
	const uint8_t IO_REGs	= 0x23;	
	// ...
}
