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

#include "pixmap/b.h"

#include "pixmap/ball.h"
#include "pixmap/ball_filler.h"


#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

static int xCursor = 500;
static int yCursor = 500;

int currentPull_x = 0, 
    currentPull_y = 0,
    clickPos_x = 0,
    clickPos_y = 0;
bool pull = false;

int MOUSE_PULL_START_X = 400;
int MOUSE_PULL_START_Y = 400;
int MOUSE_MAX_PULL = 300;

int mouse_bubbles_pos_x[3] = {0,0,0};
int mouse_bubbles_pos_y[3] = {0,0,0};




xpm_image_t imgC;
uint16_t *mCursor; //= (uint16_t*)xpm_load(cursor_xpm_xpm, XPM_5_6_5, &imgC);

xpm_image_t imgBall;
uint16_t *mBall;
xpm_image_t imgBallFiller;
uint16_t *mBallFiller;

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

    for (int i = yCursor; i < yCursor + imgC.height; i++){
        for (int j = xCursor; j < xCursor + imgC.width; j++) {
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
    mBallFiller = (uint16_t*)xpm_load(ball_filler_xpm, XPM_5_6_5, &imgBallFiller);

    mCursor = (uint16_t*)xpm_load(cursor_xpm_xpm, XPM_5_6_5, &imgC);
    transp = xpm_transparency_color(XPM_5_6_5);

    game->gState = PLAYING;
    
    draw_xpm(0,0, board, imgBoard, transp);

    //draw_xpm(700, 980, diceOne, imgDiceOne, transp);
    

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
        //printf("loop\n");

		if (is_ipc_notify(ipc_status)) { /* received notification */
                        //printf("is_ipc_notify\n");
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
                        if (kbdData & 0x80)
                            drawDice(10, 30 , 6);
                        if (kbdData == 0x1e)
                            drawDice(10, 30 , 4);
                        if (kbdData == 0x1f)
                            drawDice(10, 30 , 5);
                        if (kbdData == 0x20)
                            drawDice(10, 30 , 4);
                        if (kbdData == 0x21)
                            drawDice(10, 30 , 5);

                    }
                    if (msg.m_notify.interrupts & irq_set_timer){
                        if (game->gState == PLAYING){
                            ticks++;
                            //if (ticks % (sys_hz() / 8) == 0)
                                //randDice();
                        }
                        
                    }
		            if (msg.m_notify.interrupts & irq_set_mouse) {
                        //printf("irq_set_mouse\n");
                        mouseData = 0;   
                        mouse_ih();
                        byteCounter++;
                        parseToPacket(byteCounter % 3, mouseData, &pp);
                        

                        if (byteCounter % 3 == 0){
                            process_mouse_event(game, &pp);
                        }
			        }
                    break;
                    
		        default:
					break; /* no other notifications expected: do nothing */
                
			}
            //printf("updateScreen\n");
            updateScreen();

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

    for (int i = yCursor; i < yCursor + imgC.height; i++){
        for (int j = xCursor; j < xCursor + imgC.width; j++) {
            uint16_t *ptr_VM = (uint16_t*)video_mem;
            ptr_VM += (i * h_res + j);

            *ptr_VM = dynamicUMOUSEArray[i * h_res + j];
        }
    }
}

/*uint16_t getpixel(int x, int y){
    uint16_t color;
    int h_res = get_h_res();
  //int bits_per_pixel = get_bits_per_pixel();
    void *video_mem = get_video_mem();
    uint16_t *ptr_VM = (uint16_t*)video_mem;
    ptr_VM += (y * h_res + x);

    color = *ptr_VM;

    return color;
}*/
xpm_image_t imgb;
uint16_t *b;// = (uint16_t*)xpm_load(b_xpm, XPM_5_6_5, &imgb);
uint16_t black = 0;

void fill(int x, int y, uint16_t color){
    if (getpixel(x,y) > 0xdddd){
        changePixel(x,y, color);
        fill(x+1, y, color);
        fill(x, y+1, color);
        fill(x-1, y, color);
        fill(x, y-1, color);
    }
}

void refill(int x, int y, uint16_t oldColor, uint16_t color){
    if (getpixel(x,y) == oldColor){
        changePixel(x,y, color);
        refill(x+1, y, oldColor, color);
        refill(x, y+1, oldColor, color);
        refill(x-1, y, oldColor, color);
        refill(x, y-1, oldColor, color);
    }
}

bool emptyCell(int x, int y){
    y = y + 63;
    if (x < 175 || x > 870 || y < 180 || y > 925)
        return false;
    if (getpixel(x, y) > 0xdddd)
        return true;
    return false;
}

