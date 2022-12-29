#ifndef GAME_STATE_H
#define GAME_STATE_H
#include "timer.h"
#include "configuration.h"
#include "player.h"

typedef struct GameState
{
    Configuration *config;
    Player* player1;
    Player *player2;
    int total_moves;
    int current_player_turn;
    int * board;
    time_t timer_start;
    hms_time* elapsed_time;

} GameState;



#endif