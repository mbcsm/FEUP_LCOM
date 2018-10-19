#include <lcom/lcf.h>
#include <lcom/timer.h>
#include "keyboard.h"

#include <stdint.h>

#include "i8254.h"
#include "i8042.h"

int(kbd_write)() {
	uint32_t stat = 0;
    while( 1 ) {
        sys_inb(STAT_REG, &stat); /* assuming it returns OK */
        /* loop while 8042 input buffer is not empty */
	    uint32_t cmd = stat | INT;
        if( (stat & IBF) == 0 ) {
            sys_outb(KBC_CMD_REG, cmd); /* no args command */
            return 0;
        }	
        tickdelay(micros_to_ticks(WAIT_KBC));
    }
}

int(kbd_read)() {
	uint32_t stat = 0;
	uint32_t data = 0;

    while( 1 ) {
		sys_inb(STAT_REG, &stat); /* assuming it returns OK */
		/* loop while 8042 output buffer is empty */
		if( stat & OBF ) {
			sys_inb(OUT_BUF, &data); /* assuming it returns OK */
			if ( (stat &(PAR_ERR | TO_ERR)) == 0 ){
				return data;
            }
			else
				return -1;
		}
        tickdelay(micros_to_ticks(WAIT_KBC));
	}
}

