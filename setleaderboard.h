#ifndef SET_LEADERBOARD_H
#define SET_LEADERBOARD_H
#include <stdbool.h>
#include "PlayerHighScore.h"
#include "savingplayer.h"
void bubbleSort(winning_player leader_board[]);

int add_player_score(winning_player leader_board[], winning_player player);

int get_winner_rank(winning_player leader_board[], winning_player player);


#endif