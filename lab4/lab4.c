// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include <stdint.h>
#include <stdio.h>

// Any header files included below this line should have been created by you
#include "mouse.h"
#include "packet.h"
#include "i8042.h"
#include "i8254.h"

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need/ it]
  lcf_trace_calls("/home/lcom/labs/lab4/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab4/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}


int (mouse_test_packet)(uint32_t cnt) {
    /* To be completed */
    printf("%s(%u): under construction\n", __func__, cnt);
    
    extern uint32_t mouseData;
    uint32_t byteCounter = 0;
    struct packet pp;

	int ipc_status;
	message msg;
	uint8_t bit_no;
	int r;

    mouse_enable_data_reporting();
    enable_data_report();

	mouse_subscribe_int(&bit_no);

	uint64_t irq_set = BIT(bit_no);

	while (byteCounter / 3 < cnt) {
		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
			printf("driver_receive failed with: %d", r);
			continue;
		}
		//printf("successful\n");
		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
				case HARDWARE: /* hardware interrupt notification */
					if (msg.m_notify.interrupts & irq_set) {
						mouseData = 0;   

                        mouse_ih();                        
                        byteCounter++;
						
                        parseToPacket(byteCounter % 3, mouseData, &pp);

                        if (byteCounter % 3 == 0){
						    mouse_print_packet(&pp);
                            resetPacket(&pp);
                        }
					}
					break;
				default:
					break; /* no other notifications expected: do nothing */
			}
		}
	}
    //disable_data_report();
	mouse_unsubscribe_int();
    printf("unsubscribed\n");

    return 0;
}

int milis_to_micros(uint16_t n){
    return n * 10 * 10 * 10;
}

int (mouse_test_remote)(uint16_t period, uint8_t cnt) {
    /* To be completed */
    printf("%s(%u, %u): under construction\n", __func__, period, cnt);

    uint8_t count = cnt;
    struct packet pp;
    uint32_t data;
    uint32_t byteOne, byteTwo, byteThree;

    do {
        read_data();
        data = read_kbc();
        
        byteOne = (uint8_t)(data & 0x1100);
        byteTwo = (uint8_t)(data & 0x110000);
        byteThree = (uint8_t)(data & 0x11000000);

        parseToPacket(1, byteOne, &pp);
        parseToPacket(2, byteTwo, &pp);
        parseToPacket(3, byteThree, &pp);
        
        tickdelay(micros_to_ticks(milis_to_micros(period)));
        mouse_print_packet(&pp);
        resetPacket(&pp);
        
        count--;
    }while (count > 0);


    set_stream_mode();
    disable_data_report();

    
    write_kbc_cmd_byte( minix_get_dflt_kbc_cmd_byte() );    

    return 0;
}

extern int counter;
int (mouse_test_async)(uint8_t idle_time) {
    /* To be completed */
    printf("%s(%u): under construction\n", __func__, idle_time);

    extern uint32_t mouseData;

    int byteCounter = 0;
    struct packet pp;

	int ipc_status;
	message msg;
	uint8_t bit_no;
	int r ;
	if(timer_subscribe_int(&bit_no) != OK)
		return -1;
	
	uint64_t irq_set_timer = BIT(bit_no);

	if (mouse_subscribe_int(&bit_no) != OK)
		return -1;

	uint64_t irq_set_mouse = BIT(bit_no);

	while ((unsigned int)counter  < sys_hz() * idle_time) {
		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
			printf("driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
				case HARDWARE: /* hardware interrupt notification */
					if (msg.m_notify.interrupts & irq_set_mouse) {
						mouseData = 0;   

                        mouse_ih();                        
                        byteCounter++;
						
                        parseToPacket(byteCounter % 3, mouseData, &pp);

                        if (byteCounter % 3 == 0){
						    mouse_print_packet(&pp);
                            resetPacket(&pp);
                        }
					}
					else if (msg.m_notify.interrupts & irq_set_timer) {
						timer_int_handler();
					}
					break;
				default:
					break; /* no other notifications expected: do nothing */
			}
		}
	}

	if (mouse_unsubscribe_int() != OK)
		return -1;
	if (timer_unsubscribe_int() != OK)
		return -1;

	return 0;

    return 1;
}

