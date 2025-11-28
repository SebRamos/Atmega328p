// @file:	mem.cpp
// @author: sramos
// @brief:	Implementation of memory utilities

#include "mem.h"

namespace mem
{
	void writeReg(uint8_t* reg, uint8_t value, Write_mode_e wr_mode)
	{
		if (reg != nullptr)
		{
			switch (wr_mode)
			{
				case Write_mode_e::AND:
					*reg &= value;
				break;

				case Write_mode_e::OR:
					*reg |= value;
				break;

				case Write_mode_e::SET:
					*reg = value;
				break;

				default:
					// Should never enter here
				break;
			}
		}
		else
		{
			// @todo: impement error prints
			// print_err
		}
	}

	void clearReg(uint8_t* reg, uint8_t clear_val, Clear_mode_e clr_mode)
	{
		if (reg != nullptr)
		{
			switch (clr_mode)
			{
				case Clear_mode_e::ALL:
					*reg = 0;
				break;

				case Clear_mode_e::PARTIAL:
					// Invert the bits, then AND into the current value to clear specified 
					*reg &= ~clear_val;	
				break;

				default:
					// Should never enter here
				break;
			}
		}
		else
		{
			// @todo: impement error prints
			// print_err
		}
	}	

	uint8_t readReg(uint8_t* reg)
	{
		const uint8_t ERR_VAL = 0xff; // some error value. Put this somewhere else?
		uint8_t value = 0;

		if (reg != nullptr)
		{
			value = *reg;
		}
		else
		{
			// @todo: implement error prints
			// print_err
			value = ERR_VAL;
		}

		return value;
	}
} // end namespace mem