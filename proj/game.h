#pragma once
#include "cursor.h"


uint8_t bit_no_kbd;
uint8_t bit_no_mouse;
uint8_t bit_no_timer;


int const aaFIRST_CELL_X = 205;
int const aaFIRST_CELL_Y = 201;
int const aaCELL_WIDTH = 59;
int const aaCELL_HEIGHT = 63;
uint16_t aaCELL_COLOR = 0x001f;
uint16_t aaWHITE_CELL = 0xffff;

#define PI 3.14159265
typedef enum {
    MENU,
    MODE_MENU, 
    PLAYING,
    EXIT
} GameState; 

typedef struct {
    cursor *gameCursor;
    GameState gState;

} Game;

typedef struct {
    int speedX,
        speedY,
        posX,
        posY,
        id;
    
} Bullet;

typedef struct {
    int x,
        y;
    bool alive;
} Block;

Block blocks[256];
Bullet *bullet;

Game* Start();

GameState getGameState(Game* game);

void Handler(Game* game);

int End();

void process_mouse_event(Game* game, struct packet* pp);

void clearArrow();
void underArrow();

void underBall();

void updateScreen();
void drawMousePull();
void drawBullet();
void drawBlocks();
void shootBullet(int pullX, int pullY);

void paintCell();


void nextLevel();


