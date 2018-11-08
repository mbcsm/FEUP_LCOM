#pragma once


int mouse_subscribe_int(uint8_t *bit_no);

int mouse_unsubscribe_int();

//void mouse_ih();

uint32_t read_kbc();

int write_kbc_command(uint32_t command);

int write_kbc_argument(uint32_t argument);

int write_kbc_cmd_byte(uint8_t cmd_byte);

int write_mouse_command(uint32_t command);

int enable_data_report();

int disable_data_report();

int set_stream_mode();

int read_data();

