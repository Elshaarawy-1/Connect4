#ifndef PLAYER_H
#define PLAYER_H

typedef struct s_player
{
    char *name;
    int id;
    int score;
    int color;
    int number_of_moves;
} Player;

#endif