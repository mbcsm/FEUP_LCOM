// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

// Any header files included below this line should have been created by you

#include <lcom/timer.h>
#include "keyboard.h"
#include "mouse.h"
#include "packet.h"
#include "video.h"
#include "cursor.h"

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/proj/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/proj/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

char *clear[1440][900];

int (proj_main_loop)(int argc, char *argv[]) {
  /* To be completed */
  printf("%s(%d, %p): under construction\n", __func__, argc, argv);



  extern uint32_t mouseData;
  struct packet pp;
  extern uint32_t kbdData;

  int ipc_status;
  message msg;
  uint8_t bit_no_kbd;
  uint8_t bit_no_mouse;
  int r;

  vg_start(0x115);
  
  int h_res = get_h_res();
  int v_res = get_v_res();
  int bits_per_pixel = get_bits_per_pixel();
  void *video_mem = get_video_mem();

    if (kbd_subscribe_int(&bit_no_kbd) != 0)
      return -1;

    if (mouse_subscribe_int(&bit_no_mouse) != 0)
        return -1;


    if (mouse_disable_int() != 0)
        return -1;

    if (enable_data_report() != 0)
        return -1;

    if (mouse_enable_int() != 0)
        return -1;

    int x = 0, y = 0;

    for (int j = y; j < y + 200/*height*/; j++)
      for (int i = x; i < x + 200/*width*/; i++){
        char *ptr_VM = video_mem;
        ptr_VM += (i + h_res * j) * (bits_per_pixel / 8);
        *ptr_VM = 10;
      }
  
  //char *scr = video_mem;

	uint64_t irq_set_kbd = BIT(bit_no_kbd);
  uint64_t irq_set_mouse = BIT(bit_no_mouse);

  int byteCounter = 0;
  cursor *c = newCursor();


	while (kbdData != ESC) {
		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
			printf("driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
				case HARDWARE: /* hardware interrupt notification */
          if (msg.m_notify.interrupts & irq_set_kbd) {
            kbdData = 0;
            kbd_ih();
            if (kbdData == 0x39)
            {
              for (int j = 0; j < v_res/*height*/; j++)
                for (int i = 0; i < h_res/*width*/; i++){
                  char *ptr_VM = video_mem;
                  ptr_VM += (i + h_res * j) * (bits_per_pixel / 8);
                  *ptr_VM = 0;
                }
              y = y + 10;
              x = x + 10;
              for (int j = y; j < y + 200/*height*/; j++)
                for (int i = x; i < x + 200/*width*/; i++){
                  char *ptr_VM = video_mem;
                  ptr_VM += (i + h_res * j) * (bits_per_pixel / 8);
                  *ptr_VM = 10;
                }
            }
            if (kbdData == 0x0e)
            {
              y = y - 10;
              x = x - 10;
              for (int j = 0; j < v_res/*height*/; j++)
                for (int i = 0; i < h_res/*width*/; i++){
                  char *ptr_VM = video_mem;
                  ptr_VM += (i + h_res * j) * (bits_per_pixel / 8);
                  *ptr_VM = 0;
                }
              
              for (int j = y; j < y + 200/*height*/; j++)
                for (int i = x; i < x + 200/*width*/; i++){
                  char *ptr_VM = video_mem;
                  ptr_VM += (i + h_res * j) * (bits_per_pixel / 8);
                  *ptr_VM = 10;
                }
            }

          }
					if (msg.m_notify.interrupts & irq_set_mouse) {
            mouseData = 0;   
            mouse_ih();
            byteCounter++;
						//printf("%d ", byteCounter);
            parseToPacket(byteCounter % 3, mouseData, &pp);
            
            if (byteCounter % 3 == 0){
              updatePosition(&pp, c);
              drawCursor(c);
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

    if (kbd_unsubscribe_int() != 0)
      return -1;

  vg_exit(); 

  return 0;
}
