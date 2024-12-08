#include "tools.h"

#define NUM_ROWS 140
static int row_length = 0;

int check_for_parts(uint8_t engine[][row_length], int row){
    int num = 0;
    int sum = 0;
    bool symbol_adj = false;
    for (int pos = 0; pos < row_length; pos++){
        if (is_digit(engine[row][pos])){
            num = num * 10 + digit_to_int(engine[row][pos]);
            for (int m = -1; m < 2; m++){
                for (int n = -1; n < 2; n++){
                    if (num == 534){
                        printf("checking [%d][%d]\r\n", row + n, pos + m);
                    }
                    if (row + n > -1 && row + n < NUM_ROWS && pos + m > -1 && pos + m < row_length){
                        if (!is_digit(engine[row + n][pos + m]) && engine[row + n][pos + m] != '.' && engine[row + n][pos + m] != '\n'){
                            symbol_adj = true;
                            if (num == 534){
                                printf("next to symbol\r\n");
                            }
                        }
                    }
                }
            }
        }
        else if (num != 0 && (!is_digit(engine[row][pos]) || pos == row_length - 1)){
            //printf("num %d next to symbol? %d\r\n", num, symbol_adj);
            if (symbol_adj){
                sum += num;
            }
            num = 0;
            symbol_adj = false;
        }
    }
    printf("sum = %d\r\n", sum);
    return sum;
}

int main()
{
  int part_sum = 0;
  FILE *file = fopen("day3_input.txt", "r");
  if (file != NULL){
    uint8_t line[200];
    fgets(line, 200, file);
    int len = 0;
    while (line[len] != '\0'){
        len++;
    }
    row_length = len + 1;
    printf("row_length = %d\r\n", row_length);
    uint8_t engine[NUM_ROWS][row_length];
    for (int j = 0; j < row_length; j++){
        engine[0][j] = line[j];
    }
    for (int i = 1; i < NUM_ROWS; i++){
        fgets(engine[i], row_length, file);
        engine[i][row_length - 1] = '\0';
    }
    for (int i = 0; i < NUM_ROWS; i++){
        printf("check row %d\r\n", i);
        part_sum += check_for_parts(engine, i);
    }
  }
  fclose(file);
  printf("Calibration sum = %d\r\n", part_sum);
}