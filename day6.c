#include "tools.h"

#define NUM_RACES 4

static int times[NUM_RACES] = {0};
static int distances[NUM_RACES] = {0};

int get_options(int time, int distance)
{
    int options = 0, time_left = 0, this_distance = 0;
    for (int hold_time = 0; hold_time <= time; hold_time++)
    {
        if (hold_time * (time - hold_time) > distance)
        {
            options++;
        }
    }
    return options;
}

int main()
{
    int options[NUM_RACES] = {0};
    FILE *file = fopen("day6_input.txt", "r");
    if (file != NULL)
    {
        uint8_t line[100];
        fgets(line, 100, file);
        pull_nums_to_array(line, 0, times, NUM_RACES);
        fgets(line, 100, file);
        pull_nums_to_array(line, 0, distances, NUM_RACES);
        fclose(file);
        printf("times = [");
        for (int j = 0; j < NUM_RACES; j++)
        {
            printf("%d ", times[j]);
        }
        printf("]\r\n");
        printf("distances = [");
        for (int j = 0; j < NUM_RACES; j++)
        {
            printf("%d ", distances[j]);
        }
        printf("]\r\n");

        for (int i = 0; i < NUM_RACES; i++)
        {
            options[i] = get_options(times[i], distances[i]);
        }
        
        printf("options = [");
        for (int j = 0; j < NUM_RACES; j++)
        {
            printf("%d ", options[j]);
        }
        printf("]\r\n");
        int product = 1;
        for (int i = 0; i < NUM_RACES; i++){
            product *= options[i];
        }
        printf("Product = %d\r\n", product);
    }
}