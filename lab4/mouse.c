#include <lcom/lcf.h>
#include "mouse.h"

#include <stdint.h>

#include "i8254.h"
#include "i8042.h"

int hookid = 2;

int (mouse_subscribe_int)(uint8_t *bit_no){

    *bit_no = hookid;
	if (sys_irqsetpolicy(MOUSE_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &hookid) != OK)
		return 1;  
    
    return 0;  
}

int(mouse_unsubscribe_int)(){
    if (sys_irqrmpolicy(&hookid) != OK) {
        return -1;
    }
    return 0;
}

uint32_t mouseData;
void (mouse_ih)(){
    sys_inb(OUT_BUF, &mouseData);
}

