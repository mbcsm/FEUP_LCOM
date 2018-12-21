#pragma once 


typedef struct{

    int x;
    int y;

    xpm_image_t img;
    uint16_t *sprite; //= (uint16_t*)xpm_load(cursor_xpm_xpm, XPM_5_6_5, &img);

    uint16_t  transp; //= xpm_transparency_color(XPM_5_6_5);
    
    char *noCrsBUF[50*50]; // Colors under the cursor
    int horizontalRes;
    int verticalRes;
        
} cursor;

cursor * newCursor();

void getPosition(cursor *c, int *y, int *x);

void updatePosition(struct packet *pp, int *x, int *y);

void drawCursor(cursor *c);

void clearCursor(cursor *c);

