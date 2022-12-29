#include "move_result.h"

int validate_move(Configuration config, int *board, Move *played_move)
{
    if (played_move->column < 0 || played_move->column > config.width - 1)
    {
        return MOVE_INVALID_OUT_OF_BOUNDS;
    }
    else
    {
        for (int i = config.height - 1; i > -1; i--)
        {
            if (board[(i * config.width) + played_move->column] == 0)
            {
                played_move->row = i;
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

int row_score(Configuration config, int *board, int player_id, Move played_move)
{
    int score = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = played_move.column - 3 + i; j <= played_move.column + i; j++)
        {
            if (j < 0 || j > config.width - 1)
            {
                break;
            }
            else if (board[(played_move.row * config.width) + j] != player_id)
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

int column_score(Configuration config, int *board, int player_id, Move played_move)
{
    int score = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = played_move.row - 3 + i; j <= played_move.row + i; j++)
        {
            if (j < 0 || j > config.height - 1)
            {
                break;
            }
            else if (board[(j * config.width) + played_move.column] != player_id)
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

int lower_diagonal_score(Configuration config, int *board, int player_id, Move played_move)
{
    int score = 0;
    for (int i = 0; i < 4; i++)
    {
        int counter = i - 1;
        for (int j = played_move.column - 3 + i; j <= played_move.column + i; j++)
        {
            counter++;
            if (j < 0 || j > config.width - 1)
            {
                break;
            }
            else if (board[(played_move.row + 3 - counter) * config.width + j] != player_id)
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
int upper_diagonal_score(Configuration config, int *board, int player_id, Move played_move)
{
    int score = 0;
    for (int i = 0; i < 4; i++)
    {
        int counter = i - 1;
        for (int j = played_move.column - 3 + i; j <= played_move.column + i; j++)
        {
            counter++;
            if (j < 0 || j > config.width - 1)
            {
                break;
            }
            else if (board[(played_move.row - 3 + counter) * config.width + j] != player_id)
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

int score_calculator(Configuration config, int *board, int player_id, Move played_move)
{
    int score = 0;
    score += row_score(config, board, player_id, played_move);
    score += column_score(config, board, player_id, played_move);
    score += lower_diagonal_score(config, board, player_id, played_move);
    score += upper_diagonal_score(config, board, player_id, played_move);
    return score;
}


int play_move(Configuration config, int *board, Player *player, Move *played_move)
{
    int move_validity;
    move_validity = validate_move(config, board, played_move);
    if (move_validity == MOVE_VALID || move_validity == MOVE_END)
    {
        played_move->total_moves ++;
        board[(played_move->row * config.width) + played_move->column] = player->id;
        int score = score_calculator(config, board, player->id, *played_move);
        player->score += score;
    }
    return move_validity;
}

void unplay_move(Configuration config, int * board, Player *player, Move *played_move)
{
    int move_validity;
    move_validity = validate_move(config, board, played_move);
    played_move->row++; //We have to add 1 because validate move get the first valid row to play in
    played_move->total_moves --;
    int score = score_calculator(config, board, player->id, *played_move);
    board[played_move->row * config.width + played_move->column] = 0;
    player->score -= score;
}

void get_valid_columns(Configuration config, int *board, int valid_columns[], int * size)
{
    int i,j;
    for (i = 0, j = 0; i < config.width && i < *size; i++)
    {
        if (board[i * config.width + 0] == 0)
        {
            valid_columns[j++] = i;
        }
    }
    *size = j;
}