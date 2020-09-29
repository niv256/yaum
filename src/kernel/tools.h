#ifndef TOOLS_H
#define TOOLS_H

#include "../include/stdint.h"

void outb(uint16_t port, uint8_t val);
void outw(uint16_t port, uint16_t val);
uint8_t inb(uint16_t port);
char switch_case(char c);
char *binrep(char *dst, uint8_t num);

/*
uint8_t inw(uint16_t port);
uint8_t inl(uint16_t port);
*/

#endif
