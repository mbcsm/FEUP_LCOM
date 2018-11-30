// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

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

int (proj_main_loop)(int argc, char *argv[]) {
  /* To be completed */
  printf("%s(%d, %p): under construction\n", __func__, argc, argv);

  return 1;
}



/*
void displayMenu() {
  const char *xpm[50] = play_button;
  int xi = 24, yi = 27;
  int h, w;
  char *map;

  extern uint32_t kbdData;

  int ipc_status;
  message msg;
  uint8_t bit_no;
  int r;

  kbd_subscribe_int(&bit_no);
  uint64_t irq_set_kbd = BIT(bit_no);

  vg_start(0x105);

  int h_res = get_h_res();
  //int v_res = get_v_res();
  int bits_per_pixel = get_bits_per_pixel();
  void *video_mem = get_video_mem();

  map = read_xpm(xpm, &w, &h);

  for (int i = xi; i < xi + h; i++)
    for (int j = yi; j < yi + w; j++) {
      char *ptr_VM = video_mem;
      ptr_VM += (i * h_res + j) * (bits_per_pixel / 8);
      *ptr_VM = *map;
      map += 1;
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

  printf("%d", xpm[0]);

  if (vg_exit() != 0)
    return ;

  return ;
}
*/
