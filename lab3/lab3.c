// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>
#include <lcom/lab3.h>
#include <lcom/timer.h>
#include "keyboard.h"

#include <stdbool.h>
#include <stdint.h>
#include <i8254.h>
#include <i8042.h>
// Any header files below this line should have been created by you

int main(int argc, char *argv[]) {
	// sets the language of LCF messages (can be either EN-US or PT-PT)
	lcf_set_language("EN-US");

	// enables to log function invocations that are being "wrapped" by LCF
	// [comment this out if you don't want/need/ it]
	lcf_trace_calls("/home/lcom/labs/lab3/trace.txt");

	// enables to save the output of printf function calls on a file
	// [comment this out if you don't want/need it]
	lcf_log_output("/home/lcom/labs/lab3/output.txt");

	// handles control over to LCF
	// [LCF handles command line arguments and invokes the right function]
	if (lcf_start(argc, argv))
		return 1;

	// LCF clean up tasks
	// [must be the last statement before return]
	lcf_cleanup();

	return 0;
}

int(kbd_test_scan)(bool UNUSED(assembly)) {
	/* To be completed */
	/* When you use argument assembly for the first time, delete the UNUSED macro */
	return 0;
}
int(kbd_test_poll)() {
	while(1){
		kbd_write();
		kbd_read();
	}
	return 0;
}
int(kbd_test_timed_scan)(uint8_t UNUSED(n)) {
	/* To be completed */
	/* When you use argument n for the first time, delete the UNUSED macro */
	return 0;
}
