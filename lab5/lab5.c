// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include <lcom/lab5.h>

#include "keyboard.h"
#include "video.h"

#include <i8042.h>
#include <stdint.h>
#include <stdio.h>

// Any header files included below this line should have been created by you


int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab5/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab5/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(video_test_init)(uint16_t mode, uint8_t delay) {

  extern int counter;

  int ipc_status;
  message msg;
  uint8_t bit_no;
  int r;

  if (timer_subscribe_int(&bit_no) != OK)
    return -1;

  uint64_t irq_set_timer = BIT(bit_no);

  vg_start(mode);


  //Draw a Blue Square
  int h_res = get_h_res();
  int bits_per_pixel = get_bits_per_pixel();
  void *video_mem = get_video_mem();

  printf("%d", h_res);

  for(int i = 0; i < 100; i++){
    for(int j = 0; j < 100; j++){
      char *ptr_VM = video_mem;
      ptr_VM += (i + h_res * j) * (bits_per_pixel / 8);
      *ptr_VM = 1;
    }
  }

   


  while ((unsigned int) counter < sys_hz() * delay) {
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed with: %d", r);
      continue;
    }

    if (is_ipc_notify(ipc_status)) { /* received notification */
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE: /* hardware interrupt notification */
          if (msg.m_notify.interrupts & irq_set_timer) {
            timer_int_handler();
          }
          break;
        default:
          break; /* no other notifications expected: do nothing */
      }
    }
  }

  if (vg_exit() == 0) {
    return 0;
  }
  else
    return 1;
  
  return 0;
}

int (video_test_rectangle)(uint16_t mode, uint16_t x, uint16_t y,
                       uint16_t width, uint16_t height, uint32_t color) {
  /* To be completed */
  printf("%s(0x%03X, %u, %u, %u, %u, 0x%08x): under construction\n",
         __func__, mode, x, y, width, height, color);

  extern uint32_t kbdData;

  int ipc_status;
	message msg;
	uint8_t bit_no;
	int r;

  kbd_subscribe_int(&bit_no);

	uint64_t irq_set_kbd = BIT(bit_no);

  //initVG

  vbe_mode_info_t vbe_info;
  vbe_get_mode_info(mode, &vbe_info);

  vg_draw_hline(x, y, width, color);

  
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
					}
          /*if (msg.m_notify.interrupts & irq_set) { // INTERRUPT NOTIFICATION FOR ANOTHER 
						
					}*/
					break;
				default:
					break; /* no other notifications expected: do nothing */
			}
		}
	}

  return 1;
}

int(video_test_pattern)(uint16_t mode, uint8_t no_rectangles, uint32_t first, uint8_t step) {
  /* To be completed */
  printf("%s(0x%03x, %u, 0x%08x, %d): under construction\n", __func__, mode, no_rectangles, first, step);

  return 1;
}
