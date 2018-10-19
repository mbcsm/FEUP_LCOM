#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"

int(timer_set_frequency)(uint8_t timer, uint32_t freq) {
  /* To be completed by the students 
  printf("%s is not yet implemented!\n", __func__);*/
 
  uint8_t byte = TIMER_RB_CMD |
                 TIMER_RB_COUNT_ |
                 TIMER_RB_SEL(timer);

  uint32_t controlWord;
  
  if (sys_outb(TIMER_CTRL, byte) != OK)
    return 1;
  
  if (sys_inb(TIMER_CTRL, &controlWord) != OK)
    return 1;

  controlWord = controlWord & 0x0F;

  uint32_t timer;

  //if (timer == 0)
    timer = TIMER_SEL0 | TIMER_LSB_MSB;

  /*if (timer == 1)
    timer = TIMER_SEL1 | TIMER_LSB_MSB;

  if (timer == 2)
    timer = TIMER_SEL2 | TIMER_LSB_MSB;  */
    
  timer = timer << 4;
  controlWord = timer | controlWord;
  
  if (sys_outb(TIMER_CTRL, controlWord) != OK)
    return 1;

  if (sys_outb(TIMER_0, freq) != OK)
    return 1;

  return 1;
}

int(timer_subscribe_int)(uint8_t *UNUSED(bit_no)) {
  /* To be completed by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

int(timer_unsubscribe_int)() {
  /* To be completed by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

void(timer_int_handler)() {
  /* To be completed by the students */
  printf("%s is not yet implemented!\n", __func__);
}

/* creator: Manuel Monteiro*/
int(timer_get_conf)(uint8_t timer, uint8_t *st) {

  uint8_t byte = TIMER_RB_CMD |
                 TIMER_RB_COUNT_ |
                 TIMER_RB_SEL(timer);

  uint32_t st32Temp;



  if (sys_outb(TIMER_CTRL, byte) != OK) {
    printf("timer config = Error");
    return 1;
  }
  if (sys_inb(TIMER_CTRL, &st32Temp) != OK) {
    printf("timer config = Error");
    return 1;
  }
  
  *st = (uint8_t)st32Temp;
  printf("Timer Get Conf: DONE\n");

  return 0;
}

/* creator: Manuel Monteiro*/
int(timer_display_conf)(uint8_t timer, uint8_t st, enum timer_status_field field) {
  printf("\n\n\n_______TIMER CONFIG_________\n", st);
  printf("Status Byte: %x\n", st);
  printf("Selected Counter: %d\n", timer);

  if(TIMER_LSB_MSB & st)
    printf("Type of Access: LSB followed by MSB\n");
  else if(TIMER_MSB & st)
    printf("Type of Access: MSB\n");
  else if(TIMER_LSB & st)
    printf("Type of Access: LSB\n");
                      
  if(TIMER_SQR_WAVE & st)
    printf("Operating Mode: Mode 3 (square wave generator)\n");
  else if(TIMER_RATE_GEN & st)
    printf("Operating Mode: Mode 2 (rate generator)\n");
  else
    printf("Operating Mode: ERROR 404 MODE NOT FOUND\n");

    if(TIMER_BCD & st)
      printf("Counting Mode: BCD\n");
    else if(TIMER_BIN & st)
      printf("Counting Mode: Binary\n");
    else
      printf("Counting Mode: ERROR 404 MODE NOT FOUND\n");

timer_print_config(timer, field, )

  return 1;
}
