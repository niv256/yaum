#include <etc/modules.h>
#include <etc/shutdown.h>
#include <etc/tools.h>
#include <io/shell.h>
#include <stdio.h>
#include <string.h>

void user_input(char *input) {
  uint32_t ret;
  char trimmed[256];
  trim(trimmed, 256, input);

  putchar('\n');
  if (strcmp(trimmed, "java")) {
    puts("haha c go brrrrrrrr");
  } else if (strcmp(trimmed, "shutdown")) {
    shutdown();
  } else if (strcmp(trimmed, "reboot")) {
    reboot();
  } else if (!execute_module(trimmed, &ret)) {
    printf("return value: 0x%x\n", ret);
  } else if (strcmp(trimmed, "")) {
    puts("at least say SOMETHING...");
  } else {
    puts("stop saying nonsense, that's not even a command!");
  }

  printf("> ");
}
