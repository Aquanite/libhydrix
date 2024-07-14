#include <libhydrix/hio/io.h>
//PortIO::InByte and PortIO::OutByte
uint8_t PortIO::InByte(uint16_t port) {
    uint8_t ret;
    __asm__ __volatile__("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

void PortIO::OutByte(uint16_t port, uint8_t data) {
    __asm__ __volatile__("outb %0, %1" : : "a"(data), "Nd"(port));
}

//PortIO::InWord and PortIO::OutWord
uint16_t PortIO::InWord(uint16_t port) {
    uint16_t ret;
    __asm__ __volatile__("inw %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

void PortIO::OutWord(uint16_t port, uint16_t data) {
    __asm__ __volatile__("outw %0, %1" : : "a"(data), "Nd"(port));
}

//PortIO::InLong and PortIO::OutLong

uint32_t PortIO::InLong(uint16_t port) {
    uint32_t ret;
    __asm__ __volatile__("inl %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

void PortIO::OutLong(uint16_t port, uint32_t data) {
    __asm__ __volatile__("outl %0, %1" : : "a"(data), "Nd"(port));
}
//ioPITWait
void PortIO::IoPITWait(void) {
    InByte(0x80);
}
