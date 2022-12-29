#ifndef COLOR_H
#define COLOR_H

#define COLOR_FOREGROUND_RED     "\x1b[31m"
#define COLOR_FOREGROUND_GREEN   "\x1b[32m"
#define COLOR_FOREGROUND_YELLOW  "\x1b[33m"
#define COLOR_FOREGROUND_BLUE    "\x1b[34m"
#define COLOR_FOREGROUND_MAGENTA "\x1b[35m"
#define COLOR_FOREGROUND_CYAN    "\x1b[36m"
#define COLOR_BACKGROUND_RED     "\x1b[41m"
#define COLOR_BACKGROUND_GREEN   "\x1b[42m"
#define COLOR_BACKGROUND_YELLOW  "\x1b[43m"
#define COLOR_BACKGROUND_BLUE    "\x1b[44m"
#define COLOR_BACKGROUND_MAGENTA "\x1b[45m"
#define COLOR_BACKGROUND_CYAN    "\x1b[46m"

#define COLOR_FOREGROUND_RED_ID 0
#define COLOR_FOREGROUND_GREEN_ID 1
#define COLOR_FOREGROUND_YELLOW_ID 2
#define COLOR_FOREGROUND_BLUE_ID 3
#define COLOR_FOREGROUND_MAGENTA_ID 4
#define COLOR_FOREGROUND_CYAN_ID 5
#define COLOR_BACKGROUND_RED_ID 6
#define COLOR_BACKGROUND_GREEN_ID 7
#define COLOR_BACKGROUND_YELLOW_ID 8
#define COLOR_BACKGROUND_BLUE_ID 9/
#define COLOR_BACKGROUND_MAGENTA_ID 10
#define COLOR_BACKGROUND_CYAN_ID 11
#define COLOR_RESET   "\x1b[0m"

int get_random_foregroundcolor_id(int except_colorid);

void set_foreground_color(int color_id);

void set_console_color(char* foreground_color);

void set_console_colors(char* foreground_color, char* background_color);

void reset_console_color();
#endif