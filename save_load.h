#ifndef SAVE_LOAD_H
#define SAVE_LOAD_H
#include "game_state.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


bool write_data(char *filename, GameState *data);

bool read_data(char *filename, GameState *game);

#endif