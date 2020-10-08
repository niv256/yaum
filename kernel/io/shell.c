#include <etc/modules.h>
#include <etc/shutdown.h>
#include <etc/tools.h>
#include <io/screen.h>
#include <io/shell.h>
#include <string.h>

void user_input(char *input) {
  uint32_t ret;
  char trimmed[256];
  trim(trimmed, 256, input);

  terminal_newline();
  if (strcmp(trimmed, "java")) {
    terminal_writestring("haha c go brrrrrrrr\n");
  } else if (strcmp(trimmed, "shutdown")) {
    shutdown();
  } else if (strcmp(trimmed, "reboot")) {
    reboot();
  } else if (!execute_module(trimmed, &ret)) {
    terminal_writestring("return value: ");
    terminal_writehex(ret);
    terminal_newline();
  } else if (strcmp(trimmed, "")) {
    terminal_writestring("at least say SOMETHING...\n");
  } else {
    terminal_writestring("stop saying nonsense, that's not even a command!\n");
  }

  terminal_writestring("> ");
}
