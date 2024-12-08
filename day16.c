#include "tools.h"

#define ROW_LENGTH 10
#define NUM_ROWS 10

typedef enum DIRECTION{
    NORTH, 
    SOUTH,
    EAST,
    WEST
} DIRECTION;

uint8_t grid[NUM_ROWS][ROW_LENGTH];
bool energised[NUM_ROWS][ROW_LENGTH] = {false};

struct path_tip{
    int i;
    int j;
    DIRECTION facing;
};

void move_tip(struct path_tip tip){
    energised[tip.i][tip.j] = true;
    printf("[%d][%d] now energised. ", tip.i, tip.j);
    printf("facing %d, at %c. ", tip.facing, grid[tip.i][tip.j]);
    switch(grid[tip.i][tip.j]){
        case '.':
            switch(tip.facing){
                case NORTH:
                    if (tip.i > 0){
                        tip.i--;
                        printf("going north\r\n");
                        move_tip(tip);
                    }
                    else{
                        printf("not space\r\n");
                    }
                    break;
                case SOUTH:
                    if (tip.i < NUM_ROWS - 1){
                        tip.i++;
                        printf("going south\r\n");
                        move_tip(tip);
                    }
                    else{
                        printf("not space\r\n");
                    }
                    break;
                case EAST:
                    if (tip.j < ROW_LENGTH - 1){
                        tip.j++;
                        printf("going east\r\n");
                        move_tip(tip);
                    }
                    else{
                        printf("not space\r\n");
                    }
                    break;
                case WEST:
                    if (tip.j > 0){
                        tip.j--;
                        printf("going west\r\n");
                        move_tip(tip);
                    }
                    else{
                        printf("Not space\r\n");
                    }
                    break;
            }
        case '/':
            switch(tip.facing){
                case NORTH:
                    if (tip.j < ROW_LENGTH - 1){
                        tip.facing = EAST;
                        tip.j++;
                        printf("going east\r\n");
                        move_tip(tip);
                    }
                    else{
                        printf("not space\r\n");
                    }
                    break;
                case SOUTH:
                    if (tip.j > 0){
                        tip.facing = WEST;
                        tip.j--;
                        printf("going west\r\n");
                        move_tip(tip);
                    }
                    else{
                        printf("not space\r\n");
                    }
                    break;
                case EAST:
                    if (tip.i > 0){
                        tip.facing = NORTH;
                        tip.i--;
                        printf("going north\r\n");
                        move_tip(tip);
                    }
                    else{
                        printf("not space\r\n");
                    }
                    break;
                case WEST:
                    if (tip.i < NUM_ROWS - 1){
                        tip.facing = SOUTH;
                        tip.i++;
                        printf("going south\r\n");
                        move_tip(tip);
                    }
                    else{
                        printf("not space\r\n");
                    }
                    break;
            }
        case '\\':
            switch(tip.facing){
                case NORTH:
                    if (tip.j > 0){
                        tip.facing = WEST;
                        tip.j--;
                        printf("going west\r\n");
                        move_tip(tip);
                    }
                    else{
                        printf("not space\r\n");
                    }
                    break;
                case SOUTH:
                    if (tip.j < ROW_LENGTH - 1){
                        tip.facing = EAST;
                        tip.j++;
                        printf("going east\r\n");
                        move_tip(tip);
                    }
                    else{
                        printf("not space\r\n");
                    }
                    break;
                case EAST:
                    if (tip.i < NUM_ROWS - 1){
                        tip.facing = SOUTH;
                        tip.i++;
                        printf("going south\r\n");
                        move_tip(tip);
                    }
                    else{
                        printf("not space\r\n");
                    }
                    break;
                case WEST:
                    if (tip.i > 0){
                        tip.facing = NORTH;
                        tip.i--;
                        printf("going north\r\n");
                        move_tip(tip);
                    }
                    else{
                        printf("not space\r\n");
                    }
                    break;
            }
        case '-':
            switch (tip.facing){
                case EAST:
                    if (tip.j < ROW_LENGTH - 1 && energised[tip.i][tip.j + 1] == false){
                        tip.j++;
                        printf("going east\r\n");
                        move_tip(tip);
                    }
                    else{
                        printf("not space or already done\r\n");
                    }
                    break;
                case WEST:
                    if (tip.j > 0 && energised[tip.i][tip.j - 1] == false){
                        tip.j--;
                        printf("going west\r\n");
                        move_tip(tip);
                    }
                    else{
                        printf("not space or already done\r\n");
                    }
                    break;
                case NORTH:
                case SOUTH:
                    if (tip.j < ROW_LENGTH - 1 && energised[tip.i][tip.j + 1] == false){
                        struct path_tip new_tip = tip;
                        new_tip.j++;
                        new_tip.facing = EAST;
                        printf("going east from [%d][%d]\r\n", tip.i, tip.j);
                        move_tip(new_tip);
                    }
                    else{
                        printf("not space for east or already done\r\n");
                    }
                    if (tip.j > 0 && energised[tip.i][tip.j - 1] == false){
                        struct path_tip new_tip = tip;
                        new_tip.j--;
                        new_tip.facing = WEST;
                        printf("going west from [%d][%d]\r\n", tip.i, tip.j);
                        move_tip(new_tip);
                    }
                    else{
                        printf("not space for west or already done\r\n");
                    }
                    break;
            }
        case '|':
            switch (tip.facing){
                case NORTH:
                    if (tip.i > 0 && energised[tip.i - 1][tip.j] == false){
                        tip.i--;
                        printf("going north\r\n");
                        move_tip(tip);
                    }
                    else{
                        printf("Not space or already done\r\n");
                    }
                    break;
                case SOUTH:
                    if (tip.i < NUM_ROWS - 1 && energised[tip.i + 1][tip.j] == false){
                        tip.i++;
                        printf("going south\r\n");
                        move_tip(tip);
                    }
                    else{
                        printf("not space or already done\r\n");
                    }
                    break;
                case EAST:
                case WEST:
                    if (tip.i < NUM_ROWS - 1 && energised[tip.i + 1][tip.j] == false){
                        struct path_tip new_tip = tip;
                        new_tip.i++;
                        new_tip.facing = SOUTH;
                        printf("going south from [%d][%d]\r\n", tip.i, tip.j);
                        move_tip(new_tip);
                    }
                    else{
                        printf("Not space for south or already done\r\n");
                    }
                    if (tip.i > 0 && energised[tip.i - 1][tip.j] == false){
                        struct path_tip new_tip = tip;
                        new_tip.i--;
                        new_tip.facing = NORTH;
                        printf("going north from [%d][%d]\r\n", tip.i, tip.j);
                        move_tip(new_tip);
                    }
                    else{
                        printf("not space for north or already done\r\n");
                    }
                    break;
            }
    }
}

int main(){
    FILE *file = fopen("day16_input.txt", "r");
    if (file != NULL){
        uint8_t line[ROW_LENGTH + 2];
        for (int i = 0; i < NUM_ROWS; i++){
            fgets(line, ROW_LENGTH + 2, file);
            memcpy(grid[i], line, ROW_LENGTH);
        }
    }
    fclose(file);
    struct path_tip start = {0, 0, EAST};
    move_tip(start);
    int num_energised = 0;
    for (int i = 0; i < NUM_ROWS; i++){
        for (int j = 0; j < ROW_LENGTH; j++){
            if (energised[i][j] == true){
                num_energised++;
            }
        }
    }
    printf("num energised = %d\r\n", num_energised);
}