#include "tools.h"

long int get_options(long int time, long int distance)
{
    long int options = 0, time_left = 0, this_distance = 0;
    for (long int hold_time = 0; hold_time <= time; hold_time++)
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
    long int time = 60947882;
    long int distance = 475213810151650;
    long int options = get_options(time, distance);
    printf("options = %ld\r\n", options);
}