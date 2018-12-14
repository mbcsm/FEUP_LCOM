#include <lcom/lcf.h>

#include "game.h"
#include "keyboard.h"
#include "mouse.h"
#include "packet.h"
#include "video.h"
#include "cursor.h"
#include "cursor_pixmap.h"

Game* Start() {
    Game *game = malloc(sizeof(Game));

    vg_start(GAME_MODE);

    game->gameCursor = newCursor();
    game->gState = MENU;


/*
    int h_res = get_h_res();
    //int v_res = get_v_res();
    int bits_per_pixel = get_bits_per_pixel();
    void *video_mem = get_video_mem();*/

    int x = 200, y = 100;

    for (int j = y; j < y + 50; j++)
      for (int i = x; i < x + 100; i++){
               changePixel(i, j, 100);
    }


    if (kbd_subscribe_int(&bit_no_kbd) != 0)
      return NULL;

    if (mouse_subscribe_int(&bit_no_mouse) != 0)
        return NULL;


    if (mouse_disable_int() != 0)
        return NULL;

    if (enable_data_report() != 0)
        return NULL;

    if (mouse_enable_int() != 0)
        return NULL;

    return game;
}

void Handler(Game* game){
    extern uint32_t mouseData;
    struct packet pp;
    extern uint32_t kbdData;

    int ipc_status;
    message msg;
    int r;

    uint64_t irq_set_kbd = BIT(bit_no_kbd);
    uint64_t irq_set_mouse = BIT(bit_no_mouse);

    unsigned x = 0, y = 0;

    int byteCounter = 0;

    while (kbdData != ESC) {
		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
			printf("driver_receive failed with: %d", r);
			//continue; Cicle is outside this function
            return;
		}
		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
				case HARDWARE: /* hardware interrupt notification */
                    if (msg.m_notify.interrupts & irq_set_kbd) {
                        kbdData = 0;
                        kbd_ih();
                        if (kbdData == 0x39){
                            for (unsigned j = 0; j < v_res/*height*/; j++)
                                for (unsigned int i = 0; i < h_res/*width*/; i++){
                                char *ptr_VM = video_mem;
                                ptr_VM += (i + h_res * j) * (bits_per_pixel / 8);
                                *ptr_VM = 0;
                                }
                            y = y + 10;
                            x = x + 10;
                            for (unsigned int j = y; j < y + 200/*height*/; j++)
                                for (unsigned int i = x; i < x + 200/*width*/; i++){
                                    char *ptr_VM = video_mem;
                                    ptr_VM += (i + h_res * j) * (bits_per_pixel / 8);
                                    *ptr_VM = 10;
                                }
                        }
                        if (kbdData == 0x0e){
                            y = y - 10;
                            x = x - 10;
                            for (unsigned int j = 0; j < v_res/*height*/; j++)
                                for (unsigned int i = 0; i < h_res/*width*/; i++){
                                    char *ptr_VM = video_mem;
                                    ptr_VM += (i + h_res * j) * (bits_per_pixel / 8);
                                    *ptr_VM = 0;
                                }
              
                            for (unsigned int j = y; j < y + 200/*height*/; j++)
                                for (unsigned int i = x; i < x + 200/*width*/; i++){
                                    char *ptr_VM = video_mem;
                                    ptr_VM += (i + h_res * j) * (bits_per_pixel / 8);
                                    *ptr_VM = 10;
                                }
                        }
                        if (kbdData == ESC)
                            game->gState = EXIT;

                    }
		            if (msg.m_notify.interrupts & irq_set_mouse) {
                        mouseData = 0;   
                        mouse_ih();
                        byteCounter++;
                        parseToPacket(byteCounter % 3, mouseData, &pp);
                        

                        if (byteCounter % 3 == 0){
                            /*clearCursor(game->gameCursor);
                            updatePosition(&pp, game->gameCursor);
                            //memcpy(video_mem, clear, sizeof(video_mem));
                            drawCursor(game->gameCursor);
                            resetPacket(&pp);*/

                            //process_mouse_event(game, &pp, game->gameCursor);
                            draw_xpm(0, 0);
                        }
			        }
                    break;
                    
		        default:
					break; /* no other notifications expected: do nothing */
			}

            //DRAWMODE



		}
	}
}

int End(){
    // delete cursor 
    // Clean video mem
    // 

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

GameState getGameState(Game* game){
    return game->gState;
}


void process_mouse_event(Game *game, struct packet* pp, cursor* c){

    clearCursor(c);
    updatePosition(pp, c);
    printf("as");
    drawCursor(c);

    printf("asdf");
    resetPacket(pp);


    GameState gameSt = getGameState(game);

    int x, y;
    
    if (pp->lb)
        switch(gameSt) {
            case MENU:
                getPosition(c, &x, &y);
                if (x>0 && x < 200 && y > 0 && y < 200)
                    for (int j = y; j < y + 200; j++)
                        for (int i = x; i < x + 200; i++){
                            changePixel(i, j, 100);
                        }
                game->gState = MODE_MENU;
                
                break;
        
            default:
					break;
        }
}

void draw_xpm(int x, int y){
    int h_res = get_h_res();
  //int bits_per_pixel = get_bits_per_pixel();
  void *video_mem = get_video_mem();

  xpm_image_t img;
  uint16_t *sprite = (uint16_t*)xpm_load(cursor_xpm, XPM_5_6_5, &img);

  const uint16_t  transp = xpm_transparency_color(XPM_5_6_5);

  for (int i = x; i < x + img.height; i++){
    for (int j = y; j < y + img.width; j++) {
      uint16_t *ptr_VM = (uint16_t*)video_mem;
      ptr_VM += (i * h_res + j);
      if(*sprite != 0xff00ff)
        *ptr_VM = *sprite;
      sprite++;
    }
}
}

