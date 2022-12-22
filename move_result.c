#include "move_result.h"


int validate_move(Configuration config, int board[config.height][config.width], Move *played_move)
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

int score_calculator(Configuration config, int board[config.height][config.width], int player_id, Move played_move)
{
    /// TODO   
}








int main(void)
{

}