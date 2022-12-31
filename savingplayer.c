#include "savingplayer.h"

bool write_leaderboard(winning_player arr[])
{
    FILE *file;
    file = fopen("Leader_board.bin", "wb");
    if (file == NULL) return false;
    fwrite(arr, sizeof(winning_player)*250, 1, file);
    if (fclose(file) == EOF) return false; 
    return true;
}


bool read_leaderboard(winning_player arr[])
{
    FILE *file;
    file = fopen("Leader_board.bin", "rb");
    if (file == NULL) return false;
    while (!feof(file))
    {
        if(fread(arr, sizeof(winning_player) * 250, 1, file) != 1)
            return false;
    }
    fclose(file);
    return true;
}
