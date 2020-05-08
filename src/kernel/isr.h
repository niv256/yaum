#include <stdint.h>

#ifndef ISR_H
#define ISR_H

/*struct registers {
	// single push
	uint32_t ds;

	// pusha
	uint32_t edi;
	uint32_t esi;
	uint32_t ebp;
	uint32_t esp;
	uint32_t ebx;
	uint32_t edx;
	uint32_t ecx;
	uint32_t eax;

	// push in macro
	uint32_t int_num;
	uint32_t err_code;
};*/

struct registers
{
	unsigned int ds;
	unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
	unsigned int int_num, err_code;
	unsigned int eip, cs, eflags, useresp, ss;
} ;

#endif
