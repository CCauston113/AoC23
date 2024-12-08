#include "tools.h"

#define NUM_ROWS 140
#define row_length 142

struct gear
{
    int nums;
    int ratio;
};

static struct gear gears[NUM_ROWS][row_length];

void check_for_gears(uint8_t engine[][row_length], int row)
{
    int num = 0;
    int gearx, geary;
    bool gear_found = false;
    for (int pos = 0; pos < row_length; pos++)
    {
        if (is_digit(engine[row][pos]))
        {
            num = num * 10 + digit_to_int(engine[row][pos]);
            for (int m = -1; m < 2; m++)
            {
                for (int n = -1; n < 2; n++)
                {
                    if (row + n > -1 && row + n < NUM_ROWS && pos + m > -1 && pos + m < row_length)
                    {
                        if (engine[row + n][pos + m] == '*')
                        {
                            gearx = row + n;
                            geary = pos + m;
                            gear_found = true;
                        }
                    }
                }
            }
        }
        else if (num != 0 && (!is_digit(engine[row][pos]) || pos == row_length - 1))
        {
            // printf("num %d next to symbol? %d\r\n", num, symbol_adj);
            if (gear_found)
            {
                gears[gearx][geary].nums++;
                if (gears[gearx][geary].ratio == 0)
                {
                    gears[gearx][geary].ratio = num;
                }
                else
                {
                    gears[gearx][geary].ratio *= num;
                }
                printf("Adding to gear at [%d][%d]. Adding num %d so ratio %d\r\n", gearx, geary, num, gears[gearx][geary].ratio);
                gearx = 0;
                geary = 0;
                gear_found = false;
            }
            num = 0;
        }
    }
}

int main()
{
    FILE *file = fopen("day3_input.txt", "r");
    if (file != NULL)
    {
        uint8_t engine[NUM_ROWS][row_length];
        for (int i = 0; i < NUM_ROWS; i++)
        {
            fgets(engine[i], row_length, file);
            engine[i][row_length - 1] = '\0';
        }
        for (int i = 0; i < NUM_ROWS; i++)
        {
            printf("check row %d\r\n", i);
            check_for_gears(engine, i);
        }
    }
    fclose(file);
    int ratio_sum = 0;
    for (int i = 1; i < NUM_ROWS; i++)
    {
        for (int j = 1; j < row_length; j++)
        {
            if (gears[i][j].nums == 2)
            {
                ratio_sum += gears[i][j].ratio;
            }
        }
    }
    printf("Calibration sum = %d\r\n", ratio_sum);
}