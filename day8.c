#include "tools.h"

static const char directions[] = "LRRLLRLLRRRLRRLRLRRRLRLLRLRRLRRRLRRRLRRLRRRLRLRRRLRLRRLRLRRRLRRLLRRLLLRRLRLRRRLRLRRRLRRLRRRLRLLRRLRRLRLRRRLRRRLRRLRRLLRLLRRRLRLRRLRRRLRRLRRRLRRRLLLLRRLRLRRRLRRRLLRRLLRRLRRRLRRRLRLRLLRRLRLRLRLRLRRLRLRLRRRLRRLRRLRRLRRRLRLRRRLRLRRLRLLLLRRRLLRRRLRLLRRRLRLLRRRLLRRLRLRLRLRLLLLRRLRRRLRLLRRLRRRLRRRLRLRRLRRLRLLRRRR";
static const size_t directions_length = strlen(directions);

#define NUM_NODES 798
struct node{
    char name[3];
    char left[3];
    char right[3];
};
static struct node nodes[NUM_NODES] = {0};

struct node get_node(uint8_t *line){
    struct node this_node = {0};
    for (int pos = 0; pos < 3; pos++){
        this_node.name[pos] = line[pos];
    }
    for (int pos = 7; pos < 10; pos++){
        this_node.left[pos - 7] = line[pos];
    }
    for (int pos = 12; pos < 15; pos++){
        this_node.right[pos - 12] = line[pos];
    }
    return this_node;
}

int get_node_pos(char name[]){
    for (int pos = 0; pos < NUM_NODES; pos++){
        if (memcmp(nodes[pos].name, name, 3) == 0){
            return pos;
        }
    }
}

int main(){
    FILE *file = fopen("day8_input.txt", "r");
    if (file != NULL){
        uint8_t line[18];
        for (int node = 0; node < NUM_NODES; node++){
            fgets(line, 18, file);
            nodes[node] = get_node(line);
        }
        fclose(file);

        char next[] = {'A', 'A', 'A'};
        int current = get_node_pos(next);
        int steps = 0;
        while (memcmp(next, "ZZZ", 3) != 0){
            switch(directions[steps % directions_length]){
                case 'R':
                    current = get_node_pos(nodes[current].right);
                    memcpy(next, nodes[current].name, 3);
                    break;
                case 'L':
                    current = get_node_pos(nodes[current].left);
                    memcpy(next, nodes[current].name, 3);
                    break;
            }
            steps++;
        }
        printf("steps = %d\r\n", steps);
    }
}