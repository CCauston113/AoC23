#include "tools.h"

int get_calibration_data(uint8_t * line){
  int first_digit = 0, last_digit = 0;
  int pos = 0;
  while (line[pos] != '\n'){
    uint8_t c = line[pos];
    if (is_digit(c) && first_digit == 0){
      first_digit = digit_to_int(c);
      last_digit = digit_to_int(c);
      printf("First digit = %d\r\n", first_digit);
    }
    else if (is_digit(c)){
      last_digit = digit_to_int(c);
      printf("Last digit = %d   line[pos] = %c\r\n", last_digit, c);
    }
    pos++;
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
      calibration_sum += get_calibration_data(line);
    }
  }
  fclose(file);
  printf("Calibration sum = %d\r\n", calibration_sum);
}