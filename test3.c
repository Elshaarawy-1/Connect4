#include <stdio.h>
#include "configuration.h"
#include "player.h"
#include "move_result.h"
#include "fstack.h"
#include "undo_redo.h"
// #include "stack2.h"

void SetGame(int row, int col, int board[][col])
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            board[i][j] = 0;
        }
    }   
}

void print_game(int row, int col, int board[][col])
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }  
}

int main(){
    Configuration config;
    Player player;
    player.id = 1;
    player.score = 0;
    Move played_move;
    config.height = 10, config.width = 10;
    int board[config.height][config.width];
    SetGame(config.height, config.width, board);
    int game_validity = 100;
    struct Stack* undostack = createStack(100);
    struct Stack* redostack = createStack(100);
    while (game_validity != MOVE_END)
    {
        printf("Score: %d\n", player.score);
        print_game(10, 10, board);
        scanf("%d", &(played_move.column));
        if (played_move.column == -1)
        {
            undo_game(undostack, redostack, config, board, &player, &played_move);
        }
        else if (played_move.column == -2)
        {
            redo_game(undostack, redostack, config, board, &player, &played_move);
        }
        else
        {            
            game_validity = play_move(config, board, &player, &played_move);
            push(undostack, played_move.column);
            if (game_validity == MOVE_INVALID_COLUMN_FULL)
            {
                printf("Play in the right column\n");
            }
        }
    }
    
    return 0;
}