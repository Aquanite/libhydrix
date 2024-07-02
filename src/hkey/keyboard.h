#pragma once
#include "../hlow/cpu/cpu.h"
#include "../hcon/console.h"
#include <stdint.h>
static inline bool GetKeyDown(char scancode);
void keyboard_handler(registers_t *r);
void Keyboard_Init(Console* console);
void DisableKeyboard();
void EnableKeyboard();
uint64_t Keyboard_GetKey();