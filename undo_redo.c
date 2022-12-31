#include <stdio.h>
#include <limits.h>
#include "tui.h"
#include "undo_redo.h"

bool undo_game(GameState *game_state, struct Stack *undostack, struct Stack *redostack)
{
    Move played_move;
    played_move.column = pop(undostack);
    if (played_move.column == INT_MIN)
    {
        return false;
    }
    else
    {
        change_turn(game_state); // get the previous move's player
        Player *current_player = get_current_player(game_state);
        int move_validity = unplay_move(game_state, &played_move);
        if (move_validity == MOVE_INVALID_COLUMN_FULL || move_validity == MOVE_INVALID_OUT_OF_BOUNDS)
        {
            return false;
        }

        get_elapsed_time(game_state->timer_start, game_state->elapsed_time);
        game_state->total_moves--;
        current_player->number_of_moves--;

        print_game_state(*game_state);
        push(redostack, played_move.column);
        return true;
    }
}

bool redo_game(GameState *game_state, Stack *undostack, struct Stack *redostack)
{
    Move played_move;
    played_move.column = pop(redostack);
    if (played_move.column == INT_MIN)
    {
        return false;
    }
    else
    {
        Player *current_player = get_current_player(game_state);
        int move_validity = play_move(game_state, &played_move);
        if (move_validity == MOVE_INVALID_COLUMN_FULL || move_validity == MOVE_INVALID_OUT_OF_BOUNDS)
        {
            return false;
        }
        change_turn(game_state);
        get_elapsed_time(game_state->timer_start, game_state->elapsed_time);
        game_state->total_moves++;
        current_player->number_of_moves++;

        print_game_state(*game_state);
        push(undostack, played_move.column);
        return true;
    }
}
