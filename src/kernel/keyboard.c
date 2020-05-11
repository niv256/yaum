#include "keyboard.h"
#include "../include/stdint.h"
#include "tools.h"
#include "screen.h"
#include "isr.h"
#include "shell.h"

#define MAX_KEY_VAL 0x58

static char key_map[MAX_KEY_VAL];
static char input_buffer[256];
static int buffer_index;

enum special_characters {BACKSPACE = 1, TAB, ENTER, LEFT_CTRL, LEFT_SHIFT, RIGHT_SHIFT, LEFT_ALT,
			SPACE, CAPS_LOCK, F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
			NUM_LOCK, SCROLL_LOCK};

void keyboard_init(void) {
	// init buffer
	buffer_index = 0;
	input_buffer[0] = '\0';

	// init ascii map
	key_map[0x02] = '1';
	key_map[0x03] = '2';
	key_map[0x04] = '3';
	key_map[0x05] = '4';
	key_map[0x06] = '5';
	key_map[0x07] = '6';
	key_map[0x08] = '7';
	key_map[0x09] = '8';
	key_map[0x0a] = '9';
	key_map[0x0b] = '0';
	key_map[0x0c] = '-';
	key_map[0x0d] = '=';
	key_map[0x0e] = BACKSPACE;
	key_map[0x0f] = TAB;
	key_map[0x10] = 'q';
	key_map[0x11] = 'w';
	key_map[0x12] = 'e';
	key_map[0x13] = 'r';
	key_map[0x14] = 't';
	key_map[0x15] = 'y';
	key_map[0x16] = 'u';
	key_map[0x17] = 'i';
	key_map[0x18] = 'o';
	key_map[0x19] = 'p';
	key_map[0x1a] = '[';
	key_map[0x1b] = ']';
	key_map[0x1c] = ENTER;
	key_map[0x1d] = LEFT_CTRL;
	key_map[0x1e] = 'a';
	key_map[0x1f] = 's';
	key_map[0x20] = 'd';
	key_map[0x21] = 'f';
	key_map[0x22] = 'g';
	key_map[0x23] = 'h';
	key_map[0x24] = 'j';
	key_map[0x25] = 'k';
	key_map[0x26] = 'l';
	key_map[0x27] = ';';
	key_map[0x28] = '\'';
	key_map[0x29] = '`';
	key_map[0x2a] = LEFT_SHIFT;
	key_map[0x2b] = '\\';
	key_map[0x2c] = 'z';
	key_map[0x2d] = 'x';
	key_map[0x2e] = 'c';
	key_map[0x2f] = 'v';
	key_map[0x30] = 'b';
	key_map[0x31] = 'n';
	key_map[0x32] = 'm';
	key_map[0x33] = ',';
	key_map[0x34] = '.';
	key_map[0x35] = '/';
	key_map[0x36] = RIGHT_SHIFT;
	key_map[0x37] = '*';
	key_map[0x38] = LEFT_ALT;
	key_map[0x39] = ' ';
	key_map[0x3a] = CAPS_LOCK;
	key_map[0x3b] = F1;
	key_map[0x3c] = F2;
	key_map[0x3d] = F3;
	key_map[0x3e] = F4;
	key_map[0x3f] = F5;
	key_map[0x40] = F6;
	key_map[0x41] = F7;
	key_map[0x42] = F8;
	key_map[0x43] = F9;
	key_map[0x44] = F10;
	key_map[0x45] = NUM_LOCK;
	key_map[0x46] = SCROLL_LOCK;
	key_map[0x47] = '7';
	key_map[0x48] = '8';
	key_map[0x49] = '9';
	key_map[0x4a] = '-';
	key_map[0x4b] = '4';
	key_map[0x4c] = '5';
	key_map[0x4d] = '6';
	key_map[0x4e] = '+';
	key_map[0x4f] = '1';
	key_map[0x50] = '2';
	key_map[0x51] = '3';
	key_map[0x52] = '0';
	key_map[0x53] = '.';
	key_map[0x57] = F11;
	key_map[0x58] = F12;

	// setup the keyboard interuupt callback
	setup_isr_callback(IRQ1, &get_key_press);
}

void reset_buffer(void) {
	buffer_index = 0;
	input_buffer[0] = '\0';
}

void get_key_press(void) {
	uint8_t key_val, ascii_val;
	key_val = inb(0x60);

	if (key_val > MAX_KEY_VAL) {
		return;
	}

	ascii_val = key_map[key_val];
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
		case LEFT_SHIFT:
		case RIGHT_SHIFT:
		case LEFT_ALT:
		case CAPS_LOCK:
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
		case NUM_LOCK:
			break;
		case SCROLL_LOCK:
			// for debugging
			terminal_printstatus();
			break;
		default:
			input_buffer[buffer_index++] = ascii_val;
			input_buffer[buffer_index] = '\0';
			terminal_putchar(ascii_val);
			break;

	}
}
