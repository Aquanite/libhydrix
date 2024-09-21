#pragma once
#include <stdint.h>
#include <libhydrix/hlow/cpu/cpu.h>
void PITTimerHandler(registers_t *r);
void SetPITFrequency(uint64_t freq);
uint64_t TimeGetMilliseconds();

extern volatile uint64_t global_tick;
#define MS2PIT(ms) (ms / 1000)
#define PIT2MS(freq) (1000 / freq)
#define PIT_DEF_FREQ 100
void PITSleepS(uint64_t sec);
void PITSleepMS(uint64_t msec);