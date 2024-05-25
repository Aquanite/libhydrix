#include "fpu.h"
#include "cpuid.h"
bool __fpu_enabled__ = false;
void DoesFPUExist()
{
    uint32_t eax, ebx, ecx, edx;
    __get_cpuid(0x00000001, &eax, &ebx, &ecx, &edx);
    if (edx & (1 << 0))
    {
        __fpu_enabled__ = true;
    }
    else
    {
        __fpu_enabled__ = false;
    }
}
void FPU::Enable()
{
    DoesFPUExist();
    if (__fpu_enabled__)
    {
        __asm__ __volatile__("fninit");
    }
}
bool FPU::Is_Enabled()
{
    return __fpu_enabled__;
}