#include <libhydrix/hlow/pit/pit.h>
#include <libhydrix/hio/io.h>

volatile uint64_t global_tick = 0;
uint64_t frequency = PIT_DEF_FREQ;

void timer_handler(registers_t *r) {
    global_tick += 1;
}

/// @brief Wait for a certain number of ticks
/// @param sec Seconds to wait
void sleep(uint64_t sec) {
    uint64_t target_tick = global_tick + sec * frequency;
    while (global_tick < target_tick) {
        // HLT instruction halts the CPU until the next interrupt
        asm volatile ("hlt");
    }
}

/// @brief Wait for a certain number of ticks
/// @param msec Milliseconds to wait
void msleep(uint64_t msec) {
    uint64_t target_tick = global_tick + (msec * frequency) / 1000;
    while (global_tick < target_tick) {
        asm volatile ("hlt");
    }
}

void set_pit_freq(uint64_t freq) {
    if (freq == 0) return; // avoid division by zero
    frequency = freq;
    uint64_t divisor = 1193180 / freq;
    outb(0x43, 0x36); // Command byte
    outb(0x40, divisor & 0xFF); // Low byte of divisor
    outb(0x40, (divisor >> 8) & 0xFF); // High byte of divisor
}
