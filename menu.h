#ifndef MENU_H
#define MENU_H

/// @brief struct representing a menu and its options
typedef struct s_menu
{
    int number_of_options;
    char **options;

    /// @brief text to be shown before the menu options
    char *header; 
} Menu;

#endif