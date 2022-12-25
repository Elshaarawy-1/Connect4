#include <stdio.h>
#include "tui.h"

bool read_int(char *prompt_message, int *answer)
{
    printf("%s", prompt_message);
    int numberOfInputs = scanf("%d", answer);
    // Consume bad input.
    while (fgetc(stdin) != '\n')
        ;

    if (numberOfInputs != 1)
    {
        return false;
    }
    return true;
}

int read_selected_option(Menu *menu, char *prompt_message)
{
    print_menu(menu);
    int answer;
    bool is_int = read_int(prompt_message, &answer);
    if (!is_int)
    {
        printf("\n[ERR] Input is invalid, it must be an integer that represents the option you want to select\n");
        return read_selected_option(menu, prompt_message);
    }

    if (answer <= menu->number_of_options && answer > 0)
    {
        return answer;
    }

    // if the supplied option index isn't in the valid range, prompt the user again
    printf("\n[ERR] Input is invalid, the selected option is outside of the valid range\n");
    return read_selected_option(menu, prompt_message);
}

void print_menu(Menu *menu)
{
    printf("\n%s\n", menu->header);
    for (int i = 0; i < menu->number_of_options; i++)
    {
        printf("  %d. %s\n", i + 1, menu->options[i]);
    }
}

void print_token(int token)
{
    switch (token)
    {
    case 1:
        printf(" ● ");
        return;
    case 2:
        printf(" ○ ");
        return;
    default:
        printf("   ");
        return;
    }
}

void print_board(Configuration config, int board[][config.width])
{
    int frame_width = config.width * 2 + 1;
    int frame_height = config.height * 2 + 1;
    for (int i = 0; i < frame_height; i++)
    {
        bool at_top = i == 0;
        bool at_bottom = i == frame_height - 1;
        bool at_horizontal_border = i % 2 == 0; // if at an even row, then a border should be printed

        for (int j = 0; j < frame_width; j++)
        {
            bool at_left = j == 0;
            bool at_right = j == frame_width - 1;
            bool at_vertical_border = j % 2 == 0; // if at an even column, then a border should be printed

            if (at_top)
            {
                if (at_left)
                    printf(TOP_LEFT_CORNER);
                else if (at_right)
                    printf(TOP_RIGHT_CORNER);
                else if (at_vertical_border)
                    printf(TOP_HORIZONTAL_LINE);
                else
                    printf(HORIZONTAL_LINE);
            }
            else if (at_bottom)
            {
                if (at_left)
                    printf(BOTTOM_LEFT_CORNER);
                else if (at_right)
                    printf(BOTTOM_RIGHT_CORNER);
                else if (at_vertical_border)
                    printf(BOTTOM_HORIZONTAL_LINE);
                else
                    printf(HORIZONTAL_LINE);
            }
            else
            {
                if (at_left)
                {
                    if (at_horizontal_border)
                        printf(LEFT_VERTICAL_LINE);
                    else
                        printf(VERTICAL_LINE);
                }
                else if (at_right)
                {
                    if (at_horizontal_border)
                        printf(RIGHT_VERTICAL_LINE);
                    else
                        printf(VERTICAL_LINE);
                }
                else
                {
                    if (at_horizontal_border && at_vertical_border)
                        printf(INTERSECTION);
                    else if (at_horizontal_border && !at_vertical_border)
                        printf(HORIZONTAL_LINE);
                    else if (!at_horizontal_border && at_vertical_border)
                        printf(VERTICAL_LINE);
                    else
                        print_token(board[(i - 1) / 2][(j - 1) / 2]);
                }
            }
        }
        printf("\n");
    }
}

void print_turn(Player *player)
{
    printf("Player %d's turn", player->id);
}

void print_elapsed_time(hms_time elapsed_time)
{
    char *str_elapsed_time = NULL;
    if (elapsed_time.hours == 0)
    {
        printf(str_elapsed_time, "Game time : %02d:%02d", elapsed_time.minutes, elapsed_time.seconds);
    }
    else if (elapsed_time.hours > 0)
    {
        printf("Game time : %02d:%02d:%02d", elapsed_time.hours, elapsed_time.minutes, elapsed_time.seconds);
    }
}

void print_playerid(Player *player)
{
    printf("Player %d", player->id);
}

void print_n_moves(Player *player)
{
    printf("  Number of moves : %d", player->number_of_moves);
}

void print_score(Player *player)
{
    printf("  Score : %d", player->score);
}

