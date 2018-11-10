#pragma once


int mouse_subscribe_int(uint8_t *bit_no);

int mouse_unsubscribe_int();

//void mouse_ih();

uint32_t read_kbc();

int write_kbc_command(uint8_t command);

int write_kbc_argument(uint8_t argument);

int write_kbc_cmd_byte(uint32_t cmd_byte);

int write_mouse_command(uint32_t command);

int mouse_enable_interrupts();

int mouse_dis_int();

int mouse_en_int();

int mouse_disable_interrupts();

int enable_data_report();

int disable_data_report();

int set_stream_mode();

int set_remote_mode();

int read_mouse_data(uint32_t *packet);

enum state {
    INIT,
	IDRAWU,
    DRAWINGUP,
	VERTEX,
	IDRAWD,
	DRAWINGDOWN,
    FINAL
};

enum event_type {
	LBDOWN,
	LBUP,
	MOVEUP,
	RESIDUAL,
	RBDOWN,
	RBUP,
	MOVEDOWN,
	OTHER
};

void updateState(enum event_type evt);

bool event(struct packet *pp, uint8_t x_len);

