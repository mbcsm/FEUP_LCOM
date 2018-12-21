#pragma once
#include "cursor.h"

uint8_t bit_no_kbd;
uint8_t bit_no_mouse;
uint8_t bit_no_timer;

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

Game* Start();

GameState getGameState(Game* game);

void Handler(Game* game);

int End();

void process_mouse_event(Game* game, struct packet* pp);


