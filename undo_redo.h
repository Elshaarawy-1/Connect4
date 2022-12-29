#ifndef UNDO_REDO_H
#define UNDO_REDO_H
#include "move_result.h"
#include "fstack.h"
#include "configuration.h"
#include "player.h"


/// @brief Undo last move if valid.
/// @param config Configuration containing board width and height
/// @param board The array representing the last board state. Gets updated with the played_move if the move is valid.
/// @param player Information about the player including player id and score. Gets updated with the new score if the move is valid.
void undo_game(struct Stack* undostack, struct Stack* redostack, Configuration config, int * board, Player *player);

/// @brief Redo last move if valid.
/// @param config Configuration containing board width and height
/// @param board The array representing the last board state. Gets updated with the played_move if the move is valid.
/// @param player Information about the player including player id and score. Gets updated with the new score if the move is valid.
void redo_game(struct Stack* undostack, struct Stack* redostack, Configuration config, int * board, Player *player);


#endif