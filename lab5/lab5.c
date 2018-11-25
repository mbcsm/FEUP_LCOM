// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include <lcom/lab5.h>

#include "keyboard.h"
#include "video.h"
#include <lcom/pixmap.h>

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

  /*int ipc_status;
  message msg;
  uint8_t bit_no;
  int r;

  if (timer_subscribe_int(&bit_no) != OK)
    return -1;

  uint64_t irq_set_timer = BIT(bit_no);*/

  vg_start(mode);

  sleep(delay);
  //Draw a Blue Square
/*
  while ((unsigned int) counter < sys_hz() * delay) {
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed with: %d", r);
      continue;
    }

    if (is_ipc_notify(ipc_status)) { // received notification 
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE: // hardware interrupt notification 
          if (msg.m_notify.interrupts & irq_set_timer) {
            timer_int_handler();
          }
          break;
        default:
          break; /// no other notifications expected: do nothing 
      }
    }
  }*/

  if (vg_exit() == 0) {
    return 0;
  }
  else
    return 1;
/*
  if (timer_unsubscribe_int() != OK)
    return -1;*/
  
  return 0;
}

int (video_test_rectangle)(uint16_t mode, uint16_t x, uint16_t y,
                       uint16_t width, uint16_t height, uint32_t color) {

  extern uint32_t kbdData;

  int ipc_status;
	message msg;
	uint8_t bit_no;
	int r;

  kbd_subscribe_int(&bit_no);
	uint64_t irq_set_kbd = BIT(bit_no);

  vg_start(mode);
  
  //Draw a Blue Square
  int h_res = get_h_res();
  //int v_res = get_v_res();
  int bits_per_pixel = get_bits_per_pixel();
  void *video_mem = get_video_mem();
  


  uint8_t color_component_blue = (color >> get_blue_screen_mask_position()) & get_blue_screen_mask();
  uint8_t color_component_green = (color >> get_green_screen_mask_position()) & get_green_screen_mask();
  uint8_t color_component_red = (color >> get_red_screen_mask_position()) & get_red_screen_mask();

  uint8_t color_treated;
    
  if(mode == 0x105){
    color_treated = (color) % (1 << get_bits_per_pixel());
  }else{
    uint8_t R = color_component_red % (1 << get_red_screen_mask());
    uint8_t G = color_component_green % (1 << get_green_screen_mask());
    uint8_t B = color_component_blue % (1 << get_blue_screen_mask());	
    color_treated = R | G | B;
  }
  for (int j = y; j < y + height; j++)
    for (int i = x; i < x + width; i++){
      char *ptr_VM = video_mem;
      ptr_VM += (i + h_res * j) * (bits_per_pixel / 8);
      *ptr_VM = color_treated;
    }
  


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

					break;
				default:
					break; /* no other notifications expected: do nothing */
			}
		}
	}
	kbd_unsubscribe_int();

  if (vg_exit() == 0) {
    return 0;
  }
  else
    return 1;
}

