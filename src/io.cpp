// @file:	io.cpp
// @author: sramos
// @brief:	Input/Output register definitions and helper function implementations

#include <stdint.h>
#include "io.h"

namespace io
{

Reg_map_t* reg_map = (Reg_map_t*)mem_map::IO_REGs;

void set_ddr(uint8_t& reg, pin_e pin, direction_e direction)
{
    uint8_t pinPos = (1 << (uint8_t)pin);

	switch (direction)
	{
		case direction_e::OUTPUT:
		reg |= pinPos;
		break;
		
		case direction_e::INPUT:
		reg &= ~pinPos;
		break;
		
		default:
		break;
	}
}

void set_output(uint8_t& reg, pin_e pin, output_e output)
{
    uint8_t pinPos = (1 << (uint8_t)pin);

	switch (output)
	{
		case output_e::HIGH:
		reg |= pinPos;
		break;
		
		case output_e::LOW:
		reg &= ~pinPos;
		break;
		
		case output_e::TOGGLE:
		reg ^= pinPos;
		break;
		
		default:
		break;
	}
}

}   //end namespace io