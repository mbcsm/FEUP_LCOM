#ifndef MENU_H
#define MENU_H

#define PLAY_BUTTON_Y           100
#define HIGHSCORES_BUTTON_Y     500
#define EXIT_BUTTON_Y           900

typedef enum {
    VOID,
    PLAY_BUTTON_OVER, 
    HIGHSCORES_BUTTON_OVER,
    EXIT_BUTTON_OVER,
    HIGHSCORES
} Menu;

typedef enum {
    NON,
    LB_PRESS,
    LB_UP,
    CLICKED    
} Click;

void startMenu();

void menuIH(bool mouse, bool kbd, struct packet pp, uint32_t kbdData);

void displayMenu();

void displayHighscores();

#endif
