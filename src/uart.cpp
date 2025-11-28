// @file:	uart.cpp
// @author: sramos
// @brief:	UART Init and functionality

#include <stdint.h>
#include "uart.h"
#include "utils.h"
#include "mem.h"

Uart_driver_t::Uart_driver_t()
{
	
}

Uart_driver_t::~Uart_driver_t()
{
	
}

void Uart_driver_t::initTransmitter()
{
	setBaud(115200);	// Hardcoded
	mem::writeReg(_ucsr0b, 0x08);	// Enable Transmitter
	mem::writeReg(_ucsr0b, 0x40);	// Enable Tx Complete Interrupt
	sei();
	loadInitMessage();
}

void Uart_driver_t::initReceiver()
{
	setBaud(115200);	// Hardcoded
	mem::writeReg(_ucsr0b, 0x10);	// Enable Receiver
	mem::writeReg(_ucsr0b, 0x80);	// Enable Rx Complete Interrupt
	sei();
}

void Uart_driver_t::setBaud(uint32_t rate)
{
	// To get baud rate reg value, use: UBBR = (f_osc / (16 * BR)) - 1
	static const uint32_t F_OSC = 16000000; // Clock speed
	uint16_t baudRateReg = uint16_t(utils::round(F_OSC / (16.0f * rate)) - 1);

	// Shift the 16-bit value into two 8-bit values (high & low) accordingly
	mem::writeReg(_ubrr0h, (uint8_t)((baudRateReg & 0xff00) >> 8), mem::Write_mode_e::SET);
	mem::writeReg(_ubrr0l, (uint8_t)(baudRateReg & 0x00ff), mem::Write_mode_e::SET);
}

void Uart_driver_t::transmitByte(uint8_t data)
{
	mem::writeReg(_udr0, data, mem::Write_mode_e::SET);
}

void Uart_driver_t::transmitMessage(const uint8_t* msg, uint8_t cnt)
{
	bool txMessageComplete = false;
	setByteComplete();
	uint8_t byteNum = 0;
	
	while(!txMessageComplete)
	{
		if(_txByteComplete)
		{
			// Time to send another byte
			if (byteNum < cnt)
			{
				transmitByte(msg[byteNum++]);
				_txByteComplete = false;
			}
			else
			{
				// ... unless we finished the message
				txMessageComplete = true;
			}
		}
	}
}

void Uart_driver_t::readByte()
{
	_lastByte = mem::readReg(_udr0);
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