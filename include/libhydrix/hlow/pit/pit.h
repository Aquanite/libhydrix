#pragma once
#include <stdint.h>
#include <libhydrix/hlow/cpu/cpu.h>
void timer_handler(registers_t *r);
void set_pit_freq(uint64_t freq);
void wait(uint64_t ticks);

extern volatile uint64_t global_tick;
#define MS2PIT(ms) (100 / (ms))
#define PIT2MS(freq) (100 / (freq))
#define PIT_DEF_FREQ 100
void sleep(uint64_t sec);
void msleep(uint64_t msec);