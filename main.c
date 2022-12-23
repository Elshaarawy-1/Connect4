#include <stdio.h>
#include <stdlib.h>
#include "configuration.h"
#include "player.h"
#include "move_result.h"
#include "menu.h"
#include "tui.h"

void new_game_menu();
void view_main_menu();



int main()
{
    view_main_menu();

    return 0;
}

void new_game_menu(){
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