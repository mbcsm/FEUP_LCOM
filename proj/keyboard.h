#pragma once

/**
 * @brief Subscribes keyboard interrupts
 * @return bit_no
 * @return Return 0 upon success and non-zero otherwise
 */
int kbd_subscribe_int(uint8_t *bit_no);

/**
 * @brief Unsubscribes keyboard interrupts
 * @return Return 0 upon success and non-zero otherwise
 */
int kbd_unsubscribe_int();

/**
 * @brief Reads the buffer s data using c
 */
void kbd_ih();

/**
 * @brief Reads the buffer s data iusing assembly
 */
void kbd_asm_ih();

/**
 * @brief writes a scan code onto the buffer.
 * @param cmd
 * @return Return 0 upon success and non-zero otherwise
 */
int kbd_write(uint8_t cmd);

/**
 * @brief Gets the scan code read from the keyboard.
 * @return Returns the scan code read from the keyboard
 */
int kbd_read();

int kbd_cmd_reset(uint32_t cmd, uint32_t arg);
