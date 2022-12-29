#ifndef GAME_H
#define GAME_H
#include "configuration.h"
#include "game_state.h"



int make_player_move(GameState *game_state);

int make_computer_move(GameState *game_state);

#endif