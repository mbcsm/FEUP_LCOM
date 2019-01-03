#pragma once

static char playerNo = '0';

typedef enum {
    PAINT, 
    ROLL,
    WAIT
} PlayerState;

typedef struct {
    char* name = "player" + (++playerNo);
    bool active;
    PlayerState p;
    uint16t color;

} player;
