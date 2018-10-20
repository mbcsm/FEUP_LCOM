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

int(kbd_test_scan)(bool assembly) {
	/* To be completed */
	/* When you use argument assembly for the first time, delete the UNUSED macro */
	extern uint32_t OBF_content;
	bool make = true;
	uint8_t size;
	uint8_t bytes[2];

	int ipc_status;
	message msg;
	uint8_t bit_no;
	int r;

	kbd_subscribe_int(&bit_no);

	uint64_t irq_set = BIT(bit_no);

	while (OBF_content != ESC) {
		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
			printf("driver_receive failed with: %d", r);
			continue;
		}
		printf("successful\n");
		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
				case HARDWARE: /* hardware interrupt notification */
					if (msg.m_notify.interrupts & irq_set) {
						if(!assembly)
							kbd_ih();
						else
							kbd_asm_ih();

						if((uint8_t)OBF_content == BYTE2){
							size = 2;
							bytes[0] = (uint8_t) OBF_content;
							bytes[1] = (uint8_t) (OBF_content >> 8);
			
							if(OBF_content & BIT(7))
								make = false;
							else
								make = true;
						}
						else{
						size = 1;
						bytes[0] = (uint8_t)OBF_content;
						if(OBF_content & BIT(7))
							make = false;
						else
							make = true;
						}

						kbd_print_scancode(make, size, bytes);
					}
					break;
				default:
					break; /* no other notifications expected: do nothing */
			}
		}
	}

	kbd_unsubscribe_int();
	

	return 0;
}


int(kbd_test_poll)() {
	uint32_t data;
	uint8_t bytes[2];

	bool make;
	uint8_t size = 0;
	do{
		data = 0;
		data = kbd_read();

		if((uint8_t)data == BYTE2){
			size = 2;
			bytes[0] = (uint8_t) data;
			bytes[1] = (uint8_t) (data >> 8);
			
			if(data & BIT(7))
				make = false;
			else
				make = true;
		}
		else{
			size = 1;
			bytes[0] = (uint8_t)data;
			if(data & BIT(7))
				make = false;
			else
				make = true;
		}

		kbd_print_scancode(make, size, bytes);
	}while((uint8_t)data != ESC);
	kbd_write();
	return 0;
}
int(kbd_test_timed_scan)(uint8_t UNUSED(n)) {
	/* To be completed */
	/* When you use argument n for the first time, delete the UNUSED macro */
	return 0;
}
