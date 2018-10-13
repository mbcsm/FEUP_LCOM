
#include <lcom/lcf.h>

#include <lcom/lab2.h>
#include <lcom/timer.h>

#include <stdbool.h>
#include <stdint.h>
#include <i8254.h>

extern int counterSeconds, counter;
int main(int argc, char *argv[]) {
	// sets the language of LCF messages (can be either EN-US or PT-PT)
	lcf_set_language("EN-US");
	
	// enables to log function invocations that are being "wrapped" by LCF
	// [comment this out if you don't want/need/ it]
	lcf_trace_calls("/home/lcom/labs/lab2/trace.txt");
	
	// enables to save the output of printf function calls on a file
	// [comment this out if you don't want/need it]
	lcf_log_output("/home/lcom/labs/lab2/output.txt");
	
	// handles control over to LCF
	// [LCF handles command line arguments and invokes the right function]
	if (lcf_start(argc, argv))
	return 1;
	
	// LCF clean up tasks
	// [must be the last statement before return]
	lcf_cleanup();
	
	return 0;
}

int(timer_test_read_config)(uint8_t timer, enum timer_status_field field) {
	/* To be completed by the students */
	uint8_t st;
	
	//printf("status: %s\n", field);
	if (timer_get_conf(timer, &st) != OK)
		return 1;
	if (timer_display_conf(timer, st, field) != OK)
		return 1;
	
	return 0;
}

int(timer_test_time_base)(uint8_t timer, uint32_t freq) {
	/* To be completed by the students
	printf("%s is not yet implemented!\n", __func__);*/
	
	timer_set_frequency(timer, freq);
	
	return 0;
}

int(timer_test_int)(uint8_t time) {
	int ipc_status;
	message msg;
	uint8_t bit_no = 0;
	int r;

	if(timer_subscribe_int(&bit_no) != OK)
		return -1;
	
	uint64_t irq_set = BIT(bit_no);
	

	while ((unsigned int)counter  < sys_hz()*time) {
		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
			printf("driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
				case HARDWARE: /* hardware interrupt notification */
					if (msg.m_notify.interrupts & irq_set) {
						timer_int_handler();
						if(counter % sys_hz() == 0){
							timer_print_elapsed_time();
						}
					}
					break;
				default:
					break; /* no other notifications expected: do nothing */
			}
		}
	}
	
	if(timer_unsubscribe_int() != OK)
		return -1;

	return 0;
}

int(util_get_LSB)(uint16_t val, uint8_t *lsb) {
	/* To be completed by the students
	printf("%s is not yet implemented!\n", __func__);*/
	
	*lsb = (uint8_t) val;
	
	return 0;
}

int(util_get_MSB)(uint16_t val, uint8_t *msb) {
	/* To be completed by the students
	printf("%s is not yet implemented!\n", __func__);*/
	
	val = val >> 8;
	*msb = val;
	
	return 0;
}

