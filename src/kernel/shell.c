#include "shell.h"
#include "screen.h"
#include "../include/string.h"

void user_input(char *input) {
	char trimmed[256];

	terminal_putchar('\n');
	trim(trimmed, strlen(input), input);
	if (strcmp(trimmed, "java")) {
		terminal_writestring("haha c go brrrrrrrr\n");
	} else {
		terminal_writestring("stop saying nonsense, that's not even a command!\n");
	}
	
	terminal_writestring("> ");
}
