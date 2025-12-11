// @file:	lcd_intf.cpp
// @author: sramos
// @brief:	LCD 1602a interface implementations

#include "lcd_intf.h"
#include "io.h"
#include "delay.h"

namespace lcd
{
    static void set_lcd_ddr();
    static void set_output(pin_e pin, output_e output);
    static void operation_enable();
    static inline bool check_bit(uint8_t character, uint8_t position) { return ((character & position) == position); }
    void send_char(uint8_t character);

    void init()
    {
        set_lcd_ddr();
        set_output(pin_e::E, output_e::LOW); // Keep operation enable HIGH since it's falling-edge triggered

        uint16_t delay = 10;

        delay::delayMS(delay);
        return_home();
        delay::delayMS(delay);
        operation_enable();

        delay::delayMS(delay);
        clear_disp();
        delay::delayMS(delay);
        operation_enable();

        delay::delayMS(delay);
        func_set(true, true, false);
        delay::delayMS(delay);
        operation_enable();

        delay::delayMS(delay);
        disp_control(true, true, true);
        delay::delayMS(delay);
        operation_enable();

        for( int i = 0; i < 20; ++i)
        {
            static uint8_t start_char = '!';
            delay::delayMS(delay);
            send_char(start_char++);
            delay::delayMS(delay);
            operation_enable();
        }
    }

    void set_lcd_ddr()
    {
        // Bank D
        io::set_ddr(io::reg_map->DDRD, io::pin_e::PIN3, io::direction_e::OUTPUT);	// RS
        io::set_ddr(io::reg_map->DDRD, io::pin_e::PIN4, io::direction_e::OUTPUT);	// RW
        io::set_ddr(io::reg_map->DDRD, io::pin_e::PIN5, io::direction_e::OUTPUT);	// E
        io::set_ddr(io::reg_map->DDRD, io::pin_e::PIN6, io::direction_e::OUTPUT);	// D0
        io::set_ddr(io::reg_map->DDRD, io::pin_e::PIN7, io::direction_e::OUTPUT);	// D1

        // Bank C
        io::set_ddr(io::reg_map->DDRB, io::pin_e::PIN0, io::direction_e::OUTPUT);	// D2
        io::set_ddr(io::reg_map->DDRB, io::pin_e::PIN1, io::direction_e::OUTPUT);	// D3
        io::set_ddr(io::reg_map->DDRB, io::pin_e::PIN2, io::direction_e::OUTPUT);	// D4
        io::set_ddr(io::reg_map->DDRB, io::pin_e::PIN3, io::direction_e::OUTPUT);	// D5
        io::set_ddr(io::reg_map->DDRB, io::pin_e::PIN4, io::direction_e::OUTPUT);	// D6
        io::set_ddr(io::reg_map->DDRB, io::pin_e::PIN5, io::direction_e::OUTPUT);	// D7
    }

    void set_output(pin_e pin, output_e output)
    {
        uint8_t* io_reg = nullptr;
        io::pin_e io_pin = io::pin_e::PIN0;
        io::output_e io_output = io::output_e::LOW;

        switch (output)
        {
            case output_e::HIGH:
                io_output = io::output_e::HIGH;
            break;

            case output_e::LOW:
                io_output = io::output_e::LOW;
            break;

            default:
                // should never enter here
            break;
        }

        switch (pin)
        {
            case pin_e::RS:
                io_reg = &io::reg_map->PORTD;
                io_pin = io::pin_e::PIN3;
            break;

            case pin_e::RW:
                io_reg = &io::reg_map->PORTD;
                io_pin = io::pin_e::PIN4;
            break;

            case pin_e::E:
                io_reg = &io::reg_map->PORTD;
                io_pin = io::pin_e::PIN5;
            break;

            case pin_e::DB7:
                io_reg = &io::reg_map->PORTB;
                io_pin = io::pin_e::PIN5;
            break;

            case pin_e::DB6:
                io_reg = &io::reg_map->PORTB;
                io_pin = io::pin_e::PIN4;
            break;

            case pin_e::DB5:
                io_reg = &io::reg_map->PORTB;
                io_pin = io::pin_e::PIN3;
            break;

            case pin_e::DB4:
                io_reg = &io::reg_map->PORTB;
                io_pin = io::pin_e::PIN2;
            break;

            case pin_e::DB3:
                io_reg = &io::reg_map->PORTB;
                io_pin = io::pin_e::PIN1;
            break;

            case pin_e::DB2:
                io_reg = &io::reg_map->PORTB;
                io_pin = io::pin_e::PIN0;
            break;

            case pin_e::DB1:
                io_reg = &io::reg_map->PORTD;
                io_pin = io::pin_e::PIN7;
            break;

            case pin_e::DB0:
                io_reg = &io::reg_map->PORTD;
                io_pin = io::pin_e::PIN6;
            break;

            default:
                // should never enter here
            break;
        }

        io::set_output(*io_reg, io_pin, io_output);
    }

    void operation_enable()
    {
        set_output(pin_e::E, output_e::LOW);    // Write intruction on falling edge
        delay::delayMS(10);                     // ... no delay required. data setup time = 10ns, data hold time = 40ns (MIN)
        set_output(pin_e::E, output_e::HIGH);   // Reset to HIGH for next instruction
    }

