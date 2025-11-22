// @file:	main.cpp
// @author: sramos
// @brief:	Top level execution containing main loop

#include <stdint.h>
#include "io.h"
#include "delay.h"
#include "uart.h"

int main()
{
	Uart_driver_t uart;
	set_ddr(io_reg->DDRB, PIN5, IO_dir_e::OUTPUT);
	delay::init();
	uart.init();

    while (1) 
    {
		delay::delayMS(500);
		set_output(io_reg->PORTB, PIN5, IO_out_e::TOGGLE);
    }
}

