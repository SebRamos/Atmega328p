// @file:	lcd_intf.h
// @author: sramos
// @brief:	LCD 1602a interface declarations

#pragma once

#include <stdint.h>

namespace lcd 
{
    enum class pin_e : uint8_t 
    {
        RS,
        RW,
        E,
        DB7,
        DB6,
        DB5,
        DB4,
        DB3,
        DB2,
        DB1,
        DB0
    };

    enum class output_e : uint8_t 
    {
        HIGH,
        LOW
    };

    void init();    
    void clear_disp();
    void return_home();
    void entry_mode_set(bool id, bool shift);
    void disp_control(bool dispOn, bool cursOn, bool blnkOn);
    void curs_disp_shift(bool setCurs, bool rightLeft);
    void func_set(bool dataIntf, bool numLines, bool fontSz);
}   // end namespace lcd