#pragma once 


typedef struct{

    int x;
    int y;

    xpm_image_t img;
    uint16_t *crs;
    uint16_t  transp;
    
    char *noCrsBUF[50*50]; // Colors under the cursor
    int horizontalRes;
    int verticalRes;
        
} cursor;

cursor * newCursor();

void getPosition(cursor *c, int *y, int *x);

void updatePosition(struct packet *pp, cursor *c);

void drawCursor(cursor *c);

void clearCursor(cursor *c);

