#include <stdint.h>

#ifndef ISR_H
#define ISR_H

struct registers {
	// single push
	uint16_t ds;

	// pusha
	uint16_t edi;
	uint16_t esi;
	uint16_t ebp;
	uint16_t esp;
	uint16_t ebx;
	uint16_t edx;
	uint16_t ecx;
	uint16_t eax;

	// push in macro
	uint16_t int_num;
	uint16_t err_code;
};

#endif
