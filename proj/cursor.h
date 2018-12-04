#pragma once 
#include "bitmap.h"

typedef struct{

    int x;
    int y;

    Bitmap * crs;
        
} cursor;

cursor * newCursor();

void getPosition(cursor *c, int *y, int *x);

void updatePosition(struct packet *pp, cursor *c);

void drawCursor(cursor *c);

