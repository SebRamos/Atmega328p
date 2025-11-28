// @file:	main.cpp
// @author: sramos
// @brief:	Top level execution containing main loop

#include <stdint.h>
#include "io.h"
#include "delay.h"
#include "uart.h"

Uart_driver_t uart;
volatile bool delayChangeFlag = true;

// @todo: MOVE THIS OUTTA HERE !

ISR(UART_RX_vect)
{
	uart.readByte();
	delayChangeFlag = true;
}

int main()
{
	set_ddr(io_reg->DDRB, PIN5, IO_dir_e::OUTPUT);
	delay::init();
	uart.initReceiver();
	uint16_t delay = 0;

    while (1) 
    {
		if (delayChangeFlag)
		{
			volatile uint8_t lastByte = uart.getLastByte();

			if ((lastByte == '1') || (lastByte == 1))
			{
				delay = 0;
			}
			else
			{
				delay += lastByte;
			}

			delayChangeFlag = false;
		}

	 	delay::delayMS(delay);
	 	set_output(io_reg->PORTB, PIN5, IO_out_e::TOGGLE);
    }
}

