#include "tools.h"

static const char directions[] = "LRRLLRLLRRRLRRLRLRRRLRLLRLRRLRRRLRRRLRRLRRRLRLRRRLRLRRLRLRRRLRRLLRRLLLRRLRLRRRLRLRRRLRRLRRRLRLLRRLRRLRLRRRLRRRLRRLRRLLRLLRRRLRLRRLRRRLRRLRRRLRRRLLLLRRLRLRRRLRRRLLRRLLRRLRRRLRRRLRLRLLRRLRLRLRLRLRRLRLRLRRRLRRLRRLRRLRRRLRLRRRLRLRRLRLLLLRRRLLRRRLRLLRRRLRLLRRRLLRRLRLRLRLRLLLLRRLRRRLRLLRRLRRRLRRRLRLRRLRRLRLLRRRR";
static const size_t directions_length = strlen(directions);

#define NUM_NODES 798
struct node
{
    char name[3];
    char left[3];
    char right[3];
};
static struct node nodes[NUM_NODES] = {0};
static long long int steps = 37890973;

struct node get_node(uint8_t *line)
{
    struct node this_node = {0};
    for (int pos = 0; pos < 3; pos++)
    {
        this_node.name[pos] = line[pos];
    }
    for (int pos = 7; pos < 10; pos++)
    {
        this_node.left[pos - 7] = line[pos];
    }
    for (int pos = 12; pos < 15; pos++)
    {
        this_node.right[pos - 12] = line[pos];
    }
    return this_node;
}

int cmp_nodes(const void *n1, const void *n2)
{
    struct node node1 = *(const struct node *)n1;
    struct node node2 = *(const struct node *)n2;

    return memcmp(node1.name, node2.name, 3);
}

int get_node_pos(char name[])
{
    struct node target = {0};
    memcpy(target.name, name, 3);
    struct node *dest = (struct node *)bsearch(&target, nodes, NUM_NODES, sizeof(struct node), cmp_nodes);
    return dest - nodes;
}

bool check_end(int currents[], int length)
{
    int num_zs = 0;
    for (int node = 0; node < length; node++)
    {
        if (nodes[currents[node]].name[2] == 'Z')
        {
            num_zs++;
            printf("Thread %d   step %lld     reached ", node, steps); print_char_array(nodes[currents[node]].name, 3);
        }
    }
    return (num_zs == 6);
}

int main()
{
    // FILE *file = fopen("day8_input.txt", "r");
    // if (file != NULL)
    // {
    //     uint8_t line[18];
    //     int num_simultaneous = 0;
    //     for (int node = 0; node < NUM_NODES; node++)
    //     {
    //         fgets(line, 18, file);
    //         nodes[node] = get_node(line);
    //         if (nodes[node].name[2] == 'A')
    //         {
    //             num_simultaneous++;
    //         }
    //     }
    //     fclose(file);

    //     qsort(nodes, NUM_NODES, sizeof(struct node), cmp_nodes);

    //     int currents[] = {133, 428, 356, 507, 371, 706};
    //     while (!check_end(currents, num_simultaneous))
    //     {
    //         switch (directions[steps % directions_length])
    //         {
    //         case 'R':
    //             for (int current = 0; current < num_simultaneous; current++)
    //             {
    //                 if (memcmp(nodes[currents[current]].right, nodes[currents[current]].name, 3) != 0)
    //                 {
    //                     currents[current] = get_node_pos(nodes[currents[current]].right);
    //                 }
    //                 // printf("Thread %d: Now at ", current); print_char_array(nodes[currents[current]].name, 3);
    //             }
    //             break;
    //         case 'L':
    //             for (int current = 0; current < num_simultaneous; current++)
    //             {
    //                 if (memcmp(nodes[currents[current]].left, nodes[currents[current]].name, 3) != 0)
    //                 {
    //                     currents[current] = get_node_pos(nodes[currents[current]].left);
    //                 }
    //                 // printf("Thread %d: Now at ", current); print_char_array(nodes[currents[current]].name, 3);
    //             }
    //             break;
    //         }
    //         steps++;
    //         //printf("steps = %lld      currents = ", steps);
    //         //print_num_array(currents, num_simultaneous);
    //     }
    //     printf("steps = %lld\r\n", steps);
    // }

    long long int cycles[] = {21797, 18727, 18113, 24253, 16271, 22411};
    long long int steps = 1;
    for (int i = 0; i < 6; i++){
        steps = lcm(steps, cycles[i]);
    }
    printf("steps = %lld\r\n", steps);
}