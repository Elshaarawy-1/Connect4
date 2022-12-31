#include "move_result.h"

int validate_move(GameState *game_state, Move *played_move)
{
    if (played_move->column < 0 || played_move->column > game_state->config->width - 1)
    {
        return MOVE_INVALID_OUT_OF_BOUNDS;
    }
    else
    {
        for (int i = game_state->config->height - 1; i > -1; i--)
        {
            if (game_state->board[(i * game_state->config->width) + played_move->column] == 0)
            {
                played_move->row = i;
                if (game_state->total_moves + 1 >= (game_state->config->height * game_state->config->width))
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

int row_score(GameState *game_state, int player_id, Move played_move)
{
    int score = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = played_move.column - 3 + i; j <= played_move.column + i; j++)
        {
            if (j < 0 || j > game_state->config->width - 1)
            {
                break;
            }
            else if (game_state->board[(played_move.row * game_state->config->width) + j] != player_id)
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

int column_score(GameState *game_state, int player_id, Move played_move)
{
    int score = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = played_move.row - 3 + i; j <= played_move.row + i; j++)
        {
            if (j < 0 || j > game_state->config->height - 1)
            {
                break;
            }
            else if (game_state->board[(j * game_state->config->width) + played_move.column] != player_id)
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

int lower_diagonal_score(GameState *game_state, int player_id, Move played_move)
{
    int score = 0;
    for (int i = 0; i < 4; i++)
    {
        int counter = i - 1;
        for (int j = played_move.column - 3 + i; j <= played_move.column + i; j++)
        {
            counter++;
            if (j < 0 || j > game_state->config->width - 1)
            {
                break;
            }
            else if (game_state->board[(played_move.row + 3 - counter) * game_state->config->width + j] != player_id)
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
int upper_diagonal_score(GameState *game_state, int player_id, Move played_move)
{
    int score = 0;
    for (int i = 0; i < 4; i++)
    {
        int counter = i - 1;
        for (int j = played_move.column - 3 + i; j <= played_move.column + i; j++)
        {
            counter++;
            if (j < 0 || j > game_state->config->width - 1)
            {
                break;
            }
            else if (game_state->board[(played_move.row - 3 + counter) * game_state->config->width + j] != player_id)
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

int score_calculator(GameState *game_state, int player_id, Move played_move)
{
    int score = 0;
    score += row_score(game_state, player_id, played_move);
    score += column_score(game_state, player_id, played_move);
    score += lower_diagonal_score(game_state, player_id, played_move);
    score += upper_diagonal_score(game_state, player_id, played_move);
    return score;
}

int play_move(GameState *game_state, Move *played_move)
{
    int move_validity;
    move_validity = validate_move(game_state, played_move);
    if (move_validity == MOVE_VALID || move_validity == MOVE_END)
    {
        if (played_move->column > game_state->config->width || played_move->row > game_state->config->height)
        {
            return MOVE_INVALID_OUT_OF_BOUNDS;
        }

        played_move->total_moves++;
        Player *current_player = get_current_player(game_state);
        game_state->board[(played_move->row * game_state->config->width) + played_move->column] = current_player->id;
        int score = score_calculator(game_state, current_player->id, *played_move);
        current_player->score += score;
    }
    return move_validity;
}

int unplay_move(GameState *game_state, Move *played_move)
{
    int move_validity;
    move_validity = validate_move(game_state, played_move);
    if (played_move->column > game_state->config->width || played_move->row > game_state->config->height)
    {
        return MOVE_INVALID_OUT_OF_BOUNDS;
    }
    Player *current_player = get_current_player(game_state);
    played_move->row++; // We have to add 1 because validate move get the first valid row to play in
    played_move->total_moves--;
    int score = score_calculator(game_state, current_player->id, *played_move);
    game_state->board[played_move->row * game_state->config->width + played_move->column] = 0;
    current_player->score -= score;
    return move_validity;
}

void get_valid_columns(Configuration config, int *board, int valid_columns[], int *size)
{
    int i, j;
    for (i = 0, j = 0; i < config.width && i < *size; i++)
    {
        if (board[i] == 0)
        {
            valid_columns[j++] = i;
        }
    }
    *size = j;
}