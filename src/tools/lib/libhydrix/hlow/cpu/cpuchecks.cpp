#include <libhydrix/hlow/cpu/cpuchecks.h>
#include <stdint.h>
#include <stddef.h>
void CPUSupport::CPUID(int code, unsigned int* a, unsigned int* b, unsigned int* c, unsigned int* d)
{
    asm volatile("cpuid"
                 : "=a"(*a), "=b"(*b), "=c"(*c), "=d"(*d)
                 : "a"(code));
}

// Check if the CPU supports a feature
bool CPUSupport::CPUSupportCheckFor(CPUSupport::CPUFeature feature)
{
    unsigned int a, b, c, d;
    CPUID(1, &a, &b, &c, &d);
    if ((int)(feature) <= 31)
        return (c & (1 << (int)(feature))) != 0;
    else
        return (d & (1 << ((int)(feature) - 32))) != 0;
}