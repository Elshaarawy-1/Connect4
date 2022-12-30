#include "save_load.h"


bool write_data(char *filename, GameState *game)
{
    FILE *file;
    file = fopen(filename, "wb");
    if (file == NULL) return false;
    fwrite(game->config, sizeof(int) * 3, 1, file);
    fwrite(game->player1, sizeof(int) * 4, 1, file);
    fwrite(game->player2, sizeof(int) * 4, 1, file);
    fwrite(&(game->total_moves), sizeof(int), 1, file);
    fwrite(&(game->current_player_turn), sizeof(int), 1, file);
    fwrite(game->board, sizeof(int) * game->config->height * game->config->width, 1, file);
    fwrite(&(game->timer_start), sizeof(time_t), 1, file);
    fwrite(game->elapsed_time, sizeof(int) * 3, 1, file);
    fwrite(&(game->game_mode), sizeof(int), 1, file);
    if (fclose(file) == EOF) return false; 
    return true;
}


bool read_data(char *filename, GameState *game)
{
    FILE *file;
    file = fopen(filename, "rb");
    if (file == NULL) return false;
    if(fread(game->config, sizeof(int) * 3, 1, file) != 1)
        return false;
    if(fread(game->player1, sizeof(int) * 4, 1, file) != 1)
        return false;
    if(fread(game->player2, sizeof(int) * 4, 1, file) != 1)
        return false;
    if(fread(&(game->total_moves), sizeof(int), 1, file) != 1)
        return false;
    if(fread(&(game->current_player_turn), sizeof(int), 1, file) != 1)
        return false;
    if(fread(game->board, sizeof(int) * game->config->height * game->config->width, 1, file) != 1)
        return false;
    if(fread(&(game->timer_start), sizeof(time_t), 1, file) != 1)
        return false;
    if(fread(game->elapsed_time, sizeof(int) * 3, 1, file) != 1)
        return false;
    if(fread(&(game->game_mode), sizeof(int), 1, file) != 1)
        return false;
    fclose(file);
    return true;
}