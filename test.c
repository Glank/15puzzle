#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "constants.h"
#include "zobrist.h"
#include "board.h"
#include "hash.h"

int main(void){
    init_zobrist();
    srand(time(NULL));
    Board_t* a = newBoard();
    Board_t* b = cloneBoard(a);
    Board_t* c = cloneBoard(a);
    scramble(a);

    printBoard(a);
    printBoard(b);
    printBoard(c);

    HashTable_t* table = newHashTable(32);
    put(table, a);
    printf("%d\n", table_contains(table, c));
    put(table, b);
    printf("%d\n", table_contains(table, c));

    deleteBoard(a);
    deleteBoard(b);
    deleteBoard(c);
    deleteHashTable(table);
    return 0;    
}

