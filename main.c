#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "constants.h"
#include "zobrist.h"
#include "board.h"
#include "hash.h"

typedef struct searchNode{
    Board_t* state;
    struct searchNode *parent;
    struct searchNode **children;
    int nChildren;
    int depth;
} SearchNode_t;
SearchNode_t* newSearchNode(Board_t* board, int depth);
void deleteSearchNode(SearchNode_t* node);
void expand(SearchNode_t* node);

int main(void){
    return 0;    
}

