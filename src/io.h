// @file:	io.h
// @author: sramos
// @brief:	Input/Output register definitions and helper function declarations

#pragma once

#include "mem.h"

namespace io
{
enum class direction_e : uint8_t
{
	INPUT  = 0,
	OUTPUT = 1
};

enum class output_e : uint8_t
{
	LOW = 0,
	HIGH = 1,
	TOGGLE = 2
};

enum class pin_e : uint8_t
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

struct Reg_map_t
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

void set_ddr(uint8_t& reg, pin_e pin, direction_e direction);
void set_output(uint8_t& reg, pin_e pin, output_e output);

// Setting Actual IO register address in ATMEGA328P
extern Reg_map_t* reg_map;

}	// end namespace io
