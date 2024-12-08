#include "tools.h"

#define ROW_LENGTH 100
#define NUM_ROWS 100

static uint8_t platform[NUM_ROWS][ROW_LENGTH];

void move_rocks_north(){
    for (int j = 0; j < ROW_LENGTH; j++){
        for (int i = 1; i < NUM_ROWS; i++){
            if (platform[i][j] == 'O'){
                int new_i = i;
                while (new_i > 0 && platform[new_i - 1][j] != '#' && platform[new_i - 1][j] != 'O'){
                    new_i--;
                }
                platform[new_i][j] = 'O';
                if (new_i != i){
                    platform[i][j] = '.';
                }
            }
        }
    }
}

int calculate_load(){
    int load = 0;
    for (int i = 0; i < NUM_ROWS; i++){
        for (int j = 0; j < ROW_LENGTH; j++){
            if (platform[i][j] == 'O'){
                load += (NUM_ROWS - i);
            }
        }
    }
    return load;
}

int main(){
    FILE *file = fopen("day14_input.txt", "r");
    if (file != NULL){
        uint8_t line[ROW_LENGTH + 2];
        for (int i = 0; i < NUM_ROWS; i++){
            fgets(line, ROW_LENGTH + 2, file);
            memcpy(platform[i], line, ROW_LENGTH);
        }
    }
    fclose(file);

    move_rocks_north();
    for (int i = 0; i < NUM_ROWS; i++){
        print_char_array(platform[i], ROW_LENGTH);
    }

    int load = calculate_load();
    printf("load = %d\r\n", load);
}