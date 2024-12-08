#ifndef TOOLS_H
#define TOOLS_H
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

bool is_digit(uint8_t c);
int digit_to_int(uint8_t c);

int num_str(uint8_t *line, int pos, int *num);

int get_array_length(uint8_t *line);
void pull_nums_to_array(uint8_t *line, int start_pos, int array[], int array_length);
void pull_long_nums_to_array(uint8_t *line, int start_pos, long int array[], int array_length);
void print_num_array(int array[], int length);
void print_long_num_array(long int array[], int length);
void print_char_array(uint8_t array[], int length);

long long gcd(long long int a, long long int b);
long long lcm(long long int a, long long int b);
int city_block_distance(int i1, int j1, int i2, int j2);
#endif