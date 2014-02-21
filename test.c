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

int TOTAL_SEARCH_NODES = 0;
int TOTAL_HASH_NODES = 0;
int verbose = 0;

void test_board(){
    if(verbose)
        printf("Testing Board...\n");
    init_zobrist();
    Board_t* a = newBoard();
    assert((*a).squares[1][1] == 4);
    deleteBoard(a);
    if(verbose)
        printf("Board Passed.\n");
}

void test_hash_table(){
    if(verbose)
        printf("Testing Hash Table...\n");
    init_zobrist();
    srand(time(NULL));
    Board_t* a = newBoard();
    Board_t* b = cloneBoard(a);
    scramble(a);
    scramble(b);
    Board_t* c = cloneBoard(b);

    HashTable_t* table = newHashTable(32);
    put(table, a);
    assert(!table_contains(table, c));
    put(table, b);
    assert(table_contains(table, c));
    put(table, b);
    assert(table_contains(table, c));
    table_remove(table, b);
    assert(!table_contains(table, c));

    deleteHashTable(table);
    deleteBoard(a);
    deleteBoard(b);
    deleteBoard(c);
    if(verbose)
        printf("Hash Table Passed.\n");
}

void test_search(){
    Board_t* start = newBoard();
    HashTable_t* visited = newHashTable(32);
    put(visited, start);
    SearchNode_t* start_node = newSearchNode(start, 0, NULL);
    
    expand(start_node, visited);
    assert((*start_node).nChildren == 2);

    SearchNode_t* child = (*start_node).children[1];
    expand(child, visited);
    assert((*child).nChildren == 2);

    SearchNode_t* subchild = (*child).children[0];
    prune_nonancestors(subchild, visited);

    deleteSearchNode(start_node, visited);
    deleteHashTable(visited);
}

void test_search2(){
    init_zobrist();
    Board_t* goal = newBoard();
    HashTable_t* visited = newHashTable(1);
    Board_t* end = cloneBoard(goal);
    scramble_times(end, 10);
    put(visited, end);
    SearchNode_t* root = newSearchNode(end, 0, NULL);
    df_search(root, goal, visited, 10);

    deleteSearchNode(root, visited);
    deleteHashTable(visited);
    deleteBoard(goal);
}

void test_search3(){
    init_zobrist();
    srand(time(NULL));
    Board_t* goal = newBoard();
    HashTable_t* visited = newHashTable(32);
    Board_t* end = cloneBoard(goal);
    scramble_times(end, 10000);
    put(visited, end);
    SearchNode_t* root = newSearchNode(end, 0, NULL);
    SearchNode_t* result = idf_search(root, goal, visited, 30);
    if(result!=NULL){
        printf("Results:\n");
        printSearchNode(result);
    }

    deleteSearchNode(root, visited);
    assert(TOTAL_SEARCH_NODES==0);
    assert(TOTAL_HASH_NODES==0);
    deleteHashTable(visited);
    deleteBoard(goal);
}

void test_search4(){
    init_zobrist();
    srand(time(NULL));
    Board_t* goal = newBoard();
    HashTable_t* visited = newHashTable(32);
    Board_t* end = cloneBoard(goal);
    scramble_times(end, 10);
    put(visited, end);
    SearchNode_t* root = newSearchNode(end, 0, NULL);
    SearchNode_t* result = astar_search(root, goal, visited, 10);
    if(result!=NULL){
        printf("Results:\n");
        printSearchNode(result);
    }

    deleteSearchNode(root, visited);
    assert(TOTAL_SEARCH_NODES==0);
    assert(TOTAL_HASH_NODES==0);
    deleteHashTable(visited);
    deleteBoard(goal);
}

void test_search5(){
    init_zobrist();
    srand(time(NULL));
    Board_t* goal = newBoard();
    HashTable_t* visited = newHashTable(64);
    Board_t* end = cloneBoard(goal);
    scramble_times(end, 100);
    put(visited, end);
    SearchNode_t* root = newSearchNode(end, 0, NULL);
    SearchNode_t* result = iastar_search(root, goal, visited, 100);
    if(result!=NULL){
        printf("Results:\n");
        printSearchNode(result);
    }

    deleteSearchNode(root, visited);
    assert(TOTAL_SEARCH_NODES==0);
    assert(TOTAL_HASH_NODES==0);
    deleteHashTable(visited);
    deleteBoard(goal);
}

int main(void){
    //test_board();
    //test_hash_table();
    //test_search();
    //test_search2();
    //test_search3();
    //test_search4();
    test_search5();
    printf("All Tests Passed.\n");
    return 0;
}

