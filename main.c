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
#include "helpers.h"
#include "config_parser.h"

bool new_game_menu(GameState *game_state);
bool view_main_menu(GameState *game_state);
bool start_new_game_pvp(GameState *game_state);
bool start_new_game_pvc(GameState *game_state);
bool end_game(GameState *game_state);

bool load_config(char *path, size_t path_size, Configuration *config)
{
    static int i = 0;

    bool valid_config = parse_config(path, config);
    if (valid_config)
    {
        // printf("%d\n%d\n%d\n", config->height, config->width, config->highscore);
        i = 0;
        return true;
    }
    else
    {
        i++;
        if (i > 3)
        {
            i = 0;
            return false;
        }
        print_err("Invalid config\n");
        char config_path[path_size];
        read_line_retry("Please enter the configuration file path : ", config_path, 256);

        return load_config(config_path, 256, config);
    }
}

int main()
{
    srand(time(0));

    Configuration *config = malloc(sizeof(Configuration));

    char config_path[256] = "config.xml";
    bool load_success = load_config(config_path, 256, config);

    if (!load_success)
    {
        printf("Failed to read config too many times. Exiting...");
    }

    bool exit = false;
    do
    {
        GameState *game_state = malloc(sizeof(GameState));
        game_state->config = config;
        exit = view_main_menu(game_state);
        if (!exit)
        {
            exit = end_game(game_state);
        }

    } while (!exit);

    return 0;
}

bool end_game(GameState *game_state)
{
    if (game_state->player1->score == game_state->player2->score)
    {
        printf("The game ended with a draw.\n");
    }
    else
    {

        if (game_state->player1->score > game_state->player2->score || game_state->game_mode == GAME_MODE_PVP)
        {
            Player *winner = game_state->player1->score > game_state->player2->score ? game_state->player1 : game_state->player2;

            set_foreground_color(winner->color);
            printf("Congratulations player %d. You won!\n", winner->id);

            char name[50];
            read_line_retry("Enter your name to save your score", name, 50);
            // TODO: save score
        }
        else
        {
            printf("Unfortunately you lost :(");
        }
        
    }

    int answer;
    read_int_retry("Enter 1 if you want to go back to main menu and play again : ", &answer);

    return answer != 1; // if answer isn't one, exit
}

bool new_game_menu(GameState *game_state)
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
        return start_new_game_pvp(game_state);
    case 2:
        return start_new_game_pvc(game_state);

    case 4:
        return view_main_menu(game_state);

    default:
        return false;
    }
}

bool view_main_menu(GameState *game_state)
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
        return new_game_menu(game_state);
        break;

    default:
        break;
    }
    return false;
}

bool start_new_game_pvp(GameState *game_state)
{
    int move_type = 0;

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

bool start_new_game_pvc(GameState *game_state)
{
    int move_type = 0;

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