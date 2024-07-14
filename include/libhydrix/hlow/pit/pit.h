#pragma once
#include <stdint.h>
#include <libhydrix/hlow/cpu/cpu.h>
void PITTimerHandler(registers_t *r);
void SetPITFrequency(uint64_t freq);
void PITWait(uint64_t ticks);

extern volatile uint64_t global_tick;
#define MS2PIT(ms) (100 / (ms))
#define PIT2MS(freq) (100 / (freq))
#define PIT_DEF_FREQ 100
void PITSleepS(uint64_t sec);
void PITSleepMS(uint64_t msec);