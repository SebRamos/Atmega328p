// @file:	uart.cpp
// @author: sramos
// @brief:	UART Init and functionality
#include <stdint.h>
#include "uart.h"

Uart_driver_t::Uart_driver_t()
{
	
}

Uart_driver_t::~Uart_driver_t()
{
	
}

void Uart_driver_t::init()
{
	setBaud(115200);	// Hardcoded
	*_ucsr0b |= 0x08;	// Enable Transmitter
	*_ucsr0b |= 0x40;	// Enable Tx Complete Interrupt
	sei();
	loadInitMessage();
}

void Uart_driver_t::setBaud(uint32_t rate)
{
	// TODO: Temp hardcode. Make "rate" actually change
	*_ubrr0h = 0x00;
	*_ubrr0l = 0x08; // UBRR0 = 8. BR = 115200 @ 16.0 MHz
}

void Uart_driver_t::transmitByte(uint8_t data)
{
	*_udr0 = data;
}

void Uart_driver_t::transmitMessage(const uint8_t* msg, uint8_t cnt)
{
	bool txMessageComplete = false;
	_txByteComplete = true;
	uint8_t byteNum = 0;
	
	while(!txMessageComplete)
	{
		if(_txByteComplete)
		{
			if (byteNum < cnt)
			{
				transmitByte(msg[byteNum++]);
				_txByteComplete = false;
			}
			else
			{
				txMessageComplete = true;
			}
		}
	}
}

uint8_t Uart_driver_t::countChars(const char* msg)
{
	uint8_t cnt = 0;
	
	while (msg[cnt] != 0)
	{
		++cnt;
	}
	
	return cnt;
}

void Uart_driver_t::loadInitMessage()
{
	const char* msg[] =
	{
		"|______|______|______|______|______|______|______|______|______|______|______|______|\n",
		"    / / / /                                   / / / /\\ \\ \\ \\   |___ \\__ \\ / _ \\ \n",
		"   / / / /__ _ __ __ _ _ __ ___   ___  ___   / / / /  \\ \\ \\ \\    __) | ) | (_) |_ __\n",
		"  / / / / __| '__/ _` | '_ ` _ \\ / _ \\/ __| / / / /    \\ \\ \\ \\  |__ < / / > _ <| '_ \\ \n",
		" / / / /\\__ \\ | | (_| | | | | | | (_) \\__ \\/ / / /      \\ \\ \\ \\ ___) / /_| (_) | |_) |\n",
		"/_/_/_/ |___/_|  \\__,_|_| |_| |_|\\___/|___/_/_/_/        \\_\\_\\_\\____/____|\\___/| .__/\n",
		" ______ ______ ______ ______ ______ ______ ______ ______ ______ ______ ______  | |\n",
		"|______|______|______|______|______|______|______|______|______|______|______| |_|\n"
	};

	for (uint8_t i = 0; i < 8; ++i)
	{
		transmitMessage((const uint8_t*)msg[i], countChars(msg[i]));
	}
}