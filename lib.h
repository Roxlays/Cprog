#include <stdio.h>
#include <stdlib.h>

typedef struct Map
{
    int height;
    int width;
}; Map;

typedef struct Block
{
    int pos_x;
    int pos_y;
    struct Block* top;
    struct Block* right; 
    struct Block* bot;   
    struct Block* left;
}; Block;

Map* get_map(int height, int weidth);
void load_block(Map* map);

