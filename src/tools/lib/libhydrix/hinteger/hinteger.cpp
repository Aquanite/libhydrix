#include <libhydrix/hinteger/hinteger.h>

int Integer::ParseInt(string str)
{
    int result = 0;
    int Sign = 1;
    int i = 0;
    if (str[0] == '-')
    {
        Sign = -1;
        i++;
    }
    for (; i < StringLength(str); i++)
    {
        result = result * 10 + str[i] - '0';
    }
    return Sign * result;
}