#pragma once
#include <libhydrix/hlow/cpu/cpu.h>
#include <libhydrix/hcon/console.h>
#include <stdint.h>
bool GetKeyDown(char scancode);
void keyboard_handler(registers_t *r);
void Keyboard_Init(Console* console);
void DisableKeyboard();
void EnableKeyboard();
uint64_t Keyboard_GetKey();