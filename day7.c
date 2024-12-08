#include "tools.h"

#define NUM_ROWS 1000
#define ROW_LENGTH 11

typedef enum hand_type{
    HIGH = 1,
    PAIR = 2,
    TWO_PAIR = 3,
    THREE = 4,
    FULL_HOUSE = 5,
    FOUR = 6,
    FIVE = 7
} hand_type;

struct input{
    int hand[5];
    int bid;
    hand_type type;
};

static struct input inputs[NUM_ROWS] = {0};

hand_type get_type(int hand[]){
    int cards[13] = {0};
    for (int i = 0; i < 5; i++){
        cards[hand[i] - 2]++;
    }
    int num_pairs = 0, num_threes = 0;
    for (int i = 0; i < 13; i++){
        switch (cards[i]){
            case 5:
                return FIVE;
            case 4:
                return FOUR;
            case 3:
                num_threes++;
                break;
            case 2:
                num_pairs++;
                break;
        }
    }
    if (num_threes == 1 && num_pairs == 1){
        return FULL_HOUSE;
    }
    if (num_threes == 1){
        return THREE;
    }
    if (num_pairs == 2){
        return TWO_PAIR;
    }
    if (num_pairs == 1){
        return PAIR;
    }
    return HIGH;
}

int cmp_hands(const void *h1, const void *h2){
    struct input i1 = *(const struct input *) h1;
    int hand1[5]; memcpy(hand1, i1.hand, sizeof(i1.hand));
    struct input i2 = *(const struct input *) h2;
    int hand2[5]; memcpy(hand2, i2.hand, sizeof(i2.hand));

    hand_type type1 = get_type(hand1);
    hand_type type2 = get_type(hand2);
    if (type2 > type1){
        return 1;
    }
    if (type1 > type2){
        return -1;
    }
    for (int i = 0; i < 5; i++){
        int card1 = hand1[i];
        int card2 = hand2[i];
        if (card2 > card1){
            return 1;
        }
        if (card1 > card2){
            return -1;
        }
    }
    return 0;
}

int get_value(uint8_t card){
    if (is_digit(card)){
        return digit_to_int(card);
    }
    switch (card){
        case 'T':
            return 10;
        case 'J':
            return 11;
        case 'Q':
            return 12;
        case 'K':
            return 13;
        case 'A':
            return 14;
    }
    return 0;
}

struct input get_input(uint8_t *line){
    struct input this_input = {0};
    for (int pos = 0; pos < 5; pos++){
        this_input.hand[pos] = get_value(line[pos]);
    }
    int pos = 6;
    int bet = 0;
    while (is_digit(line[pos])){
        bet = bet * 10 + digit_to_int(line[pos]);
        pos++;
    }
    this_input.bid = bet;
    return this_input;
}

int main(){
    FILE *file = fopen("day7_input.txt", "r");
    if (file != NULL){
        uint8_t line[ROW_LENGTH];
        for (int i = 0; i < NUM_ROWS; i++){
            fgets(line, ROW_LENGTH, file);
            inputs[i] = get_input(line);
        }
        fclose(file);
    }

    qsort(inputs, NUM_ROWS, sizeof(struct input), cmp_hands);

    int winnings[NUM_ROWS];
    int sum = 0;
    for (int i = 0; i < NUM_ROWS; i++){
        //printf("Hand = ");
        //print_num_array(inputs[i].hand, 5);
        //printf("Bid = %d\r\n", inputs[i].bid);
        //printf("Hand type = %d\r\n", get_type(inputs[i].hand));
        winnings[i] = inputs[i].bid * (NUM_ROWS - i);
        //printf("Winnings = %d\r\n", winnings[i]);
        sum += winnings[i];
    }
    printf("Sum = %d\r\n", sum);

}