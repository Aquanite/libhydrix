#include "pit.h"
#include "../../hio/io.h"
volatile uint64_t global_tick = 0;
void timer_handler(registers_t *r) {
  global_tick += 1;
}

void set_pit_freq(uint64_t freq) {
  uint16_t divisor = 1193180 / freq;

  uint8_t low = (uint8_t)(divisor & 0xFF);
  uint8_t high = (uint8_t)((divisor >> 8) & 0xFF);

  outb(0x43, 0x34);
  outb(0x40, low);
  outb(0x40, high);
}


void wait(uint64_t ticks) {
  volatile uint64_t end = global_tick + ticks;
  while (global_tick < end);
}
