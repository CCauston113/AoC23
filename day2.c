#include"tools.h"

#define RED 12
#define GREEN 13
#define BLUE 14

struct match{
    int red;
    int green;
    int blue;
};

int main(){
    FILE *file = fopen("day2_input.txt", "r");
    int sum = 0;
    if (file != NULL){
        uint8_t line[200];
        int game = 1;
        while (fgets(line, 200, file)){
            int pos = 8;
            int num = 0;
            bool num_finished = true;
            struct match m = (struct match) {0, 0, 0};
            bool possible = true;
            while (line[pos] != '\n'){
                if (is_digit(line[pos])){
                    num = num*10 + digit_to_int(line[pos]);
                    num_finished = false;
                }
                else if (!num_finished && !is_digit(line[pos])){
                    num_finished = true;
                    if (memcmp(line + pos + 1, "red", 3) == 0){
                        m.red = num;
                    }
                    else if (memcmp(line + pos + 1, "green", 5) == 0){
                        m.green = num;
                    }
                    else if (memcmp(line + pos + 1, "blue", 4) == 0){
                        m.blue = num;
                    }
                    num = 0;
                }
                if (line[pos] == ';'){
                    if (m.red > RED || m.blue > BLUE || m.green > GREEN){
                        possible = false;
                    }
                    printf("match R:%d G:%d B:%d    %c\r\n", m.red, m.green, m.blue, (m.red <= RED && m.blue <= BLUE && m.green <= GREEN)?'Y':'N');
                    m = (struct match){0, 0, 0};
                }
                pos++;
            }
            if (m.red > RED || m.blue > BLUE || m.green > GREEN){
                possible = false;
            }
            printf("match R:%d G:%d B:%d    %c\r\n", m.red, m.green, m.blue, (m.red <= RED && m.blue <= BLUE && m.green <= GREEN)?'Y':'N');
            printf("%s: %c\r\n", line, possible?'Y':'N');
            if (possible){
                sum += game;
            }
            game++;
        }
        fclose(file);
        printf("Sum = %d\r\n", sum);
    }
}