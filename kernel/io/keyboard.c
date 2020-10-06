#include <etc/tools.h>
#include <io/keyboard.h>
#include <io/screen.h>
#include <io/shell.h>

#define MAX_KEY_VAL 0xb6

static char input_buffer[256];
static int buffer_index;
static char caps_state;
static char shift_state;

enum special_characters {
  UNKNOWN = 0,
  BACKSPACE,
  TAB,
  ENTER,
  LEFT_CTRL,
  LEFT_SHIFT,
  RIGHT_SHIFT,
  LEFT_ALT,
  SPACE,
  CAPS_LOCK,
  F1,
  F2,
  F3,
  F4,
  F5,
  F6,
  F7,
  F8,
  F9,
  F10,
  F11,
  F12,
  NUM_LOCK,
  SCROLL_LOCK,
  LEFT_SHIFT_RLS,
  RIGHT_SHIFT_RLS
};

// clang-format off
unsigned char get_ascii(unsigned char key) {
	switch (key) {
		case 0x02: return shift_state == 0 ? '1' : '!'; break;
		case 0x03: return shift_state == 0 ? '2' : '@'; break;
		case 0x04: return shift_state == 0 ? '3' : '#'; break;
		case 0x05: return shift_state == 0 ? '4' : '$'; break;
		case 0x06: return shift_state == 0 ? '5' : '%'; break;
		case 0x07: return shift_state == 0 ? '6' : '^'; break;
		case 0x08: return shift_state == 0 ? '7' : '&'; break;
		case 0x09: return shift_state == 0 ? '8' : '*'; break;
		case 0x0a: return shift_state == 0 ? '9' : '('; break;
		case 0x0b: return shift_state == 0 ? '0' : ')'; break;
		case 0x0c: return shift_state == 0 ? '-' : '_'; break;
		case 0x0d: return shift_state == 0 ? '=' : '+'; break;
		case 0x0e: return BACKSPACE;                    break;
		case 0x0f: return TAB;                          break;
		case 0x10: return 'q';                          break;
		case 0x11: return 'w';                          break;
		case 0x12: return 'e';                          break;
		case 0x13: return 'r';                          break;
		case 0x14: return 't';                          break;
		case 0x15: return 'y';                          break;
		case 0x16: return 'u';                          break;
		case 0x17: return 'i';                          break;
		case 0x18: return 'o';                          break;
		case 0x19: return 'p';                          break;
		case 0x1a: return shift_state == 0 ? '[' : '{';  break;
		case 0x1b: return shift_state == 0 ? ']' : '}';  break;
		case 0x1c: return ENTER;                        break;
		case 0x1d: return LEFT_CTRL;                    break;
		case 0x1e: return 'a';                          break;
		case 0x1f: return 's';                          break;
		case 0x20: return 'd';                          break;
		case 0x21: return 'f';                          break;
		case 0x22: return 'g';                          break;
		case 0x23: return 'h';                          break;
		case 0x24: return 'j';                          break;
		case 0x25: return 'k';                          break;
		case 0x26: return 'l';                          break;
		case 0x27: return shift_state == 0 ? ';' : ':'; break;
		case 0x28: return shift_state == 0 ? '\'' : '"';break;
		case 0x29: return shift_state == 0 ? '`' : ':'; break;
		case 0x2a: return LEFT_SHIFT;                   break;
		case 0x2b: return shift_state == 0 ? '\\' : '|';break;
		case 0x2c: return 'z';                          break;
		case 0x2d: return 'x';                          break;
		case 0x2e: return 'c';                          break;
		case 0x2f: return 'v';                          break;
		case 0x30: return 'b';                          break;
		case 0x31: return 'n';                          break;
		case 0x32: return 'm';                          break;
		case 0x33: return shift_state == 0 ? ',' : ':';  break;
		case 0x34: return shift_state == 0 ? '.' : ':';  break;
		case 0x35: return shift_state == 0 ? '/' : ':';  break;
		case 0x36: return RIGHT_SHIFT;                  break;
		case 0x37: return '*';                          break;
		case 0x38: return LEFT_ALT;                     break;
		case 0x39: return ' ';                          break;
		case 0x3a: return CAPS_LOCK;                    break;
		case 0x3b: return F1;                           break;
		case 0x3c: return F2;                           break;
		case 0x3d: return F3;                           break;
		case 0x3e: return F4;                           break;
		case 0x3f: return F5;                           break;
		case 0x40: return F6;                           break;
		case 0x41: return F7;                           break;
		case 0x42: return F8;                           break;
		case 0x43: return F9;                           break;
		case 0x44: return F10;                          break;
		case 0x45: return NUM_LOCK;                     break;
		case 0x46: return SCROLL_LOCK;                  break;
		case 0x47: return '7';                          break;
		case 0x48: return '8';                          break;
		case 0x49: return '9';                          break;
		case 0x4a: return '-';                          break;
		case 0x4b: return '4';                          break;
		case 0x4c: return '5';                          break;
		case 0x4d: return '6';                          break;
		case 0x4e: return '+';                          break;
		case 0x4f: return '1';                          break;
		case 0x50: return '2';                          break;
		case 0x51: return '3';                          break;
		case 0x52: return '0';                          break;
		case 0x53: return '.';                          break;
		case 0x57: return F11;                          break;
		case 0x58: return F12;                          break;
		case 0xaa: return LEFT_SHIFT_RLS;               break;
		case 0xb6: return RIGHT_SHIFT_RLS;              break;
		default:   return UNKNOWN;
	}
}
// clang-format on

void keyboard_init(void) {
  // init buffer
  buffer_index    = 0;
  input_buffer[0] = '\0';

  // states
  caps_state  = 0;
  shift_state = 0;

  // setup the keyboard interrupt callback
  setup_isr_callback(IRQ1, &get_key_press);
}

void reset_buffer(void) {
  buffer_index    = 0;
  input_buffer[0] = '\0';
}

void get_key_press(registers_t regs) {
  char key_val, ascii_val;
  key_val = inb(0x60);

  if (key_val > MAX_KEY_VAL) {
    return;
  }

  ascii_val = get_ascii(key_val);
  switch (ascii_val) {
    case ENTER:
      user_input(input_buffer);
      reset_buffer();
      break;
    case BACKSPACE:
      if (buffer_index == 0) {
        break;
      }

      if (terminal_deletechar()) {
        input_buffer[--buffer_index] = '\0';
      }
      break;
    case TAB:
    case LEFT_CTRL:
    case LEFT_ALT:
    case F1:
    case F2:
    case F3:
    case F4:
    case F5:
    case F6:
    case F7:
    case F8:
    case F9:
    case F10:
    case F11:
    case F12:
    case NUM_LOCK: break;
    case LEFT_SHIFT:
    case RIGHT_SHIFT: shift_state += 1; break;
    case LEFT_SHIFT_RLS:
    case RIGHT_SHIFT_RLS: shift_state -= 1; break;
    case CAPS_LOCK: caps_state = (caps_state + 1) % 2; break;
    case SCROLL_LOCK:
      // for debugging
      terminal_printstatus();
      break;
    case UNKNOWN: break;
    default:
      if (shift_state) {
        ascii_val = switch_case(ascii_val);
      }

      if (caps_state) {
        ascii_val = switch_case(ascii_val);
      }

      input_buffer[buffer_index++] = ascii_val;
      input_buffer[buffer_index]   = '\0';

      terminal_writechar(ascii_val);
      break;
  }
}
