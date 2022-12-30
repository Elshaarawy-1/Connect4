#include "setleaderboard.h"




void bubbleSort(winning_player leader_board[])
{
    for (int i = 0; i < 250; i++) // 250 is the maximum player winning 
    {
        bool is_sorted = true;
        for (int j = 249; j > 0; j--) 
        {
            if (leader_board[j].score > leader_board[j-1].score) 
            {
                winning_player temp;
                temp = leader_board[j];
                leader_board[j] = leader_board[j-1];
                leader_board[j-1] = temp;
                is_sorted = false;
            }
        }
        if (is_sorted) return;
    }
}


int add_player_score(winning_player leader_board[], winning_player player)
{
    int i;
    for (i = 0; i < 250; i++)
    {
        if (leader_board[i].score == -1)
        {
            leader_board[i] = player;
            return i+1;
        }
        if (strcmp(leader_board[i].name, player.name) == 0)
        {
            if (player.score > leader_board[i].score)
            {
                leader_board[i] = player;
            }
            return i+1;
        }
    }
    if (i == 250)
    {
        bubbleSort(leader_board);
        leader_board[i-1] = player;
        return i;
    }
}


int get_winner_rank(winning_player leader_board[], winning_player player)
{
    int rank;
    rank = add_player_score(leader_board, player);
    write_data(leader_board);
    if (rank == 250)
    {
        return rank;
    }
    else
    {
        bubbleSort(leader_board);
        rank = add_player_score(leader_board, player);
        return rank;
    }
}
