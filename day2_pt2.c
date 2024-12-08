#include"tools.h"

// struct match{
//     int red;
//     int green;
//     int blue;
// };

int main(){
    FILE *file = fopen("day2_input.txt", "r");
    int sum = 0;
    if (file != NULL){
        uint8_t line[200];
        while (fgets(line, 200, file)){
            int pos = 8;
            int num = 0;
            bool num_finished = true;
            int r = 0, g = 0, b = 0;
            while (line[pos] != '\n'){
                if (is_digit(line[pos])){
                    num = num*10 + digit_to_int(line[pos]);
                    num_finished = false;
                }
                else if (!num_finished && !is_digit(line[pos])){
                    num_finished = true;
                    if (memcmp(line + pos + 1, "red", 3) == 0){
                        r = (num > r)?num:r;
                    }
                    else if (memcmp(line + pos + 1, "green", 5) == 0){
                        g = (num > g)?num:g;
                    }
                    else if (memcmp(line + pos + 1, "blue", 4) == 0){
                        b = (num > b)?num:b;
                    }
                    num = 0;
                }
                pos++;
            }
            sum += r*g*b;
        }
        fclose(file);
        printf("Sum = %d\r\n", sum);
    }
}