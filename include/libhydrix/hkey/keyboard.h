#pragma once
#include <libhydrix/hlow/cpu/cpu.h>
#include <libhydrix/hcon/console.h>
#include <stdint.h>
bool GetKeyDown(char scancode);
void KeyboardHandler(registers_t *r);
void KeyboardInit(Console* console);
void DisableKeyboard();
void EnableKeyboard();
uint64_t KeyboardGetKey();