#include "tools.h"

#define SECTION_LENGTH 10

int main(){
    FILE *file = fopen("day15_input.txt", "r");
    if (file != NULL){
        long long int sum = 0;
        int hash = 0;
        uint8_t section[SECTION_LENGTH];
        memset(section, '\0', SECTION_LENGTH);
        while (fgets(section, SECTION_LENGTH, file)){
            print_char_array(section, SECTION_LENGTH);
            for (int i = 0; i < SECTION_LENGTH; i++){
                if (section[i] != ',' && section[i] != '\0'){
                    hash = ((hash + section[i]) * 17) % 256;
                }
                else{
                    printf("hash = %d\r\n", hash);
                    sum += hash;
                    hash = 0;
                    if (section[i] == '\0'){
                        break;
                    }
                }
            }
            memset(section, '\0', SECTION_LENGTH);
        }
        fclose(file);
        printf("sum = %lld\r\n", sum);
    }
}