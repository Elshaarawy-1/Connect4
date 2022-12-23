#ifndef TUI_H
#define TUI_H

#include <stdbool.h>
#include "timer.h"
#include "menu.h"
#include "player.h"

/// @brief prints a Menu struct to stdin
/// @param menu Menu to be printed
void print_menu(Menu *menu);

/// @brief Try to read an integer value from stdin
/// @param prompt the text to be printed to ask for user input
/// @param answer if the user enters a valid integer, answer is populated with the input integer
/// @return true if the user entered an integer
bool read_int(char *prompt_message, int *answer);

/// @brief Prompt the user to select an option from a menu and get the user input.
/// The user selects an option by entering the number that represents it.
/// If the user enters an invalid input, reprint the menu and ask the user for input again.
/// @param menu Menu that the user selects from
/// @param prompt_message the text to be printed to ask for user input
/// @return the number representing the option that the user selected (between 0 and menu.number_of_options)
int read_selected_option(Menu *menu, char *prompt_message);


void print_board();

/// @brief Print which player's turn it is
/// @param player the player whose turn it is
void print_turn(Player *player);

/// @brief Print elapsed time since the start of the game
/// @param elapsed_time the time to be printed
void print_elapsed_time(hms_time elapsed_time);

/// @brief Print player with id
/// @param player player whose info is to be printed
void print_playerid(Player *player);

/// @brief print number of moves a player played
/// @param player 
void print_n_moves(Player *player);

/// @brief Print player score
/// @param player player whose info is to be printed
void print_score(Player *player);

#endif