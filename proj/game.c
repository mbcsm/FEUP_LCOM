#include <lcom/lcf.h>

#include "game.h"
#include "keyboard.h"

#include "mouse.h"
#include "packet.h"
#include "video.h"
#include "cursor.h"
#include "xpm.h"
#include "pixmap/cursor_pixmap.h"
#include "pixmap/play.h"
#include "pixmap/dice1.h"
#include "pixmap/dice2.h"
#include "pixmap/dice3.h"
#include "pixmap/dice4.h"
#include "pixmap/dice5.h"
#include "pixmap/dice6.h"
#include "pixmap/ball.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

static int xCursor = 0;
static int yCursor = 0;

int currentPull_x = 0, 
    currentPull_y = 0,
    clickPos_x = 0,
    clickPos_y = 0;
bool pull = false;




xpm_image_t imgC;
uint16_t *mCursor; //= (uint16_t*)xpm_load(cursor_xpm_xpm, XPM_5_6_5, &imgC);

xpm_image_t imgBall;
uint16_t *mBall;

uint16_t  transp;

xpm_image_t imgBoard;
uint16_t *board;


////////////////////////  DICE  ///////////////////////////
xpm_image_t imgDiceOne;
uint16_t *diceOne;

xpm_image_t imgDiceTwo;
uint16_t *diceTwo;

xpm_image_t imgDiceThree;
uint16_t *diceThree;

xpm_image_t imgDiceFour;
uint16_t *diceFour;

xpm_image_t imgDiceFive;
uint16_t *diceFive;

xpm_image_t imgDiceSix;
uint16_t *diceSix;

/////////////////////////////////////////////////////////////

uint16_t dynamicUMOUSEArray[24*36];
uint16_t dynamicUARROWArray[200*200];
void underMouse(/*int xcursor, int ycursor, int cursorwidth, int cursorheight*/){
    int h_res = get_h_res();
  //int bits_per_pixel = get_bits_per_pixel();
    void *video_mem = get_video_mem();

    for (int i = xCursor; i < xCursor + imgC.height; i++){
        for (int j = yCursor; j < yCursor + imgC.width; j++) {
            uint16_t *ptr_VM = (uint16_t*)video_mem;
            ptr_VM += (i * h_res + j);

            uint16_t color = *ptr_VM;
            dynamicUMOUSEArray[i * h_res + j] = color;
        }
    }
}
void underArrow(){
    int h_res = get_h_res();
    //int bits_per_pixel = get_bits_per_pixel();
    void *video_mem = get_video_mem();

    printf("%d | %d\n", clickPos_x, clickPos_y);

    for (int i =xCursor; i < xCursor + 40; i++){
        if(i<0){continue;}
        for (int j = yCursor; j < yCursor + 40; j++) {
            if(j<0){continue;}
            uint16_t *ptr_VM = (uint16_t*)video_mem;
            ptr_VM += (i * h_res + j);

            uint16_t color = *ptr_VM;
            dynamicUARROWArray[i * h_res + j] = color;
        }
    }
}


