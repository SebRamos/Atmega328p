// @file:	main.cpp
// @author: sramos
// @brief:	Top level execution containing main loop

#include <stdint.h>
#include "io.h"
#include "delay.h"
#include "uart.h"

Uart_driver_t uart;

// @todo: MOVE THIS OUTTA HERE !
ISR(UART_TX_vect)
{
	uart.setByteComplete();
}

int main()
{
	set_ddr(io_reg->DDRB, PIN5, IO_dir_e::OUTPUT);
	delay::init();
	uart.initTransmitter();

    while (1) 
    {
	 	delay::delayMS(500);
	 	set_output(io_reg->PORTB, PIN5, IO_out_e::TOGGLE);
    }
}

