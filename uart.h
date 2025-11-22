#pragma once
// @file:	uart.h
// @author: sramos
// @brief:	UART Init and functionality

#include "mem.h"
#include "delay.h"
#include "interrupt.h"

class Uart_driver_t
{
public:
	Uart_driver_t();
	~Uart_driver_t();
	void init();
	void transmitMessage(const uint8_t* msg, uint8_t cnt);
	
private:
	void loadInitMessage();
	uint8_t countChars(const char* msg);
	void transmitByte(uint8_t data);
	void setBaud(uint32_t rate);

	uint8_t* _udr0		= (uint8_t*)mem_map::UDR0;
	uint8_t* _ucsr0b	= (uint8_t*)mem_map::UCSR0B;
	uint8_t* _ubrr0h	= (uint8_t*)mem_map::UBRR0H;
	uint8_t* _ubrr0l	= (uint8_t*)mem_map::UBRR0L;
	bool	 _txByteComplete = true;
	
	ISR(UART_TX_vect)
	{
		_txByteComplete = true;
	}
};