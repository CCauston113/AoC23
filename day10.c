#include "tools.h"

#define NUM_ROWS 5
#define ROW_LENGTH 5

static int start_i;
static int start_j;

static int loop_length = 1;

struct pipe
{
    bool up;
    bool down;
    bool left;
    bool right;
    bool connected_to_start;
    int distance;
};

static struct pipe grid[NUM_ROWS][ROW_LENGTH];

void draw_grid()
{
    struct pipe this_pipe;
    for (int i = 0; i < NUM_ROWS; i++)
    {
        for (int j = 0; j < ROW_LENGTH; j++)
        {
            this_pipe = grid[i][j];
            if (this_pipe.up == true && this_pipe.down == true && this_pipe.left == true && this_pipe.right == true)
            {
                printf("%c", 'S');
            }
            else if (!this_pipe.up && !this_pipe.down && !this_pipe.left && !this_pipe.right)
            {
                printf("%c", '.');
            }
            else if (this_pipe.up && !this_pipe.down && this_pipe.left && !this_pipe.down)
            {
                printf("%c", 'J');
            }
            else if (this_pipe.up && !this_pipe.down && !this_pipe.left && this_pipe.right)
            {
                printf("%c", 'L');
            }
            else if (!this_pipe.up && this_pipe.down && this_pipe.left && !this_pipe.right)
            {
                printf("%c", '7');
            }
            else if (!this_pipe.up && this_pipe.down && !this_pipe.left && this_pipe.down)
            {
                printf("%c", 'F');
            }
            else if (this_pipe.up && this_pipe.down && !this_pipe.left && !this_pipe.right)
            {
                printf("%c", '|');
            }
            else
            {
                printf("%c", '-');
            }
        }
        printf("\r\n");
    }
}

void check_start_connectedness(int i, int j)
{
    if (i > 0 && grid[i][j].up && grid[i - 1][j].down)
    {
        if (!grid[i - 1][j].connected_to_start)
        {
            grid[i - 1][j].connected_to_start = true;
            loop_length++;
            check_start_connectedness(i - 1, j);
        }
    }
    if (i < NUM_ROWS && grid[i][j].down && grid[i + 1][j].up)
    {
        if (!grid[i + 1][j].connected_to_start)
        {
            grid[i + 1][j].connected_to_start = true;
            loop_length++;
            check_start_connectedness(i + 1, j);
        }
    }
    if (j > 0 && grid[i][j].left && grid[i][j - 1].right)
    {
        if (!grid[i][j - 1].connected_to_start)
        {
            grid[i][j - 1].connected_to_start = true;
            loop_length++;
            check_start_connectedness(i, j - 1);
        }
    }
    if (j < ROW_LENGTH && grid[i][j].right && grid[i][j + 1].left)
    {
        if (!grid[i][j + 1].connected_to_start)
        {
            grid[i][j + 1].connected_to_start = true;
            loop_length++;
            check_start_connectedness(i, j + 1);
        }
    }
}

int adjacency(int i, int j)
{
    int adj = 0;
    struct pipe here = grid[i][j];
    if (i > 0 && here.up && grid[i - 1][j].down)
    {
        adj++;
    }
    if (i < NUM_ROWS - 1 && here.down && grid[i + 1][j].up)
    {
        adj++;
    }
    if (j > 0 && here.left && grid[i][j - 1].right)
    {
        adj++;
    }
    if (j < ROW_LENGTH - 1 && here.right && grid[i][j + 1].left)
    {
        adj++;
    }
    return adj;
}

bool cull_grid()
{
    bool changed = false;
    for (int i = 0; i < NUM_ROWS; i++)
    {
        for (int j = 0; j < ROW_LENGTH; j++)
        {
            if (!(grid[i][j].up && grid[i][j].down && grid[i][j].left && grid[i][j].right) && !(!grid[i][j].up && !grid[i][j].down && !grid[i][j].left && !grid[i][j].right))
            {
                if (!grid[i][j].connected_to_start || adjacency(i, j) != 2)
                {
                    grid[i][j] = (struct pipe){.up = false, .down = false, .left = false, .right = false};
                    changed = true;
                }
            }
        }
    }
    printf("Culled: \r\n");
    draw_grid();
    return changed;
}

int main()
{
    FILE *file = fopen("day10_input.txt", "r");
    if (file != NULL)
    {
        uint8_t row[ROW_LENGTH + 2];
        for (int i = 0; i < NUM_ROWS; i++)
        {
            fgets(row, ROW_LENGTH + 2, file);
            for (int j = 0; j < ROW_LENGTH; j++)
            {
                switch (row[j])
                {
                case '7':
                    grid[i][j] = (struct pipe){.up = false, .down = true, .left = true, .right = false};
                    break;
                case 'J':
                    grid[i][j] = (struct pipe){.up = true, .down = false, .left = true, .right = false};
                    break;
                case 'L':
                    grid[i][j] = (struct pipe){.up = true, .down = false, .left = false, .right = true};
                    break;
                case 'F':
                    grid[i][j] = (struct pipe){.up = false, .down = true, .left = false, .right = true};
                    break;
                case '|':
                    grid[i][j] = (struct pipe){.up = true, .down = true, .left = false, .right = false};
                    break;
                case '-':
                    grid[i][j] = (struct pipe){.up = false, .down = false, .left = true, .right = true};
                    break;
                case '.':
                    grid[i][j] = (struct pipe){.up = false, .down = false, .left = false, .right = false};
                    break;
                case 'S':
                    grid[i][j] = (struct pipe){.up = true, .down = true, .left = true, .right = true, .connected_to_start = true};
                    start_i = i;
                    start_j = j;
                    break;
                }
            }
        }
        fclose(file);
        draw_grid();
        check_start_connectedness(start_i, start_j);
        while (cull_grid())
            ;
        int direction = 2;
        int furthest = 0;
        int i = start_i, j = start_j;
        struct pipe here = grid[i][j];
        for (int pipe = 0; pipe < loop_length; pipe++){
            grid[i][j].distance = furthest;
            switch (direction){
                case 0:
                    //up
                    if (here.left && grid[i][j-1].right){
                        direction = 3;
                        j--;
                    }
                    else if (here.up && grid[i-1][j].down){
                        i--;
                    }
                    else if (here.right && grid[i][j+1].left){
                        direction = 1;
                        j++;
                    }
                    break;
                case 1:
                    //right
                    if (here.up && grid[i-1][j].down){
                        direction = 0;
                        i--;
                    }
                    else if (here.right && grid[i][j+1].left){
                        j++;
                    }
                    else if (here.down && grid[i+1][j].up){
                        direction = 2;
                        i++;
                    }
                    break;
                case 2:
                    //down
                    if (here.right && grid[i][j+1].left){
                        direction = 1;
                        j++;
                    }
                    else if (here.down && grid[i+1][j].up){
                        i++;
                    }
                    else if (here.left && grid[i][j-1].right){
                        direction = 3;
                        j--;
                    }
                    break;
                case 3:
                    //left
                    if (here.down && grid[i+1][j].up){
                        direction = 2;
                        i++;
                    }
                    else if (here.left && grid[i][j-1].right){
                        j--;
                    }
                    else if (here.up && grid[i-1][j].down){
                        direction = 0;
                        i--;
                    }
                    break;
            }
            furthest++;
        }
        printf("loop length = %d    furthest = %d\r\n", loop_length, furthest);
        printf("actual furthest = %d\r\n", furthest/2);
    }
}