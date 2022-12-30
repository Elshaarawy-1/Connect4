#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "configuration.h"
#include "player.h"
#include "move_result.h"
#include "menu.h"
#include "tui.h"
#include "game.h"
#include "color.h"

bool new_game_menu();
bool view_main_menu();
bool start_new_game_pvp();
bool start_new_game_pvc();

int main()
{
    // view_main_menu();
    srand(time(0));
    if (start_new_game_pvp())
    {
        return 0;
    }
    return 0;
}

bool new_game_menu()
{
    Menu *new_game_menu = malloc(sizeof(*new_game_menu));

    new_game_menu->number_of_options = 4;
    new_game_menu->header = "Select an option : ";
    new_game_menu->options = malloc(sizeof(*new_game_menu->options) * new_game_menu->number_of_options);

    new_game_menu->options[0] = "Player vs Player";
    new_game_menu->options[1] = "Player vs Computer";
    new_game_menu->options[3] = "Return to main menu";
    new_game_menu->options[4] = "Exit";

    int selected_option = read_selected_option(new_game_menu, "The index of option you want to select (between 1 and 4) : ");

    free(new_game_menu->options);
    free(new_game_menu);

    switch (selected_option)
    {
    case 1:
        return start_new_game_pvp();
        break;
    case 4:
        return view_main_menu();
        break;

    default:
        break;
    }
    return false;
}

bool view_main_menu()
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
        return new_game_menu();
        break;

    default:
        break;
    }
    return false;
}

bool start_new_game_pvp()
{
    int move_type = 0;

    // Configuration *config = (Configuration *)malloc(sizeof(Configuration));

    GameState *game_state = malloc(sizeof(GameState));
    game_state->config = malloc(sizeof(Configuration));

    game_state->config->height = 4;
    game_state->config->width = 4;

    game_state->player1 = malloc(sizeof(Player));
    game_state->player2 = malloc(sizeof(Player));
    game_state->board = calloc(game_state->config->height * game_state->config->width, sizeof(int));
    game_state->elapsed_time = malloc(sizeof(hms_time));
    game_state->game_mode = GAME_MODE_PVP;

    Stack *undo_stack = createStack(game_state->config->height * game_state->config->width);
    Stack *redo_stack = createStack(game_state->config->height * game_state->config->width);

    init_game(game_state);
    print_game_state(*game_state);
    do
    {
        move_type = make_player_move(game_state, undo_stack, redo_stack);
        if (move_type == MOVE_EXIT)
        {
            return true;
        }
        if (move_type == MOVE_VALID)
        {
            redo_stack = createStack(game_state->config->height * game_state->config->width);
        }
        
    } while (move_type != MOVE_END);
    return false;
}

bool start_new_game_pvc()
{
    int move_type = 0;

    GameState *game_state = malloc(sizeof(GameState));
    game_state->config = malloc(sizeof(Configuration));

    game_state->config->height = 4;
    game_state->config->width = 4;

    game_state->player1 = malloc(sizeof(Player));
    game_state->player2 = malloc(sizeof(Player));
    game_state->board = calloc(game_state->config->height * game_state->config->width, sizeof(int));
    game_state->elapsed_time = malloc(sizeof(hms_time));
    game_state->game_mode = GAME_MODE_PVC;

    Stack *undo_stack = createStack(game_state->config->height * game_state->config->width);
    Stack *redo_stack = createStack(game_state->config->height * game_state->config->width);

    init_game(game_state);
    print_game_state(*game_state);
    do
    {
        move_type = make_player_move(game_state, undo_stack, redo_stack);
        if (move_type == MOVE_EXIT)
        {
            return true;
        }
        if (move_type == MOVE_VALID || move_type == MOVE_REDO) // computer only plays if the user enters a valid move or redos
        {
            move_type = make_computer_move(game_state, undo_stack, redo_stack);
            redo_stack = createStack(game_state->config->height * game_state->config->width);
        }

    } while (move_type != MOVE_END);
    return false;
}