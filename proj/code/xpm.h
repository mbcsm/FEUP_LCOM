
/** @defgroup xpm xpm
 * @{
 *
 * utils for xpm
 */

#ifndef XPM_H
#define XPM_H

//#pragma once
#include "video.h"

/**
 * @brief draws xpm to a postion on the screen
 * @param x the x position of the pixel on the screen
 * @param y the y position of the pixel on the screen
 * @param sprite pointer to the sprite to be drawn
 * @param img image to be drawn
 * @param transp value of the transparent color
 */
void draw_xpm(int x, int y, uint16_t *sprite, xpm_image_t img, const uint16_t transp);

/**
 * @brief returns the value of the transparent color
 * @return transp value of the transparent color
 */
uint16_t getTransparency();

/**
 * @brief aligns an image by the center horizontally 
 * @param img image to be align
 * @return updated position
 */
int align_x_center(xpm_image_t img);

#endif
/**@}*/
