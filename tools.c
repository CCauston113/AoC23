#include "tools.h"

bool is_digit(uint8_t c)
{
    if (c >= '0' && c <= '9')
    {
        return true;
    }
    else
    {
        return false;
    }
}

int digit_to_int(uint8_t c)
{
    if (is_digit(c))
    {
        int num = c - '0';
        return num;
    }
    else
    {
        printf("%c is not a digit\r\n", c);
        return 0;
    }
}

struct num_str_data
{
    uint8_t *str;
    int length;
};

static const struct num_str_data numbers[] = {
    {"zero", 4},
    {"one", 3},
    {"two", 3},
    {"three", 5},
    {"four", 4},
    {"five", 4},
    {"six", 3},
    {"seven", 5},
    {"eight", 5},
    {"nine", 4}};

int num_str(uint8_t *line, int pos, int *num)
{
    int len = strlen(line);
    for (int i = 0; i < 10; i++)
    {
        int num_length = numbers[i].length;
        // e.g. pos = 2, num_length = 3, len = 4
        // 5 <= 4 = false, there's not space
        if (pos + num_length <= len)
        {
            bool found = true;
            for (int j = 0; j < num_length; j++)
            {
                if (numbers[i].str[j] != line[pos + j])
                {
                    found = false;
                }
            }
            if (found)
            {
                *num = i;
                return num_length;
            }
        }
    }
    return 1;
}

int get_array_length(uint8_t *line){
    int num_spaces = 0;
    int pos = 0;
    while (line[pos] != '\n'){
        if (line[pos] == ' '){
            num_spaces++;
        }
        pos++;
    }
    return num_spaces + 1;
}

void pull_nums_to_array(uint8_t *line, int start_pos, int array[], int array_length)
{
    int pos = 0, nums_found = 0, num = 0;
    bool num_finished = true;
    while (nums_found < array_length)
    {
        if (is_digit(line[pos]))
        {
            num_finished = false;
            num = num * 10 + digit_to_int(line[pos]);
        }
        else if (!num_finished && !is_digit(line[pos]))
        {
            num_finished = true;
            array[nums_found] = num;
            nums_found++;
            num = 0;
        }
        else if (line[pos] == '\n')
        {
            printf("ERROR Didn't find enough numbers\r\n");
            break;
        }
        pos++;
    }
}

void pull_long_nums_to_array(uint8_t *line, int start_pos, long int array[], int array_length)
{
    long int num = 0;
    int pos = 0, nums_found = 0;
    bool num_finished = true;
    while (nums_found < array_length)
    {
        if (is_digit(line[pos]))
        {
            num_finished = false;
            num = num * 10 + digit_to_int(line[pos]);
        }
        else if (!num_finished && !is_digit(line[pos]))
        {
            num_finished = true;
            array[nums_found] = num;
            nums_found++;
            num = 0;
        }
        else if (line[pos] == '\n')
        {
            printf("ERROR Didn't find enough numbers\r\n");
            break;
        }
        pos++;
    }
}

void print_num_array(int array[], int length)
{
    printf("[");
    for (int i = 0; i < length; i++)
    {
        printf("%d ", array[i]);
    }
    printf("]\r\n");
}

void print_long_num_array(long int array[], int length)
{
    printf("[");
    for (int i = 0; i < length; i++)
    {
        printf("%ld ", array[i]);
    }
    printf("]\r\n");
}

void print_char_array(uint8_t array[], int length)
{
    printf("[");
    for (int i = 0; i < length; i++)
    {
        printf(",%c ", array[i]);
    }
    printf("]\r\n");
}

long long gcd(long long int a, long long int b) 
{ 
    if (b == 0) 
        return a; 
    return gcd(b, a % b); 
}

long long lcm(long long int a, long long int b){
    return (a * b)/gcd(a, b);
}

int abs(int a){
    if (a >= 0){
        return a;
    }
    else{
        return a * -1;
    }
}

int city_block_distance(int i1, int j1, int i2, int j2){
    //printf("checking [%d][%d] to [%d][%d] = %d\r\n", i1, j1, i2, j2, abs(i2 - i1) + abs(j2 - j1));
    return abs(i2 - i1) + abs(j2 - j1);
}