int (mouse_test_gesture)(uint8_t x, uint8_t t) {
    /* To be completed */
    x = t;
    printf("%s: under construction\n", __func__);
    
    extern uint32_t mouseData;
    uint32_t byteCounter = 0;
    struct packet pp;

	int ipc_status;
	message msg;
	uint8_t bit_no;
	int r, stop = 0;

    mouse_enable_data_reporting();
    //enable_data_report();

	mouse_subscribe_int(&bit_no);

	uint64_t irq_set = BIT(bit_no);

    int state = 0, length_of_line = 0;

	while (stop == 0) {
		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
			printf("driver_receive failed with: %d", r);
			continue;
		}
		//printf("successful\n");
		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
				case HARDWARE: /* hardware interrupt notification */
					if (msg.m_notify.interrupts & irq_set) {
						mouseData = 0;   

                        mouse_ih();                        
                        byteCounter++;
						
                        parseToPacket(byteCounter % 3, mouseData, &pp);

                        if (byteCounter % 3 == 0){
                            switch(state){
                                case 0:
                                    if(pp.rb == 1 && pp.lb == 0){
                                        printf("rb is down -> start drawing the inverted V\n");
                                        state = 1;
                                    }
                                    break;
                                case 1:
                                    if(pp.rb == 1 && pp.delta_y > 0 && pp.delta_x > 0){
                                        length_of_line += pp.delta_x * pp.delta_x + pp.delta_y * pp.delta_y;
                                        printf("current line lenght: %d\n", length_of_line);
                                    }else if(pp.rb == 1 && (pp.delta_y <= 0 || pp.delta_x <= 0)){
                                        printf("FAILED: Wrong Direction\n");
                                        stop = 1;
                                    }else if(pp.rb == 0 && length_of_line < x){
                                        printf("FAILED: line not long enough\n");
                                        stop = 1;
                                    }else if(pp.rb == 0 && length_of_line >= x){
                                        printf("rb-release: line long enough. Press lb to coninue\n");
                                        length_of_line = 0;
                                        state = 2;
                                    }
                                    break;
                                case 2:
                                    if(pp.rb == 0 && pp.lb == 1){
                                        printf("lb is down -> start drawing the inverted V\n");
                                        state = 3;
                                    }else if(pp.rb == 1){
                                        printf("FAILED: rb pressed. should have been the lb\n");
                                        stop = 1;
                                    }
                                    break;
                                case 3:
                                    if(pp.lb == 1 && pp.delta_y < 0 && pp.delta_x > 0){
                                        length_of_line += pp.delta_x * pp.delta_x + pp.delta_y * pp.delta_y;
                                        printf("current line lenght: %d\n", length_of_line);
                                    }else if(pp.lb == 1 && (pp.delta_y >= 0 || pp.delta_x <= 0)){
                                        printf("FAILED: Wrong Direction\n");
                                        stop = 1;
                                    }else if(pp.lb == 0 && length_of_line < x){
                                        printf("FAILED: line not long enough\n");
                                        stop = 1;
                                    }else if(pp.lb == 0 && length_of_line >= x){
                                        printf("lb-release: line long enough.\nSUCCESS INVERTED V COMPLETED!\n");
                                        stop = 1;
                                    }
                                    break;

                            }
						    //mouse_print_packet(&pp);
                            resetPacket(&pp);
                        }
					}
					break;
				default:
					break; /* no other notifications expected: do nothing */
			}
		}
	}
    //disable_data_report();
	mouse_unsubscribe_int();
    printf("unsubscribed\n");

    return 0;
}

