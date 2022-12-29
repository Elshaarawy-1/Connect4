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
/// @param played_move the move played where played_move.column is the column at which the move is played. 
/// Gets updated with the move row if the move is valid.
/// @return UNAVAILABLE_OPERATION.
void undo_game(struct Stack* undostack, struct Stack* redostack, Configuration config, int board[][config.width], Player *player, Move *played_move);

/// @brief Redo last move if valid.
/// @param config Configuration containing board width and height
/// @param board The array representing the last board state. Gets updated with the played_move if the move is valid.
/// @param player Information about the player including player id and score. Gets updated with the new score if the move is valid.
/// @param played_move the move played where played_move.column is the column at which the move is played. 
/// Gets updated with the move row if the move is valid.
/// @return UNAVAILABLE_OPERATION
void redo_game(struct Stack* undostack, struct Stack* redostack, Configuration config, int board[][config.width], Player *player, Move *played_move);


#endif