#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"

int(timer_set_frequency)(uint8_t timer, uint32_t freq) {
  /* To be completed by the students 
  printf("%s is not yet implemented!\n", __func__);*/
 
  uint8_t byte = TIMER_RB_CMD | TIMER_RB_COUNT_ | TIMER_RB_SEL(timer);

  uint32_t controlWord;
  
  if (sys_outb(TIMER_CTRL, byte) != OK)
    return 1;
  
  if (sys_inb(TIMER_0, &controlWord) != OK)
    return 1;

  controlWord = controlWord & 0x3F; // 

  if (timer == 0)
    controlWord = TIMER_SEL0 | TIMER_LSB_MSB ;

  else if (timer == 1)
    controlWord = TIMER_SEL1 | TIMER_LSB_MSB;

  else if (timer == 2)
    controlWord = TIMER_SEL2 | TIMER_LSB_MSB;
    
  
  if (sys_outb(TIMER_CTRL, controlWord) != OK)
    return 1;

  if (sys_outl(TIMER_0, freq) != OK)
    return 1;

  return 0;
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


int(timer_get_conf)(uint8_t timer, uint8_t *st) {

  uint8_t byte = TIMER_RB_CMD | TIMER_RB_COUNT_ | TIMER_RB_SEL(timer); 
  uint32_t st32Temp = 0;

  if (sys_outb(TIMER_CTRL, byte) != OK) {
    printf("timer config = Error");
    return 1;
  }

if (timer == 0)
  if (sys_inb(TIMER_0, &st32Temp) != OK) {
      printf("timer config = Error");
      return 1;}
else {if (timer == 1)
  if (sys_inb(TIMER_1, &st32Temp) != OK) {
    printf("timer config = Error");
    return 1;
  }}
else {if (timer == 2)
  if (sys_inb(TIMER_2, &st32Temp) != OK) {
    printf("timer config = Error");
    return 1;
  }}

  *st = (uint8_t)st32Temp;
  printf("Timer Get Conf: DONE\n");

  return 0;

}

int(timer_display_conf)(uint8_t timer, uint8_t st, enum timer_status_field field) {
  union timer_status_field_val val;

  if (field == all)  // FIELD == ALL
    val.byte = st;

  else if (field == initial)   // FIELD == INIT
  {
    if(TIMER_LSB_MSB & st)
      val.in_mode = MSB_after_LSB;
    else if(TIMER_MSB & st)
    val.in_mode = MSB_only;
    else if(TIMER_LSB & st)
     val.in_mode = LSB_only;
   else val.in_mode = INVAL_val;
  }
  /*else if (field == mode)  // FIELD == MODE
    val.count_mode =*/
  else if (field == base)    // FIELD == BASE
  {
    if(TIMER_BCD & st)
      val.bcd = true;
    else if(TIMER_BIN & st)
      val.bcd = false;
  }

  timer_print_config(timer, field, val);

  return 1;
}
