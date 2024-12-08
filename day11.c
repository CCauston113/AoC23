#include "tools.h"

#define NUM_ROWS 140
#define ROW_LENGTH 140

int main()
{
    FILE *file = fopen("day11_input.txt", "r");
    if (file != NULL)
    {
        int extra_rows = 0, extra_cols = 0;
        int empty_rows[NUM_ROWS] = {0};
        int empty_cols[ROW_LENGTH] = {0};
        uint8_t space[NUM_ROWS][ROW_LENGTH];
        uint8_t line[ROW_LENGTH + 2];
        for (int i = 0; i < NUM_ROWS; i++)
        {
            fgets(line, ROW_LENGTH + 2, file);
            for (int j = 0; j < ROW_LENGTH; j++){
                space[i][j] = line[j];
            }
            int galaxy_count = 0;
            for (int j = 0; j < ROW_LENGTH; j++)
            {
                if (line[j] == '#')
                {
                    galaxy_count++;
                }
            }
            if (galaxy_count == 0)
            {
                extra_rows++;
                empty_rows[i] = 1;
            }
        }
        for (int i = 0; i < NUM_ROWS; i++){
            print_char_array(space[i], ROW_LENGTH);
        }
        printf("extra rows %d   \r\n", extra_rows); print_num_array(empty_rows, ROW_LENGTH);
        for (int j = 0; j < ROW_LENGTH; j++)
        {
            int galaxy_count = 0;
            for (int i = 0; i < NUM_ROWS; i++)
            {
                if (space[i][j] == '#')
                {
                    galaxy_count++;
                }
            }
            if (galaxy_count == 0)
            {
                extra_cols++;
                empty_cols[j] = 1;
            }
        }
        printf("extra columns %d   \r\n", extra_cols); print_num_array(empty_cols, NUM_ROWS);

        int num_galaxies = 0;
        for (int i = 0; i < NUM_ROWS; i++){
            for (int j = 0; j < NUM_ROWS; j++){
                if (space[i][j] == '#')
                    num_galaxies++;
            }
        }

        uint8_t expanded_space[NUM_ROWS + extra_rows][ROW_LENGTH + extra_cols];
        for (int i = 0; i < NUM_ROWS + extra_rows; i++){
            for (int j = 0; j < ROW_LENGTH + extra_cols; j++){
                expanded_space[i][j] = ' ';
            }
        }
        int dest_i = 0, dest_j = 0;
        int is[num_galaxies];
        int js[num_galaxies];
        int galaxy = 0;
        for (int i = 0; i < NUM_ROWS; i++)
        {
            dest_j = 0;
            for (int j = 0; j < ROW_LENGTH; j++)
            {
                expanded_space[dest_i][dest_j] = space[i][j];
                if (expanded_space[dest_i][dest_j] == '#'){
                    is[galaxy] = dest_i;
                    js[galaxy] = dest_j;
                    galaxy++;
                }
                printf("copying space[%d][%d]: %c to expanded_space[%d][%d]: %c\r\n", i, j, space[i][j], dest_i, dest_j, expanded_space[dest_i][dest_j]);
                if (empty_cols[j] == 1)
                {
                    dest_j++;
                    expanded_space[dest_i][dest_j] = space[i][j];
                    printf("copying space[%d][%d]: %c to expanded_space[%d][%d]: %c\r\n", i, j, space[i][j], dest_i, dest_j, expanded_space[dest_i][dest_j]);
                }
                dest_j++;
            }
            if (empty_rows[i] == 1)
            {
                dest_i++;
                for (int dest_j = 0; dest_j < ROW_LENGTH + extra_cols; dest_j++){
                    expanded_space[dest_i][dest_j] = expanded_space[dest_i - 1][dest_j];
                }
            }
            dest_i++;
        }

        for (int i = 0; i < NUM_ROWS + extra_rows; i++){
            print_char_array(expanded_space[i], ROW_LENGTH+extra_cols);
        }

        printf("galaxy is = "); print_num_array(is, num_galaxies);
        printf("galaxy js = "); print_num_array(js, num_galaxies);

        int sum = 0;
        for (int g = 0; g < num_galaxies - 1; g++){
            for (int h = g; h < num_galaxies; h++){
                sum += city_block_distance(is[g], js[g], is[h], js[h]);
            }
        }
        printf("sum = %d\r\n", sum);
    }
}