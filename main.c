#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "configuration.h"
#include "player.h"
#include "move_result.h"
#include "menu.h"
#include "tui.h"
#include "game.h"
#include "color.h"
#include "helpers.h"
#include "config_parser.h"
#include "save_load.h"
#include "player_highscore.h"
#include "savingplayer.h"
#include "setleaderboard.h"

bool new_game_menu(GameState *game_state);
bool view_main_menu(GameState *game_state);
bool load_game_menu(GameState *game_state);
bool start_new_game_pvp(GameState *game_state);
bool start_new_game_pvc(GameState *game_state);
bool run_pvp_game(GameState *game_state);
bool run_pvc_game(GameState *game_state);
bool end_game(GameState *game_state);
void set_save_file(GameState *game_state);
bool load_config(char *path, size_t path_size, Configuration *config);

int main()
{
    srand(time(0));

    Configuration *config = malloc(sizeof(Configuration));

    char config_path[256] = "config.xml";
    bool load_success = load_config(config_path, 256, config);

    if (!load_success)
    {
        printf("Failed to read config too many times. Loading default values");
        config->height = 9;
        config->width = 7;
        config->highscore = 10;
    }

    bool exit = false;
    do
    {
        GameState *game_state = malloc(sizeof(GameState));
        game_state->config = config;
        exit = view_main_menu(game_state);

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
            reset_console_color();
            char *name = calloc(50,sizeof(char));
            read_line_retry("Enter your name to save your score : ", name, 50);
            // printf("%s", name);
            winning_player leaderboard[250];
            for (int i = 0; i < 250; i++)
            {
                // strcpy(leaderboard[i].name,"N/A");
                leaderboard[i].score = -1;
            }

            read_leaderboard(leaderboard);
            winning_player leaderboard_entry;
            strcpy(leaderboard_entry.name, name);
            leaderboard_entry.score = winner->score;
            int rank = get_winner_rank(leaderboard, leaderboard_entry);
            printf("Your rank is %d\n", rank);
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

void set_save_file(GameState *game_state)
{
    FILE *file1;
    FILE *file2;
    FILE *file3;
    file1 = fopen("1.bin", "r");
    if (file1)
    {
        file2 = fopen("2.bin", "r");
        if (file2)
        {
            file3 = fopen("3.bin", "r");
            if (file3)
            {
                // if 1.bin, 2.bin, and 3.bin exists
                // save to the oldest one
                struct stat attrib1;
                stat("1.bin", &attrib1);
                struct stat attrib2;
                stat("2.bin", &attrib2);
                struct stat attrib3;
                stat("3.bin", &attrib3);

                if (attrib1.st_mtime < attrib2.st_mtime && attrib1.st_mtime < attrib3.st_mtime)
                {
                    game_state->file_id = 1;
                }
                else if (attrib2.st_mtime < attrib1.st_mtime && attrib2.st_mtime < attrib3.st_mtime)
                {
                    game_state->file_id = 2;
                }
                else
                {
                    game_state->file_id = 3;
                }
            }
            else
                game_state->file_id = 3;
        }
        else
            game_state->file_id = 2;
    }
    else
        game_state->file_id = 1; // if file 1.bin doesn't exist save to it.
}

bool new_game_menu(GameState *game_state)
{
    Menu *new_game_menu = malloc(sizeof(*new_game_menu));

    new_game_menu->number_of_options = 4;
    new_game_menu->header = "Select an option : ";
    new_game_menu->options = malloc(sizeof(*new_game_menu->options) * new_game_menu->number_of_options);

    new_game_menu->options[0] = "Player vs Player";
    new_game_menu->options[1] = "Player vs Computer";
    new_game_menu->options[2] = "Return to main menu";
    new_game_menu->options[3] = "Exit";

    int selected_option = read_selected_option(new_game_menu, "The index of option you want to select (between 1 and 4) : ");

    free(new_game_menu->options);
    free(new_game_menu);

    switch (selected_option)
    {
    case 1:
        return start_new_game_pvp(game_state);
    case 2:
        return start_new_game_pvc(game_state);

    case 3:
        return view_main_menu(game_state);

    case 4:
        return true;

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

    case 2:
        return load_game_menu(game_state);

    case 3:
    {
        winning_player leaderboard[250];
        bool leaderboard_valid = read_leaderboard(leaderboard);
        if (leaderboard_valid)
        {
            print_leaderboard(leaderboard, game_state->config->highscore);
        }
        else
        {
            // if leaderboard isn't found, write all its scores to -1
            for (int i = 0; i < 250; i++)
            {
                strcpy(leaderboard[i].name,"N/A");
                leaderboard[i].score = -1;
            }
            write_leaderboard(leaderboard);
            print_wrn("There are no scores to show\n");
        }
        return view_main_menu(game_state);
    }
    case 4:
        return true;

    default:
        break;
    }
    return false;
}

bool load_game_menu(GameState *game_state)
{
    Menu *load_menu = malloc(sizeof(*load_menu));

    load_menu->number_of_options = 5;
    load_menu->header = "Select an option : ";
    char *options[5];
    for (int i = 0; i < 5; i++)
    {
        options[i] = malloc(50);
    }

    load_menu->options = options;
    int actual_n = 0;
    for (int i = 1; i < 4; i++)
    {
        char file_name[10];
        sprintf(file_name, "%d.bin", i);
        FILE *file;
        file = fopen(file_name, "r");
        if (file)
        {
            strcpy(load_menu->options[actual_n], file_name);
            actual_n++;
        }
    }

    if (actual_n == 0)
    {
        printf("No games to load. Start a new game");
        free(load_menu);
        return new_game_menu(game_state);
    }

    load_menu->options[actual_n++] = "Return to main menu";
    load_menu->options[actual_n++] = "Exit";

    load_menu->number_of_options = actual_n;

    int selected_option = read_selected_option(load_menu, "The index of option you want to select : ");

    int n_files = actual_n - 2;
    if (n_files > 0 && selected_option <= n_files) // if there are loaded files and one is selected
    {
        int highscores = game_state->config->highscore; // keep the highscore size that is in the current config
        game_state->config->highscore = highscores;
        game_state->player1 = malloc(sizeof(Player));
        game_state->player2 = malloc(sizeof(Player));
        game_state->board = calloc(game_state->config->height * game_state->config->width, sizeof(int));
        game_state->elapsed_time = malloc(sizeof(hms_time));
        bool valid_game = read_data(load_menu->options[selected_option - 1], game_state);
        if (!valid_game)
        {
            print_err("Game file is corrupt\n");
            return new_game_menu(game_state);
        }

        game_state->timer_start = resume_timer(*(game_state->elapsed_time));
        if (strcmp(load_menu->options[selected_option - 1], "1.bin") == 0)
        {
            game_state->file_id = 1;
        }
        else if (strcmp(load_menu->options[selected_option - 1], "2.bin") == 0)
        {
            game_state->file_id = 2;
        }
        else
        {
            game_state->file_id = 3;
        }

        free(load_menu);

        if (game_state->game_mode == GAME_MODE_PVC)
        {

            game_state->game_mode = GAME_MODE_PVC;
            return run_pvc_game(game_state);
        }
        else
        {
            game_state->game_mode = GAME_MODE_PVP;
            return run_pvp_game(game_state);
        }
    }
    free(load_menu);
    if (selected_option == actual_n)
    {
        return true;
    }

    if (selected_option == actual_n - 1)
    {
        return view_main_menu(game_state);
    }
    return false;
}

bool run_pvp_game(GameState *game_state)
{

    int move_type = 0;
    Stack *undo_stack = createStack(game_state->config->height * game_state->config->width);
    Stack *redo_stack = createStack(game_state->config->height * game_state->config->width);

    print_game_state(*game_state);
    do
    {
        move_type = make_player_move(game_state, undo_stack, redo_stack);
        if (move_type == MOVE_EXIT)
        {
            free(game_state);
            return true;
        }
        if (move_type == MOVE_VALID)
        {
            redo_stack = createStack(game_state->config->height * game_state->config->width);
        }

        if (move_type == MOVE_VALID || move_type == MOVE_UNDO || move_type == MOVE_REDO)
        {
            char file_name[10];
            sprintf(file_name, "%d.bin", game_state->file_id);
            write_data(file_name, game_state);
        }
    } while (move_type != MOVE_END);
    return end_game(game_state);
}

bool start_new_game_pvp(GameState *game_state)
{
    set_save_file(game_state);
    game_state->player1 = malloc(sizeof(Player));
    game_state->player2 = malloc(sizeof(Player));
    game_state->board = calloc(game_state->config->height * game_state->config->width, sizeof(int));
    game_state->elapsed_time = malloc(sizeof(hms_time));
    game_state->game_mode = GAME_MODE_PVP;

    init_game(game_state);

    return run_pvp_game(game_state);
}

bool run_pvc_game(GameState *game_state)
{

    int move_type = 0;
    Stack *undo_stack = createStack(game_state->config->height * game_state->config->width);
    Stack *redo_stack = createStack(game_state->config->height * game_state->config->width);

    print_game_state(*game_state);
    do
    {
        move_type = make_player_move(game_state, undo_stack, redo_stack);
        if (move_type == MOVE_EXIT)
        {
            free(game_state);
            return true;
        }
        if (move_type == MOVE_VALID || move_type == MOVE_REDO) // computer only plays if the user enters a valid move or redos
        {
            move_type = make_computer_move(game_state, undo_stack, redo_stack);
            redo_stack = createStack(game_state->config->height * game_state->config->width);
        }

        if (move_type == MOVE_VALID || move_type == MOVE_UNDO || move_type == MOVE_REDO)
        {
            char file_name[10];
            sprintf(file_name, "%d.bin", game_state->file_id);
            write_data(file_name, game_state);
        }

    } while (move_type != MOVE_END);

    return end_game(game_state);
}

bool start_new_game_pvc(GameState *game_state)
{
    set_save_file(game_state);
    game_state->player1 = malloc(sizeof(Player));
    game_state->player2 = malloc(sizeof(Player));
    game_state->board = calloc(game_state->config->height * game_state->config->width, sizeof(int));
    game_state->elapsed_time = malloc(sizeof(hms_time));
    game_state->game_mode = GAME_MODE_PVC;

    init_game(game_state);
    return run_pvc_game(game_state);
}

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