    void clear_disp()
    {
        set_output(pin_e::RS,  output_e::LOW);
        set_output(pin_e::RW,  output_e::LOW);
        set_output(pin_e::DB7, output_e::LOW);
        set_output(pin_e::DB6, output_e::LOW);
        set_output(pin_e::DB5, output_e::LOW);
        set_output(pin_e::DB4, output_e::LOW);
        set_output(pin_e::DB3, output_e::LOW);
        set_output(pin_e::DB2, output_e::LOW);
        set_output(pin_e::DB1, output_e::LOW);
        set_output(pin_e::DB0, output_e::HIGH);
    }

    void return_home()
    {
        set_output(pin_e::RS,  output_e::LOW);
        set_output(pin_e::RW,  output_e::LOW);
        set_output(pin_e::DB7, output_e::LOW);
        set_output(pin_e::DB6, output_e::LOW);
        set_output(pin_e::DB5, output_e::LOW);
        set_output(pin_e::DB4, output_e::LOW);
        set_output(pin_e::DB3, output_e::LOW);
        set_output(pin_e::DB2, output_e::LOW);
        set_output(pin_e::DB1, output_e::HIGH);
        set_output(pin_e::DB0, output_e::LOW);  // Don't care
    }

    void entry_mode_set(bool id, bool shift)
    {
        set_output(pin_e::RS,  output_e::LOW);
        set_output(pin_e::RW,  output_e::LOW);
        set_output(pin_e::DB7, output_e::LOW);
        set_output(pin_e::DB6, output_e::LOW);
        set_output(pin_e::DB5, output_e::LOW);
        set_output(pin_e::DB4, output_e::LOW);
        set_output(pin_e::DB3, output_e::LOW);
        set_output(pin_e::DB2, output_e::HIGH);
        set_output(pin_e::DB1, id ? output_e::HIGH : output_e::LOW);        // Cursor move direction
        set_output(pin_e::DB0, shift ? output_e::HIGH : output_e::LOW);     // Specified display shift
    }

    void disp_control(bool dispOn, bool cursOn, bool blnkOn)
    {
        set_output(pin_e::RS,  output_e::LOW);
        set_output(pin_e::RW,  output_e::LOW);
        set_output(pin_e::DB7, output_e::LOW);
        set_output(pin_e::DB6, output_e::LOW);
        set_output(pin_e::DB5, output_e::LOW);
        set_output(pin_e::DB4, output_e::LOW);
        set_output(pin_e::DB3, output_e::HIGH);
        set_output(pin_e::DB2, dispOn ? output_e::HIGH : output_e::LOW);    // D=1 entire disp on
        set_output(pin_e::DB1, cursOn ? output_e::HIGH : output_e::LOW);    // C=1 Cursor on
        set_output(pin_e::DB0, blnkOn ? output_e::HIGH : output_e::LOW);    // B=1 Blinking cursor on
    }

    void curs_disp_shift(bool setCurs, bool rightLeft)
    {
        set_output(pin_e::RS,  output_e::LOW);
        set_output(pin_e::RW,  output_e::LOW);
        set_output(pin_e::DB7, output_e::LOW);
        set_output(pin_e::DB6, output_e::LOW);
        set_output(pin_e::DB5, output_e::LOW);
        set_output(pin_e::DB4, output_e::HIGH);
        set_output(pin_e::DB3, setCurs ? output_e::HIGH : output_e::LOW);
        set_output(pin_e::DB2, rightLeft ? output_e::HIGH : output_e::LOW);
        set_output(pin_e::DB1, output_e::LOW);  // Don't care
        set_output(pin_e::DB0, output_e::LOW);  // Don't care
    }

    void func_set(bool dataIntf, bool numLines, bool fontSz)
    {
        set_output(pin_e::RS,  output_e::LOW);
        set_output(pin_e::RW,  output_e::LOW);
        set_output(pin_e::DB7, output_e::LOW);
        set_output(pin_e::DB6, output_e::LOW);
        set_output(pin_e::DB5, output_e::HIGH);
        set_output(pin_e::DB4, dataIntf ? output_e::HIGH : output_e::LOW);  // Interface data is 8/4 bits
        set_output(pin_e::DB3, numLines ? output_e::HIGH : output_e::LOW);  // Num of lines is 2/1
        set_output(pin_e::DB2, fontSz ? output_e::HIGH : output_e::LOW);    // Font size is 5x11/5x8
        set_output(pin_e::DB1, output_e::LOW);  // Don't care
        set_output(pin_e::DB0, output_e::LOW);  // Don't care
    }

    void send_char(uint8_t character)
    {
        set_output(pin_e::RS,  output_e::HIGH);
        set_output(pin_e::RW,  output_e::LOW);
        set_output(pin_e::DB7, check_bit(character, 0x80) ? output_e::HIGH : output_e::LOW);
        set_output(pin_e::DB6, check_bit(character, 0x40) ? output_e::HIGH : output_e::LOW);
        set_output(pin_e::DB5, check_bit(character, 0x20) ? output_e::HIGH : output_e::LOW);
        set_output(pin_e::DB4, check_bit(character, 0x10) ? output_e::HIGH : output_e::LOW);
        set_output(pin_e::DB3, check_bit(character, 0x08) ? output_e::HIGH : output_e::LOW);
        set_output(pin_e::DB2, check_bit(character, 0x04) ? output_e::HIGH : output_e::LOW);
        set_output(pin_e::DB1, check_bit(character, 0x02) ? output_e::HIGH : output_e::LOW);
        set_output(pin_e::DB0, check_bit(character, 0x01) ? output_e::HIGH : output_e::LOW);
    }
}   // end namespace lcd