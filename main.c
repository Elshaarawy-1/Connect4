#include <stdio.h>
#include "configuration.h"
#include "player.h"
#include "move_result.h"

int main(){
    Move move;
    move.row = 1;
    move.column = 1;

    printf("Move at %d",move.column);
    return 0;
}