#pragma once

int kbd_subscribe_int(uint8_t *bit_no);

int kbd_unsubscribe_int();

void kbd_ih();

void kbd_asm_ih();

int kbd_write();

int kbd_read();
