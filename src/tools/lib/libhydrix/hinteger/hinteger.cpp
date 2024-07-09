#include <libhydrix/hinteger/hinteger.h>

int Integer::ParseInt(string str)
{
    int result = 0;
    int sign = 1;
    int i = 0;
    if (str[0] == '-')
    {
        sign = -1;
        i++;
    }
    for (; i < strlen(str); i++)
    {
        result = result * 10 + str[i] - '0';
    }
    return sign * result;
}

string Integer::ToString(int value)
{
    return to_string(value);
}