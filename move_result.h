#ifndef MOVE_RESULT_H
#define MOVE_RESULT_H
#include "configuration.h"
#include "player.h"

#define MOVE_VALID 0                 // The move is a valid move
#define MOVE_END 1                   // The move is the ending move
#define MOVE_INVALID_COLUMN_FULL 2   // The move is invalid because the specified column is invalid
#define MOVE_INVALID_OUT_OF_BOUNDS 3 // The move is invalid because the specifed column is out of bounds

typedef struct s_move
{
    int row;
    int column;
    int total_moves;
} Move;

/// @brief validates the move played by checking if it is within the board boundries and if the column is full.
/// If the move is valid, change the played_move.row to the lowest valid row for the token
/// @param config configuration containing board width and height
/// @param board the array representing the last board state.
/// @param played_move the move played where played_move.col is the column at which the move is played.
/// If the move is valid the played_move.row is the lowest valid row for the token
/// @return MOVE_VALID, MOVE_END, MOVE_INVALID_COLUMN_FULL, MOVE_INVALID_OUT_OF_BOUNDS
int validate_move(Configuration config, int *board, Move *played_move);

/// @brief Calculate the score that the played_move generates.
/// @param config Configuration containing board width and height.
/// @param board The array representing the board state containing the player_move.
/// @param played_move The move played to calculate score for. The move isn't checked for validity.
/// @param player_id The id of the player who played the move.
/// @return The total score in which that move lead to it.
int score_calculator(Configuration config, int *board, int player_id, Move played_move);

/// @brief Check the move if it is valid, play it and update the player score
/// @param config Configuration containing board width and height
/// @param board The array representing the last board state. Gets updated with the played_move if the move is valid.
/// @param player Information about the player including player id and score. Gets updated with the new score if the move is valid.
/// @param played_move the move played where played_move.column is the column at which the move is played.
/// Gets updated with the move row if the move is valid.
/// @return MOVE_VALID, MOVE_ENDING,MOVE_INVALID_COLUMN_FULL, MOVE_INVALID_OUT_OF_BOUNDS
int play_move(Configuration config, int *board, Player *player, Move *played_move);

void unplay_move(Configuration config, int *board, Player *player, Move *played_move);

int row_score(Configuration config, int *board, int player_id, Move played_move);

int column_score(Configuration config, int *board, int player_id, Move played_move);

int lower_diagonal_score(Configuration config, int *board, int player_id, Move played_move);

int upper_diagonal_score(Configuration config, int *board, int player_id, Move played_move);

void get_valid_columns(Configuration config, int *board, int valid_columns[], int * size);
#endif