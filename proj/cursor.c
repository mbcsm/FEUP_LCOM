#include <lcom/lcf.h>
#include "cursor.h"
#include "video.h"
#include "pixmap/cursor_pixmap.h"

    uint16_t *spritet;
    uint16_t  transpi;
    xpm_image_t imge;

cursor * (newCursor)(){
    cursor *c = malloc(sizeof(cursor));
    c->x = get_h_res() / 2;
    c->y = get_v_res() / 2;
    
    spritet = (uint16_t*)xpm_load(cursor_xpm_xpm, XPM_5_6_5, &(imge));

    transpi = xpm_transparency_color(XPM_5_6_5);

    c->verticalRes = c->img.height;
    c->horizontalRes = c->img.width;

    return c;
}

void (getPosition)(cursor *c, int *x, int *y){
    *x = c->x;
    *y = c->y;
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
}

uint16_t *dynamicArray[24*36] = {0};
//int size = 2;
//dynamicArray = malloc(24*36 * sizeof(uint16_t));

void (drawCursor)(cursor *c){
    int cx ,cy;
    getPosition(c, &cy, &cx);

    /*dynamicArray = malloc(24 * 36 * sizeof(uint16_t));
    
    uint16_t *ptr_VM = (uint16_t*)video_mem;
    ptr_VM += (cy * h_res + cx);
                
    uint16_t *back = dynamicArray;
    memcpy(back, ptr_VM, sizeof(uint16_t) * 36 * 24);*/

    if (cx >= 0 && cy >= 0 && cx < get_h_res() && cy < get_v_res()){
        for (int j = cy; j < cy + 36; j++)
            for (int i = cx; i < cx + 24; i++){ 
                if (j > get_v_res())
                    return;
                uint16_t *ptr_VM = (uint16_t*)video_mem;
                ptr_VM += (i * h_res + j);
                
                //uint16_t *back = dynamicArray;
                
                dynamicArray[j * 24 + i] = (ptr_VM); /////// HERE
                //printf("lul");
                //back++;
                
            }    
    //draw_xpmc(cx, cy);
    
    }
}

void (clearCursor)(cursor * c){
       
    int x ,y;
    getPosition(c, &y, &x);

    //int h_res = get_h_res();
  //int bits_per_pixel = get_bits_per_pixel();
  //void *video_mem = get_video_mem();

  /*xpm_image_t img;
  uint16_t *sprite = (uint16_t*)xpm_load(cursor_xpm_xpm, XPM_5_6_5, &img);

  const uint16_t  transp = xpm_transparency_color(XPM_5_6_5);

  for (int i = x; i < x + img.height; i++){
    for (int j = y; j < y + img.width; j++) {
      uint16_t *ptr_VM = (uint16_t*)video_mem;
      ptr_VM += (i * h_res + j);
      if(*(sprite) != transp)
        *ptr_VM = 0;
      (sprite)++;
    }
}*/
/*
if (x >= 0 && y >= 0 && x < get_h_res() && y < get_v_res()){
        for (int j = y; j < y + 36; j++)
            for (int i = x; i < x + 24; i++){ 
                if (j > get_v_res())
                    return;
                uint16_t *ptr_VM = (uint16_t*)video_mem;
                ptr_VM += (i * h_res + j);
                
                //uint16_t *back = dynamicArray;
                
                *ptr_VM = *(dynamicArray[j * 24 + i]); /////// HERE
}
}*/
}


