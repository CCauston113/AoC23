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

void move_rocks_south(){
    for (int j = 0; j < ROW_LENGTH; j++){
        for (int i = NUM_ROWS - 2; i >= 0; i--){
            if (platform[i][j] == 'O'){
                int new_i = i;
                while (new_i < NUM_ROWS - 1 && platform[new_i + 1][j] != '#' && platform[new_i + 1][j] != 'O'){
                    new_i++;
                }
                platform[new_i][j] = 'O';
                if (new_i != i){
                    platform[i][j] = '.';
                }
            }
        }
    }
}

void move_rocks_east(){
    for (int i = 0; i < NUM_ROWS; i++){
        for (int j = ROW_LENGTH - 2; j >= 0; j--){
            if (platform[i][j] == 'O'){
                int new_j = j;
                while (new_j < ROW_LENGTH - 1 && platform[i][new_j + 1] != '#' && platform[i][new_j + 1] != 'O'){
                    new_j++;
                }
                platform[i][new_j] = 'O';
                if (new_j != j){
                    platform[i][j] = '.';
                }
            }
        }
    }
}

void move_rocks_west(){
    for (int i = 0; i < NUM_ROWS; i++){
        for (int j = 1; j < ROW_LENGTH; j++){
            if (platform[i][j] == 'O'){
                int new_j = j;
                while (new_j > 0 && platform[i][new_j - 1] != '#' && platform[i][new_j - 1] != 'O'){
                    new_j--;
                }
                platform[i][new_j] = 'O';
                if (new_j != j){
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

int do_things(){
    int num_loops = 1000000000;
    int loads[num_loops];
    int load = 0;
    for (int loop = 0; loop < num_loops; loop++){
        move_rocks_north();
        move_rocks_west();
        move_rocks_south();
        move_rocks_east();
        loads[loop] = calculate_load();
        for (int i = loop - 1; i >= 0; i--){
            if (loads[loop] == loads[i]){
                int repeat_length = loop - i;
                int extra = (num_loops - loop) % repeat_length;
                load = loads[i + extra];
                return load;
            }
        }
    }
    return 0;
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

    
    // for (int i = 0; i < NUM_ROWS; i++){
    //     print_char_array(platform[i], ROW_LENGTH);
    // }
    int load = do_things();
    printf("load = %d\r\n", load);
}