Game* Start() {
    Game *game = malloc(sizeof(Game));

    vg_start(GAME_MODE);

    /*game->gameCursor = newCursor();
    xCursor = get_h_res() / 2;
    yCursor = get_v_res() / 2;*/

    board = (uint16_t*)xpm_load(board_pre_xpm, XPM_5_6_5, &imgBoard);

    diceOne = (uint16_t*)xpm_load(dice1_xpm, XPM_5_6_5, &imgDiceOne);
    diceTwo = (uint16_t*)xpm_load(dice2_xpm, XPM_5_6_5, &imgDiceTwo);
    diceThree = (uint16_t*)xpm_load(dice3_xpm, XPM_5_6_5, &imgDiceThree);
    diceFour = (uint16_t*)xpm_load(dice4_xpm, XPM_5_6_5, &imgDiceFour);
    diceFive = (uint16_t*)xpm_load(dice5_xpm, XPM_5_6_5, &imgDiceFive);
    diceSix = (uint16_t*)xpm_load(dice6_xpm, XPM_5_6_5, &imgDiceSix);

    mBall = (uint16_t*)xpm_load(ball_xpm, XPM_5_6_5, &imgBall);

    mCursor = (uint16_t*)xpm_load(cursor_xpm_xpm, XPM_5_6_5, &imgC);
    transp = xpm_transparency_color(XPM_5_6_5);

    game->gState = MENU;
    
    draw_xpm(0,0, board, imgBoard, transp);

    draw_xpm(700, 980, diceOne, imgDiceOne, transp);
    
    underMouse();
    draw_xpm(xCursor, yCursor, mCursor, imgC, transp);

    srand(time(0));

    if (kbd_subscribe_int(&bit_no_kbd) != 0)
      return NULL;

    if (timer_subscribe_int(&bit_no_timer) != 0)
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

void drawDice(int y, int x, int number){
    switch (number)
    {
        case 1:
            draw_xpm(y, x, diceOne, imgDiceOne, transp); 
            break;
        case 2:
            draw_xpm(y, x, diceTwo, imgDiceTwo, transp);
            break;
        case 3:
            draw_xpm(y, x, diceThree, imgDiceThree, transp);
            break;
        case 4:
            draw_xpm(y, x, diceFour, imgDiceFour, transp);
            break;
        case 5:
            draw_xpm(y, x, diceFive, imgDiceFive, transp);
            break;
        case 6:
            draw_xpm(y, x, diceSix, imgDiceSix, transp);
            break;
        default:
            break;
    }
}

void randDice(){
    int first = 1 + rand() % 6;
    int second = 1 + rand() % 6;

    drawDice(700, 980, first);
    drawDice(700, 1100, second);
}


void Handler(Game* game){
    extern uint32_t mouseData;
    struct packet pp;
    extern uint32_t kbdData;

    int ipc_status;
    message msg;
    int r;

    uint64_t irq_set_timer = BIT(bit_no_timer);
    uint64_t irq_set_kbd = BIT(bit_no_kbd);
    uint64_t irq_set_mouse = BIT(bit_no_mouse);


    int byteCounter = 0;
    int ticks = 0;

    while (kbdData != ESC) {
		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
			printf("driver_receive failed with: %d", r);
            return;
		}
		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
				case HARDWARE: /* hardware interrupt notification */
                    if (msg.m_notify.interrupts & irq_set_kbd) {
                        kbdData = 0;
                        kbd_ih();
                        
                        if (kbdData == ESC)
                            game->gState = EXIT;

                        if (kbdData == 0x39){
                            if (game->gState == MENU)
                                game->gState = PLAYING;
                            else if (game->gState == PLAYING){
                                game->gState = MENU;
                                ticks = 0;
                                }
                        }
                    }
                    if (msg.m_notify.interrupts & irq_set_timer){
                        if (game->gState == PLAYING){
                            ticks++;
                            if (ticks % (sys_hz() / 8) == 0)
                                randDice();
                        }
                        
                    }
		            if (msg.m_notify.interrupts & irq_set_mouse) {
                        mouseData = 0;   
                        mouse_ih();
                        byteCounter++;
                        parseToPacket(byteCounter % 3, mouseData, &pp);
                        

                        if (byteCounter % 3 == 0){

                            process_mouse_event(game, &pp);
                            updateScreen();
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

    if (timer_unsubscribe_int() != 0)
        return -1;

    vg_exit();

    return 0;
    }

GameState getGameState(Game* game){
    return game->gState;
}


void clearMouse(/*int xcursor, int ycursor, int cursorwidth, int cursorheight*/){
    int h_res = get_h_res();
  //int bits_per_pixel = get_bits_per_pixel();
    void *video_mem = get_video_mem();

    for (int i = xCursor; i < xCursor + imgC.height; i++){
        for (int j = yCursor; j < yCursor + imgC.width; j++) {
            uint16_t *ptr_VM = (uint16_t*)video_mem;
            ptr_VM += (i * h_res + j);

            *ptr_VM = dynamicUMOUSEArray[i * h_res + j];
        }
    }
}

void process_mouse_event(Game *game, struct packet* pp){
    if (xCursor + imgC.height < get_v_res() && yCursor + imgC.width < get_h_res()){
        clearMouse();
    }
    
    updatePosition(pp, &yCursor, &xCursor);

    GameState gameSt = getGameState(game);

    if (pp->lb){
        if(!pull){
            printf("pulling\n");
            pull = true;
            currentPull_x = 0;
            currentPull_y = 0;
            clickPos_x = yCursor;
            clickPos_y = xCursor;
        }

        currentPull_x+=pp->delta_x;
        currentPull_y+=pp->delta_y;

        underArrow();
        int pixelDraw_x = 0;
        int pixelDraw_y = 0;
        for (int i = 0; i < abs(currentPull_x); i++){
            for (int j = 0; j < abs(currentPull_y); j++){

                if(currentPull_x>0)
                    pixelDraw_x = clickPos_x - i;
                else
                    pixelDraw_x = clickPos_x + i;

                if(currentPull_y>0)
                    pixelDraw_y = clickPos_y + j;
                else
                    pixelDraw_y = clickPos_y - j;

                if(pixelDraw_x > 0 && pixelDraw_y > 0 )
                    changePixel(pixelDraw_x, pixelDraw_y, 0x0080);
            }
        }
        printf("pixelDraw_x:%d | pixelDraw_y:%d \n",  pixelDraw_x, pixelDraw_y);
    }else{
        if(pull){
            pull = false;
            currentPull_x = 0;
            currentPull_y = 0;
        }
    }
    
    if (pp->lb){
        switch(gameSt) {
            case MENU:   
                break;
            default:	
                break;
        }
    }

    if (xCursor + imgC.height < get_v_res() && yCursor + imgC.width < get_h_res()){
        underMouse();
        draw_xpm(xCursor, yCursor, mCursor, imgC, transp);
    }

    resetPacket(pp);

}
void updateScreen(){
    int h_res = get_h_res();
    int v_res = get_v_res();
    int bytes_per_pixel = get_bits_per_pixel();
    void *video_mem = get_video_mem();
    memset(video_mem, 0,  h_res * v_res * bytes_per_pixel);

    if(pull == true){drawMousePull();}
}
void drawMousePull(){
    draw_xpm(0,0, board, imgBall, transp);
}
