#pragma once
#include <stdint.h>
#include <stddef.h>

/// @brief Read a byte from a port
/// @param port The port
/// @return The byte read
uint8_t inb(uint16_t port);
/// @brief Write a byte to a port
/// @param port The port
/// @param data The byte to write
void outb(uint16_t port, uint8_t data);
/// @brief Read a word from a port
/// @param port The port
/// @return The word read
uint16_t inw(uint16_t port);
/// @brief Write a word to a port
/// @param port The port
/// @param data The word to write
void outw(uint16_t port, uint16_t data);
/// @brief Read a double word from a port
/// @param port The port
/// @return The double word read
uint32_t inl(uint16_t port);
/// @brief Write a double word to a port
/// @param port The port
void outl(uint16_t port, uint32_t data);
/// @brief Wait for I/O to complete
void iowait(void);