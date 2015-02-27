#include <stdarg.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <assert.h>
#include "constants.h"
#include "zobrist.h"
#include "board.h"
#include "hash.h"
#include "search.h"

#define TIMES_TO_SCRAMBLE 40

int TOTAL_SEARCH_NODES = 0;
int TOTAL_HASH_NODES = 0;

int main(void){
    //initialize stuff
    init_zobrist();
    srand(time(NULL));
    //create a new board
    Board_t* goal = newBoard();
    //create a new visited cache
    HashTable_t* visited = newHashTable(32);
    //create a cloned state of the board and scrable it
    Board_t* scrabled = cloneBoard(goal);
    scramble_times(scrabled, TIMES_TO_SCRAMBLE);

    printf("Starting search...\n");
    SearchNode_t* root = newSearchNode(scrabled, 0, NULL);
    SearchNode_t* result = idf_search(root, goal, visited, 30);

    //print out the search
    if(result!=NULL){
        printf("Search Path:\n");
        printSearchNode(result);
    }
    else
        printf("Search failed.\n");

    //clean up
    deleteSearchNode(root, visited);
    assert(TOTAL_SEARCH_NODES==0);
    assert(TOTAL_HASH_NODES==0);
    deleteHashTable(visited);
    deleteBoard(goal);
    return 0;
}

