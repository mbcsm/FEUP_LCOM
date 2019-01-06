#include <lcom/lcf.h>

#include "menu.h"
#include "xpm.h"
#include "font.h"
#include "cursor.h"

/* ------------- XPMs --------------- */
#include "pixmap/play_button.h"



uint16_t *playbutton;
xpm_image_t imgPlayButton;
  
/*------------------------------------*/
Menu menuState = VOID;


void startMenu(){
    
    //board = (uint16_t*)xpm_load(board_pre_xpm, XPM_5_6_5, &imgBoard);
    playbutton = (uint16_t*)xpm_load(play_button, XPM_5_6_5, &imgPlayButton);

    //draw_xpm()
}

void menuIH(bool mouse, bool kbd, struct packet pp, uint32_t kbdData){
    if (mouse){
        bool lb = pp.lb;
        if (lb)
        printf("erg");
        
        
    }
    else if (kbd){
        
        switch (kbdData)
        {
            case 0x9c: //ENTER BREAKCODE
                if (menuState == PLAY_BUTTON_OVER)
                    return ; //SOMETHING ---------------------------------------
                if (menuState == HIGHSCORES_BUTTON_OVER){
                    menuState = HIGHSCORES;
                    displayMenu();
                }
                if (menuState == EXIT_BUTTON_OVER)
                    return; //SOMETHING-----------------------------------------
                break;

            case 0x8e: // BACKSPACE BREAKCODE
                if (menuState == HIGHSCORES){
                    menuState = VOID;
                    displayMenu();
                }
                break;
            case 0x48: // NUMPAD 8 - (UP ARROW)
                if (menuState == PLAY_BUTTON_OVER){
                    menuState = EXIT_BUTTON_OVER;
                    displayMenu();
                }
                if (menuState == HIGHSCORES_BUTTON_OVER){
                    menuState = PLAY_BUTTON_OVER;
                    displayMenu();
                }
                if (menuState == EXIT_BUTTON_OVER){
                    menuState = HIGHSCORES_BUTTON_OVER;
                    displayMenu();
                }
                break;

            case 0x50: // NUMPAD 2 - (DOWN ARROW)
                if (menuState == PLAY_BUTTON_OVER){
                    menuState = HIGHSCORES_BUTTON_OVER;
                    displayMenu();
                }
                if (menuState == HIGHSCORES_BUTTON_OVER){
                    menuState = EXIT_BUTTON_OVER;
                    displayMenu();
                }
                if (menuState == EXIT_BUTTON_OVER){
                    menuState = PLAY_BUTTON_OVER;
                    displayMenu();
                }
                break;
            default:
                break;
        }
    }

}

void displayMenu(){
    int x, y;

    //draw_xpm()
    
    switch (menuState)
    {
        case VOID:
            x = align_x_center(imgPlayButton);
            y = PLAY_BUTTON_Y;
            draw_xpm(x, y, playbutton, imgPlayButton, getTransparency());
            
            y = HIGHSCORES_BUTTON_Y;
            //draw_xpm(x, y, );

            y = EXIT_BUTTON_Y;
            //draw_xpm(x, y, );
            break;

        case PLAY_BUTTON_OVER:
            x = align_x_center(imgPlayButton);
            y = PLAY_BUTTON_Y;
            draw_xpm(x, y, playbutton, imgPlayButton, getTransparency());
            
            y = HIGHSCORES_BUTTON_Y;
            //draw_xpm(x, y, );

            y = EXIT_BUTTON_Y;
            //draw_xpm(x, y, );
            break;

        case HIGHSCORES_BUTTON_OVER:
            x = align_x_center(imgPlayButton);
            y = PLAY_BUTTON_Y;
            draw_xpm(x, y, playbutton, imgPlayButton, getTransparency());
            
            y = HIGHSCORES_BUTTON_Y;
            //draw_xpm(x, y, );

            y = EXIT_BUTTON_Y;
            //draw_xpm(x, y, );
            break;

        case EXIT_BUTTON_OVER:
            x = align_x_center(imgPlayButton);
            y = PLAY_BUTTON_Y;
            draw_xpm(x, y, playbutton, imgPlayButton, getTransparency());
            
            y = HIGHSCORES_BUTTON_Y;
            //draw_xpm(x, y, );

            y = EXIT_BUTTON_Y;
            //draw_xpm(x, y, );
            break;

        case HIGHSCORES:
            /* code */
            break;
    
        default:
            break;
    }

}

void displayScores(){

}
