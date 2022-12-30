#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tui.h"
#include "color.h"

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

bool read_line(char *prompt, char *buff, size_t size)
{
    int ch, extra;

    // Get line with buffer overrun protection.
    if (prompt != NULL)
    {
        printf("%s", prompt);
        fflush(stdout);
    }
    if (fgets(buff, size, stdin) == NULL)
        return false;

    // If it was too long, there'll be no newline. In that case, we flush
    // to end of line so that excess doesn't affect the next call.
    if (buff[strlen(buff) - 1] != '\n')
    {
        extra = 0;
        while (((ch = getchar()) != '\n') && (ch != EOF))
            extra = 1;
        buff[strlen(buff) - 1] = '\0';
        return (extra == 1) ? false : true;
    }

    // Otherwise remove newline and give string back to caller.
    buff[strlen(buff) - 1] = '\0';
    return true;
}

void read_line_retry(char *prompt, char *buff, size_t size)
{
    bool success = read_line(prompt, buff, size);
    if (!success)
    {
        char err_msg[100];
        sprintf(err_msg, "Input is invalid. Make sure input size is at most %lu.\n", size);
        print_err(err_msg);
        read_line_retry(prompt, buff, size);
    }
}

void read_int_retry(char *prompt, int *answer)
{
    bool success = read_int(prompt, answer);
    if (!success)
    {
        char err_msg[100];
        print_err("Input is invalid. Make sure you entered an integer\n");
        read_int_retry(prompt, answer);
    }
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

void print_err(char *error_msg)
{
    set_console_color(COLOR_FOREGROUND_RED);
    printf("[ERR] %s", error_msg);
    reset_console_color();
}

void print_wrn(char *warning_msg)
{
    set_console_color(COLOR_FOREGROUND_YELLOW);
    printf("[WRN] %s", warning_msg);
    reset_console_color();
}

void print_token(int player_id, int player_color)
{
    switch (player_id)
    {
    case 1:
    case 2:
        set_foreground_color(player_color);
        printf(" ● ");
        reset_console_color();
        return;
    // case 2:
    //     printf(" ○ ");
    //     return;
    default:
        printf("   ");
        return;
    }
}

void print_board(GameState game_state)
{
    int frame_width = game_state.config->width * 2 + 1;
    int frame_height = game_state.config->height * 2 + 1;
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
                    {
                        int r = (i - 1) / 2;
                        int c = (j - 1) / 2;
                        int player_id = game_state.board[(r * game_state.config->width) + c];
                        int player_color;
                        if (player_id == 1)
                        {
                            player_color = game_state.player1->color;
                        }
                        else if (player_id == 2)
                        {
                            player_color = game_state.player2->color;
                        }

                        print_token(player_id, player_color);
                    }
                }
            }
        }
        printf("\n");
    }
}

void print_turn(Player *player)
{
    set_foreground_color(player->color);
    printf("\t\tPlayer %d's turn", player->id);
    reset_console_color();
}

void print_elapsed_time(hms_time elapsed_time)
{
    if (elapsed_time.hours == 0)
    {
        printf("Game time : %02d:%02d", elapsed_time.minutes, elapsed_time.seconds);
    }
    else if (elapsed_time.hours > 0)
    {
        printf("Game time : %02d:%02d:%02d", elapsed_time.hours, elapsed_time.minutes, elapsed_time.seconds);
    }
}

void print_playerid(Player *player)
{
    set_foreground_color(player->color);
    printf("Player %-22d", player->id);
    reset_console_color();
}

void print_n_moves(Player *player)
{
    set_foreground_color(player->color);
    printf("  Number of moves : %-10d", player->number_of_moves);
    reset_console_color();
}

void print_score(Player *player)
{
    set_foreground_color(player->color);
    printf("  Score : %-20d", player->score);
    reset_console_color();
}

void print_line()
{
    printf("\n");
}

void print_game_state(GameState game_state)
{
    system("clear");
    printf("Total moves : %d\n", game_state.total_moves);
    print_elapsed_time(*(game_state.elapsed_time));
    print_line();
    print_board(game_state);
    print_line();
    Player *current_player = game_state.current_player_turn == 1 ? game_state.player1 : game_state.player2;
    print_turn(current_player);
    print_line();
    print_playerid(game_state.player1);
    print_playerid(game_state.player2);
    print_line();
    print_score(game_state.player1);
    print_score(game_state.player2);
    print_line();
    print_n_moves(game_state.player1);
    print_n_moves(game_state.player2);
    print_line();
}

int read_board_input(char *prompt_message, Configuration *config)
{

    int answer;
    bool is_int = read_int(prompt_message, &answer);
    if (!is_int)
    {
        printf("\n[ERR] Input is invalid, it must be an integer.\n");
        return read_board_input(prompt_message, config);
    }

    if (answer <= config->width && answer > -3)
    {
        return answer;
    }

    // if the supplied option index isn't in the valid range, prompt the user again
    printf("\n[ERR] Input is invalid, the selected option is outside of the valid range\n");
    return read_board_input(prompt_message, config);
}