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
        int is[num_galaxies];
        int js[num_galaxies];
        int galaxy = 0;
        for (int i = 0; i < NUM_ROWS; i++){
            for (int j = 0; j < ROW_LENGTH; j++){
                if (space[i][j] == '#'){
                    is[galaxy] = i;
                    js[galaxy] = j;
                    galaxy++;
                }
            }
        }

        printf("galaxy is = "); print_num_array(is, num_galaxies);
        printf("galaxy js = "); print_num_array(js, num_galaxies);

        long long int sum = 0;
        long int base_distance;
        for (int g = 0; g < num_galaxies - 1; g++){
            for (int h = g + 1; h < num_galaxies; h++){
                base_distance = city_block_distance(is[g], js[g], is[h], js[h]);
                for (int i = is[g]; i < is[h]; i++){
                    if (empty_rows[i] == 1){
                        base_distance += 1;
                        //printf("now %ld from i %d\r\n", base_distance, i);
                    }
                }
                for (int j = js[g]; j < js[h]; j++){
                    if (empty_cols[j] == 1){
                        base_distance += 1;
                        //printf("now %ld from j %d\r\n", base_distance, j);
                    }
                }
                printf("[%d][%d] to [%d][%d] distance = %ld\r\n", is[g], js[g], is[h], js[h], base_distance);
                sum += base_distance;
                printf("sum = %lld\r\n", sum);
            }
        }
        printf("sum = %lld\r\n", sum);
    }
}