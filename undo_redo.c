#include "undo_redo.h"

void undo_game(struct Stack* undostack, struct Stack* redostack, Configuration config, int board[][config.width], Player *player, Move *played_move)
{
    played_move->column = pop(undostack);
    if (played_move->column == INT_MIN)
    {
        printf("You cannot undo.\n");
    }
    else
    {
    unplay_move(config, board, player, played_move);
    push(redostack, played_move->column);
    }
}

void redo_game(struct Stack* undostack, struct Stack* redostack, Configuration config, int board[][config.width], Player *player, Move *played_move)
{
    played_move->column = pop(redostack);
    if (played_move->column == INT_MIN)
    {
        printf("You cannot redo.\n");
    }
    else
    {
        play_move(config, board, player, played_move);
        push(undostack, played_move->column);
    }
}


