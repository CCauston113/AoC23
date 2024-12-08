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
  int matches = 0;
  for (int num = 0; num < NUM_YOUR_NUMBERS; num++){
    for (int i = 0; i < NUM_WINNING_NUMBERS; i++){
      if (your_numbers[num] == winning_numbers[i]){
        matches++;
      }
    }
  }
  return matches;
}

void get_copies(int cards[], int card, int matches){
  for (int i = 1; i <= matches && card + i < NUM_CARDS; i++){
    printf("Adding %d copies of card %d\r\n", cards[card], card + i);
    cards[card + i] += cards[card];
  }
  printf("[");
  for (int i = 0; i < NUM_CARDS; i++){
    printf("%d ", cards[i]);
  }
  printf("]\r\n");
}

int main(){
  int winning_numbers[NUM_CARDS][NUM_WINNING_NUMBERS];
  int your_numbers[NUM_CARDS][NUM_YOUR_NUMBERS];
  int cards[NUM_CARDS];
  for (int i = 0; i < NUM_CARDS; i++){
    cards[i] = 1;
  }
  int matches = 0;

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
      matches = check_card(winning_numbers[i], your_numbers[i]);
      get_copies(cards, i, matches);
    }
    int total_cards = 0;
    for (int i = 0; i < NUM_CARDS; i++){
      total_cards += cards[i];
    }
    printf("total cards = %d\r\n", total_cards);
  }
}