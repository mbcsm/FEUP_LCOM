#ifndef MENU_H
#define MENU_H

#define PLAY_BUTTON_Y           200
#define HIGHSCORES_BUTTON_Y     400
#define EXIT_BUTTON_Y           600

#include "xpm.h"
#include "font.h"
#include "cursor.h"

/* ------------- XPMs --------------- */

#include "pixmap/menu/exit_button.h"
#include "pixmap/menu/exit_button_over.h"
#include "pixmap/menu/highscores_button.h"
#include "pixmap/menu/highscores_button_over.h"
#include "pixmap/menu/play_button.h"
#include "pixmap/menu/play_button_over.h"

/*------------------------------------*/

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

int startMenu();

int menuIH(bool mouse, bool kbd, struct packet* pp, uint32_t kbdData);

int displayMenu();

void displayHighscores();

#endif