int(video_test_pattern)(uint16_t mode, uint8_t no_rectangles,  uint32_t first, uint8_t step) {

  extern uint32_t kbdData;

  int ipc_status;
	message msg;
	uint8_t bit_no;
	int r;

  kbd_subscribe_int(&bit_no);
	uint64_t irq_set_kbd = BIT(bit_no);

  vg_start(mode);
  
  //Draw a Blue Square
  int h_res = get_h_res();
  int v_res = get_v_res();
  int bits_per_pixel = get_bits_per_pixel();
  void *video_mem = get_video_mem();


  int width = h_res / no_rectangles;
  int height = v_res / no_rectangles;
  int size = 0;

  if(width < height){
    size = width;
  }else{
    size = height;
  }

  int current_x = 0;
  int current_y = 0;
  int current_rec_x = 0;
  int current_rec_y = 0;
  int total = 0;


  uint8_t color_component_blue = (first >> get_blue_screen_mask_position()) & get_blue_screen_mask();
  uint8_t color_component_green = (first >> get_green_screen_mask_position()) & get_green_screen_mask();
  uint8_t color_component_red = (first >> get_red_screen_mask_position()) & get_red_screen_mask();

  for(int rec_index = 0 ; rec_index < no_rectangles * no_rectangles; rec_index ++ ){
     uint8_t color;
    
    if(mode == 0x105){
      color = (first + (current_rec_x * no_rectangles + current_rec_y) * step) % (1 << get_bits_per_pixel());
    }else{
      uint8_t R = (color_component_red + current_rec_x * step) % (1 << get_red_screen_mask());
      uint8_t G = (color_component_green + current_rec_y * step) % (1 << get_green_screen_mask());
      uint8_t B = (color_component_blue + (current_rec_x + current_rec_y) * step) % (1 << get_blue_screen_mask());	
      color = R | G | B;
    }


    for(int i = current_x; i < size + current_x; i++){
      for(int j = current_y; j < size + current_y; j++){
        char *ptr_VM = video_mem;
        ptr_VM += (i + h_res * j) * (bits_per_pixel / 8);
        *ptr_VM = color;
      }
    }

    current_rec_x++;
    total++;
    if(total % no_rectangles == 0){
      current_rec_x = 0;
      current_rec_y++;
      current_x = 0;
      current_y += size;
    }else{
      current_x += size;
    }
  }


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

					break;
				default:
					break; /* no other notifications expected: do nothing */
			}
		}
	}
	kbd_unsubscribe_int();

  if (vg_exit() == 0) {
    return 0;
  }
  else
    return 1;
}

int (video_test_xpm)(const char *xpm[], uint16_t xi, uint16_t yi){
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
  
  int bits_per_pixel = get_bits_per_pixel();
  void *video_mem = get_video_mem();

  map = read_xpm(xpm, &w, &h);

  for (int j= yi; j < yi + h; j++)
    for (int i = xi; i < xi + w; i++){
      char *ptr_VM = video_mem;
      ptr_VM += (i + h_res * j) * (bits_per_pixel / 8); /* Fazer funcao de acesso a posicao no array*/
      *ptr_VM = *map;
      map += 1;
    }

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

					break;
				default:
					break; /* no other notifications expected: do nothing */
			}
		}
	}
	kbd_unsubscribe_int();

  printf("%d", xpm[0]);

  if (vg_exit() != 0) 
    return 1;

  return 0;
}


int (video_test_move)(const char *xpm[], uint16_t xi, uint16_t yi, uint16_t xf, uint16_t yf, int16_t speed, uint8_t fr_rate){
  extern int counter;

  int ipc_status;
	message msg;
	uint8_t bit_no;
	int r;

  int h, w;
  char *map;

  vg_start(0x105); // MACRO!!

  int h_res = get_h_res();
  
  int bits_per_pixel = get_bits_per_pixel();
  void *video_mem = get_video_mem();



  timer_subscribe_int(&bit_no);
  uint64_t irq_set_timer = BIT(bit_no);

uint16_t xn = xi, yn = yi;

  while (xn < xf || yn < yf) {
		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
			printf("driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
				case HARDWARE: /* hardware interrupt notification */
					if (msg.m_notify.interrupts & irq_set_timer) {

            if (counter % (sys_hz() / fr_rate) == 0){
            map = read_xpm(xpm, &w, &h);

            clearW_H(xn - speed, yn - speed, w, h);
            for (int j= yn; j < yn + h; j++)
              for (int i = xn; i < xn + w; i++){
                char *ptr_VM = video_mem;
                ptr_VM += (i + h_res * j) * (bits_per_pixel / 8); /* Fazer funcao de acesso a posicao no array*/
                *ptr_VM = *map;
                map += 1;
              }
            if (xn == xf && speed > 0)
              yn += speed; 
            else if (yn == yf && speed > 0)
              xn += speed; 
            }


						timer_int_handler();
					}
          
					break;
				default:
					break; /* no other notifications expected: do nothing */
			}
		}
  }

timer_unsubscribe_int();

kbd_subscribe_int(&bit_no);
uint64_t irq_set_kbd = BIT(bit_no);
extern uint32_t kbdData;

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

					break;
				default:
					break; /* no other notifications expected: do nothing */
			}
		}
	}
	kbd_unsubscribe_int();


if (vg_exit() != 0) 
    return 1;

return 0;

}

