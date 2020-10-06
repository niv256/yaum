#include <etc/modules.h>
#include <etc/shutdown.h>
#include <etc/tools.h>
#include <io/screen.h>
#include <io/shell.h>
#include <string.h>

void user_input(char *input) {
  int module_index;
  char trimmed[256];
  trim(trimmed, 256, input);

  terminal_newline();
  if (strcmp(trimmed, "java")) {
    terminal_writestring("haha c go brrrrrrrr\n");
  } else if (strcmp(trimmed, "shutdown")) {
    shutdown();
  } else if (strcmp(trimmed, "reboot")) {
    reboot();
  } else if (strcmp(trimmed, "")) {
    terminal_writestring("at least say SOMETHING...\n");
  } else if ((module_index = get_exec_module_index(trimmed)) != -1) {
    uint32_t ret = execute_binary_modules(module_index);
    terminal_writestring("return value: ");
    terminal_writehex(ret);
    terminal_newline();
  } else {
    terminal_writestring("stop saying nonsense, that's not even a command!\n");
  }

  terminal_writestring("> ");
}
