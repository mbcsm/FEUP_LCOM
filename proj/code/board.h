#pragma once
/** @defgroup board board
 * @{
 *
 * utils for board
 */
int boardArr[12][12];

/**
 * @brief Initializes the board's array
*/
void startBoard();

/**
 * @brief Updates the board's array
 * @param seed helps with getting a random number
*/
void updateBoard(int seed);

/**
 * @brief Prints current board onto the terminal
*/
void printBoard();

/**
 * @brief Checks if a cell is empty
 * @param x the x position of the cell
 * @param y the y position of the cell
*/
bool emptyCell(int x, int y);

/**
 * @brief paints a board cell
 * @param x the x position of the cell
 * @param y the y position of the cell
 * @param color the color of the cell in hex
*/
void paintBoardCell(int x, int y, uint16_t color);

/**
 * @brief clears a board cell with a new color
 * @param x the x position of the cell
 * @param y the y position of the cell
 * @param color the old color of the cell in hex
 * @param oldColor the new color of the cell in hex
*/
void clearBoardCell(int x, int y, uint16_t oldColor, uint16_t color);

/**
 * @brief paints board with the alive blocks
*/
void paintBoard();

/**@}*/
