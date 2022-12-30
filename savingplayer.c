#include "savingplayer.h"

bool write_data(winning_player player)
{
    FILE *file;
    file = fopen("Leader_board.bin", "ab");
    if (file == NULL) return false;
    fwrite(&player, sizeof(winning_player), 1, file);
    if (fclose(file) == EOF) return false; 
    return true;
}

bool read_data(winning_player arr[])
{
    FILE *file;
    file = fopen("Leader_board.bin", "rb");
    if (file == NULL) return false;
    while (!feof(file))
    {
        if(fread(arr, sizeof(winning_player), 1, file) != 1)
            return false;
    }
    fclose(file);
    return true;
}