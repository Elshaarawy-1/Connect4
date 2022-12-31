#ifndef TUI_H
#define TUI_H

#include <stdbool.h>
#include "timer.h"
#include "menu.h"
#include "player.h"
#include "configuration.h"
#include "game_state.h"
#include "player_highscore.h"

#define INTERSECTION "╬"
#define HORIZONTAL_LINE "═══"
#define VERTICAL_LINE "║"
#define LEFT_VERTICAL_LINE "╠"
#define RIGHT_VERTICAL_LINE "╣"
#define TOP_HORIZONTAL_LINE "╦"
#define BOTTOM_HORIZONTAL_LINE "╩"
#define TOP_LEFT_CORNER "╔"
#define BOTTOM_LEFT_CORNER "╚"
#define TOP_RIGHT_CORNER "╗"
#define BOTTOM_RIGHT_CORNER "╝"


/// @brief prints a Menu struct to stdin
/// @param menu Menu to be printed
void print_menu(Menu *menu);

/// @brief Try to read an integer value from stdin
/// @param prompt the text to be printed to ask for user input
/// @param answer if the user enters a valid integer, answer is populated with the input integer
/// @return true if the user entered an integer
bool read_int(char *prompt_message, int *answer);

bool read_line (char *prompt, char *buff, size_t size);

void read_int_retry(char *prompt, int *answer);

void read_line_retry(char *prompt, char *buff, size_t size);

/// @brief Prompt the user to select an option from a menu and get the user input.
/// The user selects an option by entering the number that represents it.
/// If the user enters an invalid input, reprint the menu and ask the user for input again.
/// @param menu Menu that the user selects from
/// @param prompt_message the text to be printed to ask for user input
/// @return the number representing the option that the user selected (between 0 and menu.number_of_options)
int read_selected_option(Menu *menu, char *prompt_message);

/// @brief prints error message to console
/// @param error_msg the message to print
void print_err(char *error_msg);

/// @brief prints warning message to console
/// @param error_msg the message to print
void print_wrn(char *warning_msg);

void print_token(int player_id,int player_color);

void print_board(GameState game_state);

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

void print_game_state(GameState game_state);

int read_board_input(char* prompt_message,Configuration * config);


void print_leaderboard(winning_player leaderboard[], int leaderboard_size);

#endif