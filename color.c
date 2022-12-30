#include "color.h"
#include <stdio.h>
#include <stdlib.h>

int get_random_foregroundcolor_id(int except_colorid){
    int color = rand() % (4 + 1);
    if (color == except_colorid)
    {
        return get_random_foregroundcolor_id(except_colorid);
    }
    
    return color;
}

void set_foreground_color(int color_id)
{
    switch (color_id)
    {
    case COLOR_FOREGROUND_RED_ID:
        set_console_color(COLOR_FOREGROUND_RED);
        break;
    case COLOR_FOREGROUND_GREEN_ID:
        set_console_color(COLOR_FOREGROUND_GREEN);
        break;
    case COLOR_FOREGROUND_YELLOW_ID:
        set_console_color(COLOR_FOREGROUND_YELLOW);
        break;
    case COLOR_FOREGROUND_BLUE_ID:
        set_console_color(COLOR_FOREGROUND_BLUE);
        break;
    case COLOR_FOREGROUND_MAGENTA_ID:
        set_console_color(COLOR_FOREGROUND_MAGENTA);
        break;
    default:
        break;
    }
}

void set_console_color(char *foreground_color)
{
    printf("%s", foreground_color);
}

void set_console_colors(char *foreground_color, char *background_color)
{
    printf("%s%s", foreground_color, background_color);
}

void reset_console_color()
{
    printf(COLOR_RESET);
}