#include <stdio.h>
#include <stdlib.h>
#include "configuration.h"
#include "player.h"
#include "move_result.h"
#include "menu.h"
#include "tui.h"
#include "game.h"

void new_game_menu();
void view_main_menu();
void start_new_game();

int main()
{
    // view_main_menu();
    start_new_game();
    return 0;
}

void new_game_menu()
{
    Menu *new_game_menu = malloc(sizeof(*new_game_menu));

    new_game_menu->number_of_options = 5;
    new_game_menu->header = "Select an option : ";
    new_game_menu->options = malloc(sizeof(*new_game_menu->options) * new_game_menu->number_of_options);

    new_game_menu->options[0] = "Player vs Player";
    new_game_menu->options[1] = "Player vs Computer (Easy)";
    new_game_menu->options[2] = "Player vs Computer (Hard)";
    new_game_menu->options[3] = "Return to main menu";
    new_game_menu->options[4] = "Exit";

    int selected_option = read_selected_option(new_game_menu, "The index of option you want to select (between 1 and 5) : ");

    free(new_game_menu->options);
    free(new_game_menu);

    switch (selected_option)
    {
    case 1:
        start_new_game();
        break;
    case 4:
        view_main_menu();
        break;

    default:
        break;
    }
}

void view_main_menu()
{
    Menu *main_menu = malloc(sizeof(*main_menu));

    main_menu->number_of_options = 4;
    main_menu->header = "Select an option : ";
    main_menu->options = malloc(sizeof(*main_menu->options) * main_menu->number_of_options);

    main_menu->options[0] = "Start a new game";
    main_menu->options[1] = "Load game";
    main_menu->options[2] = "Leaderboard";
    main_menu->options[3] = "Exit";

    int selected_option = read_selected_option(main_menu, "The index of option you want to select (between 1 and 4) : ");

    free(main_menu->options);
    free(main_menu);

    switch (selected_option)
    {
    case 1:
        new_game_menu();
        break;

    default:
        break;
    }
}

void start_new_game()
{
    int is_end = 0;

    // Configuration *config = (Configuration *)malloc(sizeof(Configuration));

    GameState *game_state = malloc(sizeof(GameState));
    game_state->config = malloc(sizeof(Configuration));

    game_state->config->height = 10;
    game_state->config->width = 10;

    game_state->player1 = malloc(sizeof(Player));
    game_state->player2 = malloc(sizeof(Player));
    game_state->board = calloc(game_state->config->height * game_state->config->width, sizeof(int));
    game_state->elapsed_time = malloc(sizeof(hms_time));



    game_state->player1->id = 1;
    game_state->player1->color = 0;
    game_state->player1->number_of_moves = 0;
    game_state->player1->score = 0;
    
    game_state->player2->id = 2;
    game_state->player2->color = 1;
    game_state->player2->number_of_moves = 0;
    game_state->player2->score = 0;
    game_state->current_player_turn = 1;

    game_state->elapsed_time->hours = 0;
    game_state->elapsed_time->minutes = 0;
    game_state->elapsed_time->seconds = 0;
    
    game_state->timer_start = start_timer();
    // *game_state = init_game(*config);
    print_game_state(*game_state);
    do
    {
        is_end = make_player_move(game_state);

    } while (!is_end);
}