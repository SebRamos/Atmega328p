// @file:	utils.h
// @author: sramos
// @brief:	Common utilities for basic processing

#pragma once

namespace utils
{
    // @brief: Will round a floating point value by nearest integer value (half up)
    int round(float input)
    {   
        if (input >= 0)
        {
            return (int)(input + 0.5f);
        }
        else
        {
            return (int)(input - 0.5f);
        }
    }
    
} // end namespace utils