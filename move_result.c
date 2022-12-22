#include "move_result.h"

int validate_move(Configuration config, int board[][config.width], Move *played_move)
{
    if (played_move->column < 0 || played_move->column > config.width-1)
    {
        return MOVE_INVALID_OUT_OF_BOUNDS;
    }
    else
    {
        for (int i = config.height -1; i > -1 ; i--)
        {
            if (board[i][played_move->column] == 0)
            {
                played_move->row = i;
                played_move->total_moves ++;
                if (played_move->total_moves == (config.height * config.width))
                {
                    return MOVE_END;
                }
                else
                {
                    return MOVE_VALID;
                }
            }    
        }
        return MOVE_INVALID_COLUMN_FULL;
    }    
}

int row_score(Configuration config, int board[][config.width], int player_id, Move played_move)
{
    int score = 0;
    for (int i = 0; i < 4 ; i++)
    {
        for (int j = played_move.column -3 + i; j <= played_move.column + i; j++)
        {
            if (j < 0 || j > config.width-1)
            {
                break;
            }
            else if (board[played_move.row][j] != player_id)
            {
                break;
            }
            else if (j == played_move.column + i)
            {
                score++;
            }
        }
    }
    return score;
}

int column_score(Configuration config, int board[][config.width], int player_id, Move played_move)
{
    int score = 0;
    for (int i = 0; i < 4 ; i++)
    {
        for (int j = played_move.row -3 + i; j <= played_move.row + i; j++)
        {
            if (j < 0 || j > config.height-1)
            {
                break;
            }
            else if (board[j][played_move.column] != player_id)
            {
                break;
            }
            else if (j == played_move.row + i)
            {
                score++;
            }
        }
    }
    return score;
}

int score_calculator(Configuration config, int board[][config.width], int player_id, Move played_move)
{
    int score = 0;
    score += row_score(config, board, player_id, played_move);
    score += column_score(config, board, player_id, played_move);

    return score;
}


int play_move(Configuration config, int board[][config.width], Player *player, Move *played_move)
{
    int move_validity;
    move_validity = validate_move(config, board, played_move);
    if (move_validity == MOVE_VALID || move_validity == MOVE_END)
    {
        board[played_move->row][played_move->column] = player->id;
        int score = score_calculator(config, board, player->id, *played_move);
        player->score += score;
    }
    return move_validity;
}