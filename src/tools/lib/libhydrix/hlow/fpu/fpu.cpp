#include <libhydrix/hlow/fpu/fpu.h>
#include <cpuid.h>
bool fpu_enabled = false;
void DoesFPUExist()
{
    uint32_t eax, ebx, ecx, edx;
    __get_cpuid(0x00000001, &eax, &ebx, &ecx, &edx);
    if (edx & (1 << 0))
    {
        fpu_enabled = true;
    }
    else
    {
        fpu_enabled = false;
    }
}
void FPU::Enable()
{
    DoesFPUExist();
    if (fpu_enabled)
    {
        __asm__ __volatile__("fninit");
    }
    else
    {
        // int 0x20
        __asm__ __volatile__("int $0x20");
    }
}
bool FPU::Is_Enabled()
{
    return fpu_enabled;
}

void FPU::Init()
{

}
