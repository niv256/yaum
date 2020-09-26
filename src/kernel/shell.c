#include "shell.h"
#include "../include/string.h"
#include "screen.h"
#include "shutdown.h"

void user_input(char *input) {
  char trimmed[256];
  trim(trimmed, 256, input);

  terminal_putchar('\n');
  if (strcmp(trimmed, "java")) {
    terminal_writestring("haha c go brrrrrrrr\n");
  } else if (strcmp(trimmed, "shutdown")) {
    shutdown();
  } else if (strcmp(trimmed, "reboot")) {
    reboot();
  } else if (strcmp(trimmed, "")) {
    terminal_writestring("at least say SOMETHING...\n");
  } else {
    terminal_writestring("stop saying nonsense, that's not even a command!\n");
  }

  terminal_writestring("> ");
}
