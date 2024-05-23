#pragma once
#include "stdint.h"
#include "stddef.h"
#include "../hstring/string.h"
class Integer
{
    public:
        static int ParseInt(string str);
        static string ToString(int value);
};