#ifndef GAME_H
#define GAME_H
#include <stdio.h>
#include <stdlib.h>
#include "player.h"
#include "tui.h"
#include "move_result.h"



int make_player_move(GameState *game_state)
{
    int column = read_board_input("Select a column to play in : ", game_state->config);

    Move played_move;
    played_move.column = column;
    played_move.total_moves = game_state->total_moves;
    Player *current_player = game_state->current_player_turn == 1 ? game_state->player1 : game_state->player2;
    int move_validity = play_move(*(game_state->config), game_state->board, current_player, &played_move);
    if (move_validity == MOVE_INVALID_COLUMN_FULL)
    {
        printf("\n[ERR] Input is invalid, the column you chose is already full. Please choose another column\n");
        return make_player_move(game_state);
    }

    if (move_validity == MOVE_INVALID_OUT_OF_BOUNDS)
    {
        printf("\n[ERR] Input is invalid, the column you chose is out of bounds. Please choose another column\n");
        return make_player_move(game_state);
    }

    game_state->current_player_turn = game_state->current_player_turn == 1 ? 2 : 1;
    get_elapsed_time(game_state->timer_start,game_state->elapsed_time);
    game_state->total_moves++;
    current_player->number_of_moves++;

    print_game_state(*game_state);

    return move_validity;
}

int make_computer_move(GameState *game_state)
{
    int column = read_board_input("Select a column to play in : ", game_state->config);

    Move played_move;
    played_move.column = column;
    played_move.total_moves = game_state->total_moves;
    Player *current_player = game_state->current_player_turn == 1 ? game_state->player1 : game_state->player2;
    int move_validity = play_move(*(game_state->config), game_state->board, current_player, &played_move);
    if (move_validity == MOVE_INVALID_COLUMN_FULL)
    {
        printf("\n[ERR] Input is invalid, the column you chose is already full. Please choose another column\n");
        return make_computer_move(game_state);
    }

    if (move_validity == MOVE_INVALID_OUT_OF_BOUNDS)
    {
        printf("\n[ERR] Input is invalid, the column you chose is out of bounds. Please choose another column\n");
        return make_computer_move(game_state);
    }

    game_state->current_player_turn = game_state->current_player_turn == 1 ? 2 : 1;
    get_elapsed_time(game_state->timer_start,game_state->elapsed_time);
    game_state->total_moves++;
    current_player->number_of_moves++;

    print_game_state(*game_state);

    return move_validity;
}

#endif