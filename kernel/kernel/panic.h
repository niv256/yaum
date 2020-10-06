#ifndef PANIC_H
#define PANIC_H

void panic(char *panic_msg, char *file, int line);

#define PANIC(panic_msg) panic(panic_msg, __FILE__, __LINE__);

#endif
