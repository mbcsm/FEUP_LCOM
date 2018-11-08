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
    //sys_inb(OUT_BUF, &mouseData);
    uint32_t stat = 0;
	uint32_t data = 0;
while (1){
	sys_inb(STAT_REG, &stat); /* assuming it returns OK */
		/* loop while 8042 output buffer is empty */
	if( stat & OBF && stat & AUX) {
		sys_inb(OUT_BUF, &data); /* assuming it returns OK */
		if ((stat & (PAR_ERR | TO_ERR)) == 0 ){
			mouseData = data;
        }
		else
			mouseData = 0;
    return;
	}
    tickdelay(micros_to_ticks(WAIT_KBC));
}
}

uint32_t (read_kbc)(){
	int i = 0;
	uint32_t data;
	uint32_t stat;

	while (i < 8) {
		if (sys_inb(STAT_REG, &stat) != OK)
			return -1;

		if (stat & OBF) {
			sys_inb(OUT_BUF, &data);

			if ((stat & (PAR_ERR | TO_ERR)) == 0)
				return data;
			else
				return -1;
		}
		tickdelay(micros_to_ticks(WAIT_KBC));
		i++;
	}
	return -1;

}

int (write_kbc_command)(uint32_t command){
	uint32_t stat = 0;
    while( 1 ) {
        sys_inb(STAT_REG, &stat); /* assuming it returns OK */
        /* loop while 8042 input buffer is not empty */
	    //uint32_t cmd = stat | INT;
        if( (stat & IBF) == 0 ) {
            sys_outb(KBC_CMD_REG, command); /* no args command */
			printf("d4 to kbc_reg\n");
            return 0;
        }	
        tickdelay(micros_to_ticks(WAIT_KBC));
    }
	return -1;
}

int (write_kbc_argument)(uint32_t argument){
	uint32_t stat = 0;
    while( 1 ) {
        sys_inb(STAT_REG, &stat); /* assuming it returns OK */
        /* loop while 8042 input buffer is not empty */
	    //uint32_t cmd = stat | INT;
        if( (stat & IBF) == 0 ) {
            sys_outb(IN_BUF, argument); /* no args command */
			printf("arg sent\n");
            return 0;
        }	
        tickdelay(micros_to_ticks(WAIT_KBC));
    }
	return -1;
}

int (write_kbc_cmd_byte)(uint8_t cmd_byte){
	if (write_kbc_command(KBC_WRITE_CMD) != 0)
		return -1;
	if (write_kbc_argument(cmd_byte) != 0)
		return -1;

	return 0;
}

int (write_mouse_command)(uint32_t command){
	if (write_kbc_command(MOUSE_WRITE_CMD) != 0)
		return -1;
	if (write_kbc_argument(command) != 0)
		return -1;

	return 0;
}

int (enable_data_report)(){
	uint8_t response;
	do {
		write_mouse_command(EN_DATA_REPORT);
		response = read_kbc();

		if (response == ERROR)
			return -1;
	}
	while (response != ACK);

	return 0;
}

int (disable_data_report)(){
	uint8_t response;
	do {
		write_mouse_command(DIS_DATA_REPORT);
		response = read_kbc();

		if (response == ERROR)
			return -1;
	}
	while (response != ACK);

	return 0;
}

int (set_stream_mode)(){
	uint8_t response;
	do {
		write_mouse_command(DIS_DATA_REPORT);
		response = read_kbc();

		if (response == ERROR)
			return -1;
	}
	while (response != ACK);

	return 0;
}

int (read_data)(){
	uint8_t response;
	do {
		write_mouse_command(READ_DATA);
		response = read_kbc();

		if (response == ERROR)
			return -1;
	}
	while (response != ACK);

	return 0;
}
