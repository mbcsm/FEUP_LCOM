#include <lcom/lcf.h>

#include "game.h"
#include "keyboard.h"

#include "mouse.h"
#include "packet.h"
#include "video.h"
#include "rtc.h"
#include "cursor.h"
#include "xpm.h"
//#include "pixmap/cursor_pixmap.h"
#include "pixmap/play.h"
#include "pixmap/dice1.h"
#include "pixmap/dice2.h"
#include "pixmap/dice3.h"
#include "pixmap/dice4.h"
#include "pixmap/dice5.h"
#include "pixmap/dice6.h"

//#include "pixmap/fonts/white-size22/z.h"

#include "pixmap/b.h"

#include "pixmap/ball.h"
#include "pixmap/ball_filler.h"

#include "board.h"
#include "font.h"
#include "menu.h"
#include "score.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

int level = 1;

int xCursor = 500;
int yCursor = 500;

int currentPull_x = 0, 
    currentPull_y = 0,
    clickPos_x = 0,
    clickPos_y = 0;
bool pull = false;

int MOUSE_PULL_START_X = 500;
int MOUSE_PULL_START_Y = 900;
int MOUSE_MAX_PULL = 300;

int mouse_bubbles_pos_x[3] = {0,0,0};
int mouse_bubbles_pos_y[3] = {0,0,0};

int const bFIRST_CELL_X = 205;
int const bFIRST_CELL_Y = 201;
int const bCELL_WIDTH = 55;
int const bCELL_HEIGHT = 60;
uint16_t bCELL_COLOR = 0x001f;
uint16_t bWHITE_CELL = 0xffff;

int totalBlocks = 0;




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

uint16_t dynamicUARROWArray[200*200];
uint16_t dynamicUBALLArray[1440*840];

