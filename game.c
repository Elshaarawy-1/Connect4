#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "game.h"
#include "player.h"
#include "tui.h"
#include "move_result.h"
#include "color.h"
#include "undo_redo.h"


void init_game(GameState *game_state)
{
    game_state->player1->id = 1;
    game_state->player1->color = get_random_foregroundcolor_id(-1);
    game_state->player1->number_of_moves = 0;
    game_state->player1->score = 0;

    game_state->player2->id = 2;
    // get a random color other than player1's color
    game_state->player2->color = get_random_foregroundcolor_id(game_state->player1->color);
    game_state->player2->number_of_moves = 0;
    game_state->player2->score = 0;
    game_state->current_player_turn = 1;

    game_state->elapsed_time->hours = 0;
    game_state->elapsed_time->minutes = 0;
    game_state->elapsed_time->seconds = 0;

    game_state->timer_start = start_timer();
}

int make_player_move(GameState *game_state, Stack *undo_stack, Stack *redo_stack)
{
    int input = read_board_input("Select a column to play in or enter -1 to open the in-game menu : ", game_state->config);

    if (input == -1)
    {
        return run_in_game_menu(game_state, undo_stack, redo_stack);
    }

    Move played_move;
    played_move.column = input - 1;
    played_move.total_moves = game_state->total_moves;
    Player *current_player = get_current_player(game_state);
    int move_validity = play_move(game_state, &played_move);
    if (move_validity == MOVE_INVALID_COLUMN_FULL)
    {
        printf("\n[ERR] Input is invalid, the column you chose is already full. Please choose another column\n");
        return make_player_move(game_state, undo_stack, redo_stack);
    }

    if (move_validity == MOVE_INVALID_OUT_OF_BOUNDS)
    {
        printf("\n[ERR] Input is invalid, the column you chose is out of bounds. Please choose another column\n");
        return make_player_move(game_state, undo_stack, redo_stack);
    }

    change_turn(game_state);
    get_elapsed_time(game_state->timer_start, game_state->elapsed_time);
    game_state->total_moves++;
    current_player->number_of_moves++;

    print_game_state(*game_state);
    push(undo_stack, played_move.column);
    return move_validity;
}

int make_computer_move(GameState *game_state, Stack *undo_stack, Stack *redo_stack)
{
    int size = game_state->config->width;
    int valid_columns[size];
    get_valid_columns(*(game_state->config), game_state->board, valid_columns, &size);

    int random_column_index = rand() % (size);
    Move played_move;

    played_move.column = valid_columns[random_column_index];
    played_move.total_moves = game_state->total_moves;
    Player *current_player = get_current_player(game_state);
    int move_validity = play_move(game_state, &played_move);

    change_turn(game_state);
    get_elapsed_time(game_state->timer_start, game_state->elapsed_time);
    game_state->total_moves++;
    current_player->number_of_moves++;

    print_game_state(*game_state);
    push(undo_stack, played_move.column);
    return move_validity;
}

int run_in_game_menu(GameState *game_state, Stack *undo_stack, Stack *redo_stack)
{
    Menu *in_game_menu = malloc(sizeof(*in_game_menu));

    in_game_menu->number_of_options = 4;
    in_game_menu->header = "Select an option : ";
    in_game_menu->options = malloc(sizeof(*in_game_menu->options) * in_game_menu->number_of_options);

    in_game_menu->options[0] = "Undo";
    in_game_menu->options[1] = "Redo";
    in_game_menu->options[2] = "Return to game";
    in_game_menu->options[3] = "Save and exit game";

    int selected_option = read_selected_option(in_game_menu, "The index of the option you want to select (between 1 and 4) : ");

    free(in_game_menu->options);
    free(in_game_menu);

    Player *current_player = game_state->current_player_turn == 1 ? game_state->player1 : game_state->player2;
    switch (selected_option)
    {
    case 1:
    {
        bool can_undo = undo_game(game_state, undo_stack, redo_stack);
        if (!can_undo)
        {
            print_wrn("There are no moves to undo\n");
            return MOVE_NONE;
        }

        if (game_state->game_mode == GAME_MODE_PVC) // if playing against computer, undo 2 moves
        {
            undo_game(game_state, undo_stack, redo_stack);
        }

        return MOVE_UNDO;
    }
    case 2:
    {
        bool can_redo = redo_game(game_state, undo_stack, redo_stack);
        if (!can_redo)
        {
            print_wrn("There are no moves to redo\n");
            return MOVE_NONE;
        }
        // if (game_state->game_mode == GAME_MODE_PVC) // if playing against computer, have the computer make a new move
        // {
        //     make_computer_move(game_state, undo_stack, redo_stack);
        // }

        return MOVE_REDO;
    }
    case 4:
        return MOVE_EXIT;
    default:
        return MOVE_NONE;
    }
}