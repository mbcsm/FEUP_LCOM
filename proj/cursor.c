#include <lcom/lcf.h>
#include "cursor.h"

#include "video.h"
#include "bitmap.h"

cursor * (newCursor)(){
    cursor *c = malloc(sizeof(cursor));
    c->x = get_h_res() / 2;
    c->y = get_v_res() / 2;

    c->crs = loadBitmap("/home/Desktop/cursor.bmp");
    
    if (c->crs == NULL)
     printf("NULL cursor");

    return c;
}

void (getPosition)(cursor *c, int *y, int *x){
    *x = c->x;
    *y = c->y;
}

void (updatePosition)(struct packet *pp, cursor *c){
    c->x += (int)pp->delta_x;
    c->y -= (int)pp->delta_y;

    if (c->x > get_h_res())
        c->x = get_h_res();
    else if (c->x < 0)
        c->x = 0;

    if (c->y > get_v_res())
        c->y = get_v_res();
    else if (c->y < 0)
        c->y = 0;
}

void (drawCursor)(cursor *c){
    int cx = c->x, cy = c->y;
    getPosition(c, &cy, &cx);

    cx += h_res/2;
    cy += v_res/2;

    if (cx >= 0 && cy >= 0 && cx < get_h_res() && cy < get_v_res())
        for (int j = cy; j < cy + 4; j++)
            for (int i = cx; i < cx + 4; i++){
            changePixel(i, j, 255);
            }

    drawBitmap(c->crs, cx, cy, ALIGN_LEFT);
}
