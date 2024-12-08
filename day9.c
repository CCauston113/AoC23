#include "tools.h"

#define NUM_ROWS 200

bool all_zeroes(long int nums[], int length){
    for (int i = 0; i < length; i++){
        if (nums[i] != 0){
            return false;
        }
    }
    return true;
}

long int get_next_value(long int nums[], int length){
    long int diffs[length - 1];
    for (int i = 0; i < length - 1; i++){
        diffs[i] = nums[i + 1] - nums[i];
    }
    printf("Diffs = "); print_long_num_array(diffs, length - 1);
    if (all_zeroes(diffs, length - 1)){
        return 0;
    }
    return get_next_value(diffs, length - 1) + diffs[length - 2];
}

int main(){
    long int sum = 0;
    FILE *file = fopen("day9_input.txt", "r");
    if (file != NULL){
        uint8_t line[200];
        for (int i = 0; i < NUM_ROWS; i++){
            fgets(line, 200, file);
            int length = get_array_length(line);
            long int nums[length];
            char *data = line;
            int offset = 0;
            for (int j = 0; j < length - 1; j++){
                sscanf(data, "%ld %n", nums + j, &offset);
                data += offset;
            }
            sscanf(data, "%ld", nums + length - 1);
            print_long_num_array(nums, length);
            long int next = get_next_value(nums, length) + nums[length - 1];
            printf("next = %ld\r\n", next);
            sum += next;
        }
        fclose(file);
        printf("sum = %ld\r\n", sum);
    }
}