#pragma once

class CPUSupport
{
    private:
        // Registers for CPUID
        static void CPUID(int code, unsigned int* a, unsigned int* b, unsigned int* c, unsigned int* d);
    public:
        typedef enum class CPUFeature {
            // Bit in register ECX
            SSE3 = 0,
            PCLMULQDQ = 1,
            DTES64 = 2,
            MONITOR = 3,
            DS_CPL = 4,
            VMX = 5,
            SMX = 6,
            EIST = 7,
            TM2 = 8,
            SSSE3 = 9,
            CNXT_ID = 10,
            SDBG = 11,
            FMA = 12,
            CMPXCHG16B = 13,
            xTPR = 14,
            PDCM = 15,
            PCID = 17,
            DCA = 18,
            SSE4_1 = 19,
            SSE4_2 = 20,
            x2APIC = 21,
            MOVBE = 22,
            POPCNT = 23,
            AES = 25,
            XSAVE = 26,
            OSXSAVE = 27,
            AVX = 28,
            F16C = 29,
            RDRAND = 30,
            // Bit in register EDX
            FPU = 0,
            VME = 1,
            DE = 2,
            PSE = 3,
            TSC = 4,
            MSR = 5,
            PAE = 6,
            MCE = 7,
            CX8 = 8,
            APIC = 9,
            SEP = 11,
            MTRR = 12,
            PGE = 13,
            MCA = 14,
            CMOV = 15,
            PAT = 16,
            PSE36 = 17,
            PSN = 18,
            CLFSH = 19,
            DS = 21,
            ACPI = 22,
            MMX = 23,
            FXSR = 24,
            SSE = 25,
            SSE2 = 26,
            SS = 27,
            HTT = 28,
            TM = 29,
            PBE = 31
        } CPUFeature;
        static bool CPUSupportCheckFor(CPUFeature Feature);
};