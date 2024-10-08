#pragma once

#include <cstdint>
#include "gpio.h"

namespace bsp
{
    class can
    {
    private:
        /* init parameters */
        struct can_param
        {
        };

    public:
        can(/* args */);
        ~can();
    };

    can::can(/* args */)
    {
    }

    can::~can()
    {
    }

}