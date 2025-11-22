#pragma once
// @file:	io.h
// @author: sramos
// @brief:	Input/Output register definitions and helper functions

#include "mem.h"

enum class IO_dir_e : uint8_t
{
	INPUT  = 0,
	OUTPUT = 1
};

enum class IO_out_e : uint8_t
{
	LOW = 0,
	HIGH = 1,
	TOGGLE = 2
};

enum IO_pin_e : uint8_t
{
	PIN0 = 0,
	PIN1 = 1,
	PIN2 = 2,
	PIN3 = 3,
	PIN4 = 4,
	PIN5 = 5,
	PIN6 = 6,
	PIN7 = 7
};

struct IO_Reg_t
{
	uint8_t PINB;
	uint8_t DDRB;
	uint8_t PORTB;
	uint8_t PINC;
	uint8_t DDRC;
	uint8_t PORTC;
	uint8_t PIND;
	uint8_t DDRD;
	uint8_t PORTD;
};

void set_ddr(uint8_t& reg, uint8_t pin, IO_dir_e direction)
{
	switch (direction)
	{
		case IO_dir_e::OUTPUT:
		reg |= (1 << pin);
		break;
		
		case IO_dir_e::INPUT:
		reg &= ~(1 << pin);
		break;
		
		default:
		break;
	}
}

void set_output(uint8_t& reg, uint8_t pin, IO_out_e output)
{
	switch (output)
	{
		case IO_out_e::HIGH:
		reg |= (1 << pin);
		break;
		
		case IO_out_e::LOW:
		reg &= ~(1 << pin);
		break;
		
		case IO_out_e::TOGGLE:
		reg ^= (1 << pin);
		break;
		
		default:
		break;
	}
}

// Setting Actual IO register address in ATMEGA328P
IO_Reg_t* io_reg = (IO_Reg_t*)mem_map::IO_REGs;
