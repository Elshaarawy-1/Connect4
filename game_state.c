#include "game_state.h"

Player* get_current_player(GameState* game_state){
    return game_state->current_player_turn == 1 ? game_state->player1 : game_state->player2;
}

void change_turn(GameState* game_state){
    game_state->current_player_turn = game_state->current_player_turn == 1 ? 2 : 1;
}