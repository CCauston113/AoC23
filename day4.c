#include "tools.h"

#define NUM_CARDS 203
#define NUM_WINNING_NUMBERS 10
#define NUM_YOUR_NUMBERS 25
// #define NUM_CARDS 6
// #define NUM_WINNING_NUMBERS 5
// #define NUM_YOUR_NUMBERS 8

void copy_card(uint8_t *card, int winning_numbers[], int your_numbers[]){
  int pos = 8;
  bool num_finished = true;
  int num = 0, winning_num = 0;
  while (card[pos] != '|'){
    if (is_digit(card[pos])){
      num_finished = false;
      int digit = digit_to_int(card[pos]);
      num = num * 10 + digit;
    }
    else if (num_finished == false && !is_digit(card[pos])){
      num_finished = true;
      winning_numbers[winning_num] = num;
      winning_num++;
      num = 0;
    }
    pos++;
  }
  int your_num = 0;
  while (card[pos] != '\n' && card[pos] != '\0'){
    if (is_digit(card[pos])){
      num_finished = false;
      int digit = digit_to_int(card[pos]);
      num = num * 10 + digit;
    }
    else if (num_finished == false && !is_digit(card[pos])){
      num_finished = true;
      your_numbers[your_num] = num;
      your_num++;
      num = 0;
    }
    pos++;
  }
  your_numbers[your_num] = num;
}

int check_card(int winning_numbers[], int your_numbers[]){
  int points = 0;
  for (int num = 0; num < NUM_YOUR_NUMBERS; num++){
    for (int i = 0; i < NUM_WINNING_NUMBERS; i++){
      if (your_numbers[num] == winning_numbers[i]){
        if (!points){
          points = 1;
        }
        else{
          points *= 2;
        }
      }
    }
  }
  return points;
}

int main(){
  int winning_numbers[NUM_CARDS][NUM_WINNING_NUMBERS];
  int your_numbers[NUM_CARDS][NUM_YOUR_NUMBERS];
  int total_score = 0;

  FILE *file = fopen("day4_input.txt", "r");
  if (file != NULL){
    uint8_t card[200];
    for (int i = 0; i < NUM_CARDS; i++){
      fgets(card, 200, file);
      copy_card(card, winning_numbers[i], your_numbers[i]);
      printf("winning_numbers %d = [", i);
      for (int j = 0; j < NUM_WINNING_NUMBERS; j++){
        printf("%d ", winning_numbers[i][j]);
      }
      printf("]\r\n");
      printf("your numbers = [");
      for (int j = 0; j < NUM_YOUR_NUMBERS; j++){
        printf("%d ", your_numbers[i][j]);
      }
      printf("]\r\n");
      total_score += check_card(winning_numbers[i], your_numbers[i]);
      printf("score = %d\r\n", total_score);
    }
  }
}