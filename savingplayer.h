#ifndef SAVING_PLAYER_H
#define SAVING_PLAYER_H
#include <stdio.h>
#include <stdbool.h>
#include "player_highscore.h"
bool write_leaderboard(winning_player arr[]);
bool read_leaderboard(winning_player arr[]);


#endif