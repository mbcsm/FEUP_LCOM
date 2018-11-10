// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include <stdint.h>
#include <stdio.h>

// Any header files included below this line should have been created by you
#include "mouse.h"
#include "packet.h"
#include "i8042.h"
//#include "i8254.h"

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


//////////////////////////////////////
///////  MOUSE TEST PACKET  //////////
//////////////////////////////////////

int (mouse_test_packet)(uint32_t cnt) {
        
    extern uint32_t mouseData;
    uint32_t byteCounter = 0;
    struct packet pp;

	int ipc_status;
	message msg;
	uint8_t bit_no;
	int r;


    if (mouse_subscribe_int(&bit_no) != 0)
        return -1;


    if (mouse_disable_int() != 0)
        return -1;

    if (enable_data_report() != 0)
        return -1;

    if (mouse_enable_int() != 0)
        return -1;
	
    

	uint64_t irq_set = BIT(bit_no);

	while (byteCounter / 3 < cnt) {
		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
			printf("driver_receive failed with: %d", r);
			continue;
		}
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
    if (mouse_disable_int() != 0)
        return -1;

    if (disable_data_report() != 0)
        return -1;

    if (mouse_unsubscribe_int() != 0)
        return -1;
    
    return 0;
}

int miliseconds_to_micros(uint16_t n){
    return n * 10 * 10 * 10;
}


//////////////////////////////////////
///////  MOUSE TEST REMOTE  //////////
//////////////////////////////////////

int (mouse_test_remote)(uint16_t period, uint8_t cnt) {

    uint8_t count = cnt;
    struct packet pp;
    uint32_t packet[3];
    
    do {
            read_mouse_data(packet);  
        
            parseToPacket(1, packet[0], &pp);
            parseToPacket(2, packet[1], &pp);
            parseToPacket(3, packet[2], &pp);
        
            tickdelay(micros_to_ticks(miliseconds_to_micros(period)));
            mouse_print_packet(&pp);
            resetPacket(&pp);
            count--;
        

    }while (count > 0);

    if (set_stream_mode() != 0)
        return -1;
   
    if (disable_data_report() != 0)
        return -1;
    
    uint32_t cmd_byte = minix_get_dflt_kbc_cmd_byte(); 
    
    if (write_kbc_cmd_byte(cmd_byte) != 0)
        return -1;
    
    return 0;
}


//////////////////////////////////////
///////  MOUSE TEST ASYNC  ///////////
//////////////////////////////////////

int (mouse_test_async)(uint8_t idle_time) {
    
    extern uint32_t mouseData;
    extern int counter;

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

    
    if (mouse_disable_int() != 0)
        return -1;

    if (enable_data_report() != 0)
        return -1;

    if (mouse_enable_int() != 0)
        return -1;

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
                            counter = 0;
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
        
    if (mouse_disable_int() != 0)
        return -1;

    if (disable_data_report() != 0)
        return -1;

	if (mouse_unsubscribe_int() != OK)
		return -1;
	if (timer_unsubscribe_int() != OK)
		return -1;

	return 0;
}


//////////////////////////////////////
///////  MOUSE TEST GESTURE  /////////
//////////////////////////////////////

int (mouse_test_gesture)(uint8_t x, uint8_t t) {
    
    extern uint32_t mouseData;
    uint32_t byteCounter = 0;
    struct packet pp;

	int ipc_status;
	message msg;
	uint8_t bit_no;
	int r;


	if (mouse_subscribe_int(&bit_no) != 0)
        return -1;

    if (mouse_disable_int() != 0)
        return -1;

    if (enable_data_report() != 0)
        return -1;

    if (mouse_enable_int() != 0)
        return -1;

	uint64_t irq_set = BIT(bit_no);   

    bool EndState = false;

	while (!EndState) {
		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
			printf("driver_receive failed with: %d", r);
			continue;
		}
		
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
                            //tickdelay(micros_to_ticks(miliseconds_to_micros(500)));   //  DEBUGGING PURPOSES

                            EndState = event(&pp, x, t); // event(packet pp, uint8_t x, uint8_t t)  return true when the state machine reaches the final state
                            resetPacket(&pp);
                        }
					}
					break;
				default:
					break; /* no other notifications expected: do nothing */
			}
		}
	}
    if (mouse_disable_int() != 0)
        return -1;

    if (disable_data_report() != 0)
        return -1;

    if (mouse_unsubscribe_int() != 0)
        return -1;
    
    return 0;
}

