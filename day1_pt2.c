#include "tools.h"

int get_calibration_data(uint8_t * line){
  int first_digit = 0, last_digit = 0;
  int pos = 0;
  int num;
  bool is_num = false;
  while (line[pos] != '\n'){
    uint8_t c = line[pos];
    if (is_digit(c)){
      num = digit_to_int(c);
      is_num = true;
    }
    else{
      int num_length = num_str(line, pos, &num);
      if (num_length > 1){
        is_num = true;
      }
    }
    if (is_num && first_digit == 0){
      first_digit = num;
      last_digit = num;
    }
    else if (is_num){
      last_digit = num;
    }
    pos ++;
  }
  return first_digit * 10 + last_digit;
}

int main()
{
  int calibration_sum = 0;
  FILE *file = fopen("day1_input.txt", "r");
  if (file != NULL){
    uint8_t line[100]; //longest line is 61 but allow extra in case I missed one
    while (fgets(line, 100, file)){
      int value = get_calibration_data(line);
      calibration_sum += value;
      printf("Value = %d  Total = %d\r\n", value, calibration_sum);
    }
  }
  fclose(file);
  printf("Calibration sum = %d\r\n", calibration_sum);
}