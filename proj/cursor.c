#include <lcom/lcf.h>
#include "cursor.h"
#include "video.h"
#include "cursor_pixmap.h"

cursor * (newCursor)(){
    cursor *c = malloc(sizeof(cursor));
    c->x = get_h_res() / 2;
    c->y = get_v_res() / 2;
    
    c->crs = (uint16_t*)xpm_load(cursor_xpm, XPM_5_6_5, &c->img);

    c->transp = xpm_transparency_color(XPM_5_6_5);

    c->verticalRes = c->img.height;
    c->horizontalRes = c->img.width;

    return c;
}

void (getPosition)(cursor *c, int *x, int *y){
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
    int cx ,cy;
    getPosition(c, &cy, &cx);

    if (cx >= 0 && cy >= 0 && cx < get_h_res() && cy < get_v_res()){
        /*for (int j = cy; j < cy + c->verticalRes; j++)
            for (int i = cx; i < cx + c->horizontalRes; i++){ 
                if (j > get_v_res())
                    return;
                
            }
                
        for (int j = cy; j < cy + 4; j++) // A ELIMINAR
            for (int i = cx; i < cx + 4; i++){ 
                if (j > get_v_res())
                    return;
                changePixel(i, j, 255);
            }*/
    
    

    for (int i = cy; i < cy + c->img.height; i++){
        for (int j = cx; j < cx + c->img.width; j++) {
            uint16_t *ptr_VM = (uint16_t*)video_mem;
            ptr_VM += (i * get_h_res() + j);
            //if(*(c->crs) != c->transp)
            *ptr_VM = *(c->crs);
            c->crs++;
        }
    }
    }
}

void (clearCursor)(cursor * c){
       
    int cx ,cy;
    getPosition(c, &cx, &cy);

    if (cx >= 0 && cy >= 0 && cx < get_h_res() && cy < get_v_res())
        for (int j = cy; j < cy + 4; j++)
            for (int i = cx; i < cx + 4; i++){
                if (j > get_v_res())
                    return;
                changePixel(i, j, 0);
            }

}
