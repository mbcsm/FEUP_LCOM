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
        if( (stat & IBF) == 0 ) {
            sys_outb(KBC_CMD_REG, cmd); /* no args command */
            return 0;
        }
        delay(WAIT_KBC);
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
			if ( (stat &(PAR_ERR | TO_ERR)) == 0 )
				return data;
			else
				return -1;
		}
		delay(WAIT_KBC);
	}
}


int(timer_get_conf)(uint8_t timer, uint8_t *st) {

	uint8_t byte = TIMER_RB_CMD | TIMER_RB_COUNT_ | TIMER_RB_SEL(timer);
	uint32_t st32Temp = 0;

	if (sys_outb(TIMER_CTRL, byte) != OK) {
		//printf("timer config = Error");
		return 1;
	}

	switch (timer){
	case 0:
	if (sys_inb(TIMER_0, &st32Temp) != OK) {
		//printf("timer config = Error");
		return 1;
		}
	break;
	case 1:
	if (sys_inb(TIMER_1, &st32Temp) != OK) {
			//printf("timer config = Error");
			return 1;
		}
	break;
	case 2:
	if (sys_inb(TIMER_2, &st32Temp) != OK) {
			//printf("timer config = Error");
			return 1;
		}
	break;
	default:
	return 1;
	}

  *st = (uint8_t) st32Temp;
  //printf("Timer Get Conf: DONE\n");

  return 0;
}
