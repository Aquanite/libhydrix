#include <libhydrix/hlow/pic/pic.h>
#include <libhydrix/hio/io.h>
void SendPICEndOfInterrupt(uint8_t irq)
{
	if(irq >= 8)
		PortIO::OutByte(PIC2_COMMAND,PIC_EOI);
 
	PortIO::OutByte(PIC1_COMMAND,PIC_EOI);
}

void RemapPIC(int offset1, int offset2)
{
	uint8_t a1, a2;
 
	a1 = PortIO::InByte(PIC1_DATA);                        // save masks
	a2 = PortIO::InByte(PIC2_DATA);
 
	PortIO::OutByte(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);  // starts the initialization sequence (in cascade mode)
	PortIO::IoPITWait();
	PortIO::OutByte(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
	PortIO::IoPITWait();
	PortIO::OutByte(PIC1_DATA, offset1);                 // ICW2: Master PIC vector offset
	PortIO::IoPITWait();
	PortIO::OutByte(PIC2_DATA, offset2);                 // ICW2: Slave PIC vector offset
	PortIO::IoPITWait();
	PortIO::OutByte(PIC1_DATA, 4);                       // ICW3: tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)
	PortIO::IoPITWait();
	PortIO::OutByte(PIC2_DATA, 2);                       // ICW3: tell Slave PIC its cascade identity (0000 0010)
	PortIO::IoPITWait();
 
	PortIO::OutByte(PIC1_DATA, ICW4_8086);               // ICW4: have the PICs use 8086 mode (and not 8080 mode)
	PortIO::IoPITWait();
	PortIO::OutByte(PIC2_DATA, ICW4_8086);
	PortIO::IoPITWait();
 
	PortIO::OutByte(PIC1_DATA, a1);   // restore saved masks.
	PortIO::OutByte(PIC2_DATA, a2);
}

void DisablePIC()
{
    PortIO::OutByte(PIC1_DATA, 0xFF);
    PortIO::OutByte(PIC2_DATA, 0xFF);
}

void SetIRQMask(uint8_t IRQline) {
    uint16_t port;
    uint8_t value;
 
    if(IRQline < 8) {
        port = PIC1_DATA;
    } else {
        port = PIC2_DATA;
        IRQline -= 8;
    }
    value = PortIO::InByte(port) | (1 << IRQline);
    PortIO::OutByte(port, value);        
}
 
void ClearIRQMask(uint8_t IRQline) {
    uint16_t port;
    uint8_t value;
 
    if(IRQline < 8) {
        port = PIC1_DATA;
    } else {
        port = PIC2_DATA;
        IRQline -= 8;
    }
    value = PortIO::InByte(port) & ~(1 << IRQline);
    PortIO::OutByte(port, value);        
}

/* Helper func */
static uint16_t __pic_get_irq_reg(int ocw3)
{
    /* OCW3 to PIC CMD to get the register values.  PIC2 is chained, and
     * represents IRQs 8-15.  PIC1 is IRQs 0-7, with 2 being the chain */
    PortIO::OutByte(PIC1_COMMAND, ocw3);
    PortIO::OutByte(PIC2_COMMAND, ocw3);
    return (PortIO::InByte(PIC2_COMMAND) << 8) | PortIO::InByte(PIC1_COMMAND);
}
 
/* Returns the combined value of the cascaded PICs irq request register */
uint16_t GetPICIrr(void)
{
    return __pic_get_irq_reg(PIC_READ_IRR);
}
 
/* Returns the combined value of the cascaded PICs in-service register */
uint16_t GetPICIsr(void)
{
    return __pic_get_irq_reg(PIC_READ_ISR);
}