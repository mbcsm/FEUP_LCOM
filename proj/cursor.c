#include <lcom/lcf.h>

#include "cursor.h"


int x_Cursor = 500;
int y_Cursor = 500;

xpm_image_t imgC;
uint16_t *mCursor;
uint16_t transp;

uint16_t dynamicUMOUSEArray[24*36];

int startCursor(){
    mCursor = (uint16_t*)xpm_load(cursor_xpm_xpm, XPM_5_6_5, &imgC);
    transp = xpm_transparency_color(XPM_5_6_5);
    underMouse();
    draw_xpm(x_Cursor, y_Cursor, mCursor, imgC, transp);

    return 0;
}

void (getPosition)(int *x, int *y){
    *x = x_Cursor;
    *y = y_Cursor;
}

void (updatePosition)(struct packet *pp, int *x, int *y){
    *x += (int)pp->delta_x;
    *y -= (int)pp->delta_y;

    if (*x > get_h_res())
        *x = get_h_res();
    else if (*x < 0)
        *x = 0;

    if (*y > get_v_res())
        *y = get_v_res();
    else if (*y < 0)
        *y = 0;

        x_Cursor = *x;
        y_Cursor = *y;
}

void clearMouse(/*int xcursor, int ycursor, int cursorwidth, int cursorheight*/){
    int h_res = get_h_res();
  //int bits_per_pixel = get_bits_per_pixel();
    void *video_mem = get_video_mem();

    for (int i = y_Cursor; i < y_Cursor + imgC.height; i++){
        for (int j = x_Cursor; j < x_Cursor + imgC.width; j++) {
            uint16_t *ptr_VM = (uint16_t*)video_mem;
            ptr_VM += (i * h_res + j);

            *ptr_VM = dynamicUMOUSEArray[i * h_res + j];
        }
    }
}

void underMouse(/*int xcursor, int ycursor, int cursorwidth, int cursorheight*/){
    int h_res = get_h_res();
  //int bits_per_pixel = get_bits_per_pixel();
    void *video_mem = get_video_mem();

    for (int i = y_Cursor; i < y_Cursor + imgC.height; i++){
        for (int j = x_Cursor; j < x_Cursor + imgC.width; j++) {
            uint16_t *ptr_VM = (uint16_t*)video_mem;
            ptr_VM += (i * h_res + j);

            uint16_t color = *ptr_VM;
            dynamicUMOUSEArray[i * h_res + j] = color;
        }
    }
}
