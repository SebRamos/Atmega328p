// @file:	main.cpp
// @author: sramos
// @brief:	Top level execution containing main loop

#include <stdint.h>
#include "io.h"
#include "delay.h"
#include "uart.h"
#include "lcd_intf.h"

Uart_driver_t uart;

// @todo: MOVE THIS OUTTA HERE !
ISR(UART_TX_vect)
{
	uart.setByteComplete();
}

int main()
{
	//io::set_ddr(io::reg_map->DDRB, io::pin_e::PIN5, io::direction_e::OUTPUT);
	delay::init();
	uart.initTransmitter();
	lcd::init();

    while (1) 
    {
	 	//delay::delayMS(100);
	 	//io::set_output(io::reg_map->PORTB, io::pin_e::PIN5, io::output_e::TOGGLE);
    }
}

