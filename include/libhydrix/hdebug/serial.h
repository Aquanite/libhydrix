#pragma once

class Debugger
{
    public:
    #define COM1 0x3F8

    static void DebugPrint(const char* str);

    static void CLIHalt();
    static void STIHalt();
};