#pragma once
#include <stdint.h>
#include <stddef.h>

#define PIC1		0x20		/* IO base address for master PIC */
#define PIC2		0xA0		/* IO base address for slave PIC */
#define PIC1_COMMAND	PIC1
#define PIC1_DATA	(PIC1+1)
#define PIC2_COMMAND	PIC2
#define PIC2_DATA	(PIC2+1)
#define ICW1_ICW4	0x01		/* Indicates that ICW4 will be present */
#define ICW1_SINGLE	0x02		/* Single (cascade) mode */
#define ICW1_INTERVAL4	0x04		/* Call address interval 4 (8) */
#define ICW1_LEVEL	0x08		/* Level triggered (edge) mode */
#define ICW1_INIT	0x10		/* Initialization - required! */
#define ICW4_8086	0x01		/* 8086/88 (MCS-80/85) mode */
#define ICW4_AUTO	0x02		/* Auto (normal) EOI */
#define ICW4_BUF_SLAVE	0x08		/* Buffered mode/slave */
#define ICW4_BUF_MASTER	0x0C		/* Buffered mode/master */
#define ICW4_SFNM	0x10		/* Special fully nested (not) */
#define PIC_EOI		0x20
#define PIC_READ_IRR                0x0a    /* OCW3 irq ready next CMD read */
#define PIC_READ_ISR                0x0b    /* OCW3 irq service next CMD read */
/// @brief Send an End of Interrupt to the PIC
/// @param irq The IRQ number
void SendPICEndOfInterrupt(uint8_t irq);
/// @brief Remap the PIC
/// @param offset1 The offset for the master PIC
/// @param offset2 The offset for the slave PIC
void RemapPIC(int offset1, int offset2);
/// @brief Disable the PIC
void DisablePIC();
/// @brief Set mask for IRQ line
/// @param IRQline The IRQ line
void SetIRQMask(uint8_t IRQline);
/// @brief Clear mask for IRQ line
/// @param IRQline The IRQ line
void ClearIRQMask(uint8_t IRQline);
/// @brief Get the Interrupt Request Register
uint16_t GetPICIrr(void);
/// @brief Get the In-Service Register
uint16_t GetPICIsr(void);