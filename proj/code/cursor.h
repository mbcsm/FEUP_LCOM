/** @defgroup cursor cursor
 * @{
 *
 * utils for cursor
 */
#ifndef CURSOR_H
#define CURSOR_H

#include "xpm.h"
#include "video.h"
#include "pixmap/cursor_pixmap.h"

/**
 * @brief Initializes the cursors image
*/
int startCursor();

/**
 * @brief returns the current position of the cursor
 * @param x pointer of the x position
 * @param y pointer of the y position
*/
void getPosition(int *x, int *y);

/**
 * @brief updates the position and image of the cursor
 * @param pp pointer of mouse packet
 * @param x pointer of the x position
 * @param y pointer of the y position
*/
void updatePosition(struct packet *pp, int *x, int *y);

/**
 * @brief Removes the cursor image from the screen
*/
void clearMouse();

/**
 * @brief Saves the pixel information bellow the cusrsor
*/
void underMouse();


#endif
/**@}*/

