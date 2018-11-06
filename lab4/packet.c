#include <lcom/lcf.h>
#include "packet.h"
#include "i8042.h"

void (resetPacket)(struct packet *pp){
    pp->bytes[0] = 0x00;
    pp->bytes[1] = 0x00;
    pp->bytes[2] = 0x00;    
}

void (parseToPacket)(int byte, uint32_t data, struct packet *pp){
    if (byte == 1){
        pp->bytes[0] = data;
        pp->lb = (data & LB);
        pp->rb = (data & RB);
        pp->mb = (data & MB);
        pp->x_ov = (data & X_OVF);
        pp->y_ov = (data & Y_OVF);

    }
    else if (byte == 2){
        pp->bytes[1] = data;
    }
    else if (byte == 0)
        pp->bytes[2] = data;
}

