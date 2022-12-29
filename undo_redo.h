#ifndef UNDO_REDO_H
#define UNDO_REDO_H
#include "stdbool.h"
#include "move_result.h"
#include "fstack.h"
#include "configuration.h"
#include "player.h"
#include "game_state.h"


/// @brief Undo last move if valid.
/// @param config Configuration containing board width and height
/// @param board The array representing the last board state. Gets updated with the played_move if the move is valid.
/// @param player Information about the player including player id and score. Gets updated with the new score if the move is valid.

bool undo_game(GameState *game_state, struct Stack *undostack, struct Stack *redostack);

/// @brief Redo last move if valid.
/// @param config Configuration containing board width and height
/// @param board The array representing the last board state. Gets updated with the played_move if the move is valid.
/// @param player Information about the player including player id and score. Gets updated with the new score if the move is valid.

bool redo_game(GameState *game_state, Stack *undostack, struct Stack *redostack);


#endif