void underBall(){
    int h_res = get_h_res();
    void *video_mem = get_video_mem();

    for (int i = MOUSE_PULL_START_Y; i < MOUSE_PULL_START_Y - currentPull_y; i++){
        for (int j = MOUSE_PULL_START_X; j < MOUSE_PULL_START_Y - currentPull_x; j++) {
            uint16_t *ptr_VM = (uint16_t*)video_mem;
            ptr_VM += (i * h_res + j);

            uint16_t color = *ptr_VM;
            dynamicUBALLArray[i * h_res + j] = color;
        }
    }
}
void underArrow(){
    int h_res = get_h_res();
    //int bits_per_pixel = get_bits_per_pixel();
    void *video_mem = get_video_mem();

    //printf("%d | %d\n", clickPos_x, clickPos_y);

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
    game->gState = MENU;


    blocks[0].x = 600;
    blocks[0].y = 400;

    vg_start(GAME_MODE);

    board = (uint16_t*)xpm_load(board_pre_xpm, XPM_5_6_5, &imgBoard);

    /*diceOne = (uint16_t*)xpm_load(dice1_xpm, XPM_5_6_5, &imgDiceOne);
    diceTwo = (uint16_t*)xpm_load(dice2_xpm, XPM_5_6_5, &imgDiceTwo);
    diceThree = (uint16_t*)xpm_load(dice3_xpm, XPM_5_6_5, &imgDiceThree);
    diceFour = (uint16_t*)xpm_load(dice4_xpm, XPM_5_6_5, &imgDiceFour);
    diceFive = (uint16_t*)xpm_load(dice5_xpm, XPM_5_6_5, &imgDiceFive);
    diceSix = (uint16_t*)xpm_load(dice6_xpm, XPM_5_6_5, &imgDiceSix);*/

    
    if (startMenu() == 0)
        printf("Started Menu");
    if (startCursor() == 0)
        printf("Started Cursor");

    loadScores();

    /*xpm_image_t imgData;
    uint16_t *data;

    data = (uint16_t*)xpm_load(zw_xpm, XPM_5_6_5, &imgData);
    draw_xpm(10, 10, data, imgData, getTransparency());*/

    printstring("lcom", 4, "w", 2, 500);
    
    
    /*draw_xpm(0,0, board, imgBoard, transp);
    startBoard();*/


    //srand(time(NULL));

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

    if (rtc_subscribe_int(&bit_no_rtc) != 0)
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
    uint64_t irq_set_rtc = BIT(bit_no_rtc);


    int byteCounter = 0;
    int ticks = 0;

    while (game->gState != EXIT) {
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
                        
                        if (kbdData == ESC){
                            if (game->gState == MENU){
                                game->gState = EXIT;
                                break;
                            }
                            else if (game->gState == PLAYING){
                                game->gState = MENU;
                                addNewScore(200);
                                saveScores();
                                startMenu();
                                startCursor();
                            }
                        }
                        
                        if (game->gState == MENU){
                            int response = menuIH(false, true, &pp, kbdData);                           
                            switch (response)
                            {
                                case 2:
                                    game->gState = EXIT;
                                    break;
                                case 1:
                                    game->gState = PLAYING;
                                    clearScreen();
                                    // start actual game here
                                    break;
                            
                                default:
                                    break;
                            }
                        }

                    }
                    if (msg.m_notify.interrupts & irq_set_timer){
                        if (game->gState == PLAYING){
                            ticks++;
                            //if (ticks % (sys_hz() / 8) == 0)
                                //randDice();
                        }
                        if (ticks > 20000){
                            ticks = 0;
                        }
                        if (game->gState == PLAYING)
                            updateScreen();

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
                    if (msg.m_notify.interrupts & irq_set_rtc) {
                        rtc_ih();
                    }
                    break;
                    
		        default:
					break; /* no other notifications expected: do nothing */
                
			}
            //printf("updateScreen\n");
            /*if (yCursor + imgC.height < get_v_res() && xCursor + imgC.width < get_h_res()){
                clearMouse();
                underMouse();
                draw_xpm(xCursor, yCursor, mCursor, imgC, transp);
            }*/
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

void paintCell(int x, int y){
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
    if (gameSt == PLAYING){
    if (pp->rb){
        if(!pull){
            //printf("pulling\n");
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
            //printf("pull over\n");
            pull = false;
            shootBullet(currentPull_x, currentPull_y);
            currentPull_x = 0;
            currentPull_y = 0;
            /*for(int i = 0; i < 3; i++){draw_xpm(mouse_bubbles_pos_y[i], mouse_bubbles_pos_x[i], mBallFiller, imgBallFiller, transp);}*/
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
    }
    else if (game->gState == MENU){
            int kbd = 0;
            int response = menuIH(true, false, pp, kbd);
            switch (response){
                    case 2:
                        game->gState = EXIT;
                        return;
                    case 1:
                        game->gState = PLAYING;
                        // start actual game here
                        break;
                            
                    default:
                        break;
            }
    }

    
    if (yCursor + imgC.height < get_v_res() && xCursor + imgC.width < get_h_res()){
        underMouse();
        draw_xpm(xCursor, yCursor, mCursor, imgC, transp);
    }

    resetPacket(pp);

}
void updateScreen(){
    draw_xpm(0,0, board, imgBoard, transp);
    drawBlocks();
    if(pull == true){drawMousePull();}
    draw_xpm(xCursor, yCursor, mCursor, imgC, transp);
    if(bullet != NULL){drawBullet();}
}


void drawMousePull(){
    if(currentPull_y >= 0 || currentPull_x == 0 ){return;}

    //printf("drawing mouse pull\n");

    int pixelDraw_x = MOUSE_PULL_START_X;
    int pixelDraw_y = MOUSE_PULL_START_Y;

    int increment_x = -currentPull_x / 3;
    int increment_y = currentPull_y / 3;

    for (int i = 0; i < 3; i++){
        pixelDraw_x += increment_x;
        pixelDraw_y += increment_y;
        mouse_bubbles_pos_x[i] = pixelDraw_x;
        mouse_bubbles_pos_y[i] = pixelDraw_y;
        draw_xpm(pixelDraw_x, pixelDraw_y, mBall, imgBall, transp);
    }
    //printf("___________________\n");
}
void drawBullet(){
    if((bullet -> posX > get_h_res() - 430) || (bullet -> posX < 180)){bullet -> speedX = -bullet -> speedX;}
    if(bullet -> posY < 200){bullet -> speedY = -bullet -> speedY;}
    if(bullet -> posY > MOUSE_PULL_START_Y){
        nextLevel();
        free(bullet);
        bullet = NULL;
        return;
    }
    bullet -> posX += bullet -> speedX;
    bullet -> posY += bullet -> speedY;


    bullet -> x = (bullet -> posX - bFIRST_CELL_X) / bCELL_WIDTH;
    bullet -> y = (bullet -> posY - bFIRST_CELL_Y) / bCELL_HEIGHT;

    draw_xpm(bullet -> posX, bullet -> posY, mBall, imgBall, transp);

    int deleteX = -1, deleteY = -1;
    bool blockCollision = false, blockFound = false;


    if(getpixel(bullet -> posX, bullet -> posY) != bWHITE_CELL
    ||  getpixel(bullet -> posX + imgBall.width, bullet -> posY) != bWHITE_CELL
    ||  getpixel(bullet -> posX, bullet -> posY + imgBall.height) != bWHITE_CELL
    ||  getpixel(bullet -> posX + imgBall.width, bullet -> posY + imgBall.height) != bWHITE_CELL){
        deleteX = bullet -> x;
        deleteY = bullet -> y;
        blockCollision = true;   
    }


    
    if(blockCollision == true){
        //printf("deleteX:%d | deleteY:%d\n", deleteX, deleteY);
        for(int j = 0; j < totalBlocks; j ++){
            if(blocks[j].x == deleteX && blocks[j].y == deleteY && blocks[j].alive){
                blocks[j].alive = false;
                blockFound = true;
                return;
            }
        }
        /*
        if(blockFound){
            if(bullet->speedX > 0 && bullet->speedY > 0){
                if((bullet -> posX - bFIRST_CELL_X) != deleteX){
                    bullet -> speedY = -bullet -> speedY;
                }else{
                    bullet -> speedX = -bullet -> speedX;
                }
                bullet -> posX += bullet -> speedX * 2;
                bullet -> posY += bullet -> speedY * 2;
            }
        }
        */
    }
}

void shootBullet(int pullX, int pullY){
    bullet = malloc(sizeof(Bullet));
    bullet -> id = 1;
    bullet -> posX = MOUSE_PULL_START_X;
    bullet -> posY = MOUSE_PULL_START_Y;

    int speedX = pullX;
    int speedY = pullY;

    while(abs(speedX) > 10 || abs(speedY) >  10){
        speedX = speedX/5;
        speedY = speedY/5;
    }
    while(abs(speedX) < 5 && abs(speedY) <  5){
        speedX = speedX * 2;
        speedY = speedY * 2;
    }

    bullet -> speedX = -speedX;
    bullet -> speedY = speedY;

    for(int i = 0; i < totalBlocks; i++){
        if(blocks[i].alive){
            printf("i: %d |blocks[i].x: %d | blocks[i].y: %d\n",i, blocks[i].x, blocks[i].y);
        }
    }
    printf("_____________________\n");
}

void drawBlocks(){
    for(int i = 0; i < totalBlocks; i++){
        if(blocks[i].alive){
            fill(blocks[i].x * 60 + bFIRST_CELL_X, blocks[i].y * 60 + bFIRST_CELL_Y, 0x001e);
        }
    }
}

void nextLevel(){
    for(int j = 0; j < 256; j ++){
        if(blocks[j].alive){
            blocks[j].y += 1;
            if(blocks[j].y ==12){
                printf("Game OVER!\n");
            }
        }
    }

    for(int i = 0; i < 12; i++){
        srand ( time(NULL) );
        int prob = rand() % 100;
        if(prob < 50){
            blocks[totalBlocks].alive = true;
            blocks[totalBlocks].x = i;
            blocks[totalBlocks].y = 0;
            totalBlocks++;
        }
    }
}
