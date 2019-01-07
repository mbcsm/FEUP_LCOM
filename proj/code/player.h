/** @defgroup player player
 * @{
 *
 * utils for player
 */
#ifndef PLAYER_H
#define PLAYER_H

typedef struct {
/*    char* name = "player" + (++playerNo);
    bool active;
    PlayerState p;
    uint16t color;
*/

    int level;
    int score;

    

} Player;

/**
 * @brief Initializes player
 */
void startPlayer();

#endif
/**@}*/
