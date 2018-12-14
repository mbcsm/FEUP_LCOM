// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include <lcom/lab5.h>

#include "keyboard.h"
#include "video.h"
#include "pixmap/play_button.h"

#include <i8042.h>
#include <stdint.h>
#include <stdio.h>

// Any header files included below this line should have been created by you

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






void display_menu() {

  extern uint32_t kbdData;

  int ipc_status;
  message msg;
  uint8_t bit_no;
  int r;

  kbd_subscribe_int(&bit_no);
  uint64_t irq_set_kbd = BIT(bit_no);

  vg_start(0x11A);

  int h_res = get_h_res();
  //int bits_per_pixel = get_bits_per_pixel();
  void *video_mem = get_video_mem();


  int xi = 0, yi = 0;


  xpm_image_t img;
  uint16_t *sprite = (uint16_t*)xpm_load(play_button, XPM_5_6_5, &img);

  const uint16_t  transp = xpm_transparency_color(XPM_5_6_5);

  for (int i = xi; i < xi + img.height; i++){
    for (int j = yi; j < yi + img.width; j++) {
      uint16_t *ptr_VM = (uint16_t*)video_mem;
      ptr_VM += (i * h_res + j);
      if(*sprite != transp)
        *ptr_VM = *sprite;
      sprite++;
    }
  }

  while (kbdData != ESC) {
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE: 
          if (msg.m_notify.interrupts & irq_set_kbd) {
            kbdData = 0;
            kbd_ih();
          }

          break;
        default:
          break;
      }
    }
  }
  kbd_unsubscribe_int();

  //printf("%d", xpm[0]);

  if (vg_exit() != 0)
    return ;

  return ;
}





int (proj_main_loop)(int argc, char *argv[]) {
  /* To be completed */
  printf("%s(%d, %p): under construction\n", __func__, argc, argv);

  display_menu();
  return 1;
}
