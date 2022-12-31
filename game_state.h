#ifndef GAME_STATE_H
#define GAME_STATE_H
#include "timer.h"
#include "configuration.h"
#include "player.h"

#define GAME_MODE_PVP 0 // player vs player mode
#define GAME_MODE_PVC 1 // player vs computer mode

typedef struct GameState
{
    Configuration *config;
    Player *player1;
    Player *player2;
    int total_moves;
    int current_player_turn;
    int *board;
    time_t timer_start;
    hms_time *elapsed_time;
    int game_mode;
    int file_id;
} GameState;

Player* get_current_player(GameState* game_state);
void change_turn(GameState* game_state);

#endif