void paintCell(){
    int x = xCursor, y = yCursor;
    do {
        if (x > 175 && x < 870 && y > 180 && y < 925){
            fill(x, y, 0x001e);
        }
        if (emptyCell(x,y)){
            //sleep(1);
            refill(x, y, 0x001e, 0xffff);
            y = y + 63;
        }
        else{
            fill(x, y, 0x001e);
            return;
        }
    } while (emptyCell(x,y));

    fill(x, y, 0x001e);
}

void process_mouse_event(Game *game, struct packet* pp){

    mCursor = (uint16_t*)xpm_load(cursor_xpm_xpm, XPM_5_6_5, &imgC);
    if (yCursor + imgC.height < get_v_res() && xCursor + imgC.width < get_h_res()){
        clearMouse();
    }
    
    updatePosition(pp, &xCursor, &yCursor);
    

    GameState gameSt = getGameState(game);

    if (pp->rb){
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
    }else{
        if(pull){
            pull = false;
            shootBullet(currentPull_x, currentPull_y);
            currentPull_x = 0;
            currentPull_y = 0;
            for(int i = 0; i < 3; i++){draw_xpm(mouse_bubbles_pos_y[i], mouse_bubbles_pos_x[i], mBallFiller, imgBallFiller, transp);}
        }
    }

    if (pp->lb)
        switch(gameSt) {
            case MENU:
                if (xCursor > 200 && yCursor > 200){
                    game->gState = PLAYING;
                    board = (uint16_t*)xpm_load(board_pre_xpm, XPM_5_6_5, &imgBoard);
                    //clearScreen();
                    draw_xpm(0,0, board, imgBoard, transp);
                }
                if (xCursor < 50 && yCursor < 50){
                    game->gState = EXIT;
                }
                break;

            case PLAYING:
                //getPosition(c, &x, &y);              coordinates to allow painting  top 175x  180y   to 870x  925y
                //paintCell();
                
                
                break;
        
            default:
					break;
        }
    
    if (yCursor + imgC.height < get_v_res() && xCursor + imgC.width < get_h_res()){
        underMouse();
        draw_xpm(xCursor, yCursor, mCursor, imgC, transp);
    }

    resetPacket(pp);

}
void updateScreen(){
    if(bullet != NULL){drawBullet();}
    if(pull == true){drawMousePull();}
}


void drawMousePull(){
    if(currentPull_y >= 0 || currentPull_x == 0 ){return;}

    printf("drawing mouse pull\n");

    int pixelDraw_x = MOUSE_PULL_START_X;
    int pixelDraw_y = MOUSE_PULL_START_Y;

    int increment_x = -currentPull_x / 3;
    int increment_y = currentPull_y / 3;

    

    for(int i = 0; i < 3; i++){draw_xpm(mouse_bubbles_pos_y[i], mouse_bubbles_pos_x[i], mBallFiller, imgBallFiller, transp);}
    for (int i = 0; i < 3; i++){
        pixelDraw_x += increment_x;
        pixelDraw_y += increment_y;
        mouse_bubbles_pos_x[i] = pixelDraw_x;
        mouse_bubbles_pos_y[i] = pixelDraw_y;

        draw_xpm(pixelDraw_x, pixelDraw_y, mBall, imgBall, transp);
    }
}
void drawBullet(){
    draw_xpm(bullet -> posY, bullet -> posX, mBallFiller, imgBallFiller, transp);

     if(bullet -> posX > get_h_res() - 50)
        bullet -> speedX = -bullet -> speedX;
    if(bullet -> posX < 0)
        bullet -> speedX = -bullet -> speedX;
    if(bullet -> posY < 50)
        bullet -> speedY = -bullet -> speedY;
    if(bullet -> posY > get_v_res() - 500){
        free(bullet);
        bullet = NULL;
        return;
    }

    if(bullet -> speedX > 0)
        bullet -> posX += 10;
    else
        bullet -> posX -= 10;

    if(bullet -> speedY > 0)
        bullet -> posY += 10;
    else
        bullet -> posY -= 10;

   
    
    draw_xpm(bullet -> posY, bullet -> posX, mBall, imgBall, transp);

    
}

void shootBullet(int pullX, int pullY){
    bullet = malloc(sizeof(Bullet));
    bullet -> id = 1;
    bullet -> posX = MOUSE_PULL_START_X;
    bullet -> posY = MOUSE_PULL_START_Y;


    int speedX = 10 * pullX/pullY;
    int speedY = 10 * pullY/pullX;


    bullet -> speedX = speedX;
    bullet -> speedY = -speedY;    
}
