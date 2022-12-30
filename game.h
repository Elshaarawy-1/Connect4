#ifndef GAME_H
#define GAME_H
#include <stdbool.h>
#include "game_state.h"
#include "fstack.h"

void init_game(GameState *game_state);

int make_player_move(GameState *game_state, Stack *undo_stack, Stack *redo_stack);

int make_computer_move(GameState *game_state, Stack *undo_stack, Stack *redo_stack);

int run_in_game_menu(GameState *game_state, Stack *undo_stack, Stack *redo_stack);

#endif