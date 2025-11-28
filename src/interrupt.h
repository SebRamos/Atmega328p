// @file:	interrupt.h
// @author: sramos
// @brief:	Interrupt vector table (IVT) & Interrupt Service Routine (ISR) definitions and attributes.

#ifndef INTERRUPT_H
#define INTERRUPT_H

// Set the vector attributes to corresponding vector table symbol
// e.g. __vector_11(void) __attribute__((arg1, arg2, etc.))
// Attributes:
// signal - tells the compiler this is an interrupt handler
// used   - prevents the compiler from optimizing this setting away
// externally_visible - ensures the linker can see this
#define ISR_SIG(vector) extern "C" void vector(void) __attribute__((signal, used, externally_visible));
#define ISR(vector) void vector(void)

// Set Vector syntax to vector name in table defined in ATMEGA assembly 
// e.g. Vector 11 is __vector_11 symbol in table
#define VECTOR(N) __vector_ ## N

// Vector table
#define RESET_vect			VECTOR(0)	// External pin, power-on reset
#define TIMER1_CAPT_vect	VECTOR(10)	// Timer/Counter1 capture event
#define TIMER1_COMPA_vect	VECTOR(11)  // Timer/Counter1 Compare Match A
#define UART_RX_vect        VECTOR(18)  // UART Rx Complete
#define UART_TX_vect		VECTOR(20)  // UART Tx Complete


// GLobal functions
#define sei()	__asm__ __volatile__ ("sei" ::: "memory")	// Set interrupt Flag - Enables I-Bit in SREG
#define cli()	__asm__ __volatile__ ("cli" ::: "memory")	// Clr interrupt Flag - Cleares I-Bit in SREG

#endif