#pragma once
/** @defgroup game game
 * @{
 *
 * utils for game
 */
#include "cursor.h"


uint8_t bit_no_kbd;
uint8_t bit_no_mouse;
uint8_t bit_no_timer;
uint8_t bit_no_rtc;


#define PI 3.14159265
typedef enum {
    MENU,
    PLAYING,
    EXIT
} GameState; 

typedef struct {
    //cursor *gameCursor;
    GameState gState;

} Game;

typedef struct {
    int speedX,
        speedY,
        posX,
        posY,
        x,
        y,
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

/**
 * @brief Handles every interruption made by the drivers
 * @param game pointer to the Game struct of the current session
*/
void Handler(Game* game);

/**
 * @brief Closes all the interruptions at the end of the program
*/
int End();

/**
 * @brief processes mouse event by changing relevant information like pull values and also prints the cursor on to the screen
 * @param game pointer to the Game struct of the current session
 * @param pp packet of the mouse input 
*/
void process_mouse_event(Game* game, struct packet* pp);

/**
 * @brief erases cursor from screen
*/
void clearArrow();

/**
 * @brief fills the backbuffer of whatś behind the cursor image
*/
void underArrow();

/**
 * @brief fills the backbuffer of the board with the available blocks
*/
void saveBoard();

/**
 * @brief Draws the board with the "alive" blocks on to the screen
*/
void drawBoard();

/**
 * @brief Calls a series of functions to print every element on to the screen during play time
*/
void updateScreen();

/**
 * @brief Draws the pull of the mouse in game
*/
void drawMousePull();

/**
 * @brief Draws the bullet fired by the player
*/
void drawBullet();

/**
 * @brief Draws the blocks that are alive and that are going to be saved to the backbuffer
*/
void drawBlocks();

/**
 * @brief Calculates the speed with which the bullet is going to get fired at at both the x and  componnent, depending on how the pulling event is at the moment
 * @param pullX pull x component
 * @param pullX pull y component 
*/
void shootBullet(int pullX, int pullY);

/**
 * @brief Paints a cell of the board with a block
*/
void paintCell();

/**
 * @brief Advances the player on to the next level
*/
void nextLevel();


/**@}*/

