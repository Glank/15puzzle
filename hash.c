#include <stdio.h>
#include <stdlib.h>
#include "constants.h"
#include "zobrist.h"
#include "board.h"
#include "hash.h"


extern int TOTAL_HASH_NODES;
//#### HashNode_t Methods ####
HashNode_t* newHashNode(Board_t* load){
    TOTAL_HASH_NODES++;
    HashNode_t* node = (HashNode_t*) malloc(sizeof(HashNode_t));
    (*node).load = load;
    (*node).next = NULL;
    return node;
}
//Doesn't free the boards!
void deleteHashNode(HashNode_t* node){
    TOTAL_HASH_NODES--;
    if((*node).next != NULL)
        deleteHashNode((*node).next);
    free(node);
}
int append(HashNode_t* node, HashNode_t* other){
    if(equalsBoard((*node).load, (*other).load))
        return 0;
    if((*node).next == NULL)
        (*node).next = other;
    else
        append((*node).next, other);
    return 1;
}
HashNode_t* node_remove(HashNode_t* node, Board_t* board){
    if(equalsBoard((*node).load, board)){
        HashNode_t* new_head = (*node).next;
        (*node).next = NULL;
        deleteHashNode(node);
        return new_head;
    }
    else if((*node).next != NULL){
        (*node).next = node_remove((*node).next, board);
        return node;
    }
    return NULL;
}
int node_contains(HashNode_t* node, Board_t* load){
    if(equalsBoard((*node).load, load))
        return 1;
    else if((*node).next != NULL)
        return node_contains((*node).next, load);
    return 0;
}
void printHashNode(HashNode_t* node){
    printBoard((*node).load);
    if((*node).next!=NULL)
        printHashNode((*node).next);
}
    

//#### HashTable_t Methods ####
HashTable_t* newHashTable(int nBuckets){
    HashTable_t* table = (HashTable_t*) malloc(sizeof(HashTable_t));
    (*table).buckets = (HashNode_t**) malloc(sizeof(HashNode_t*)*nBuckets);
    (*table).nBuckets = nBuckets;
    int i;
    for(i=0; i<nBuckets; i++)
        (*table).buckets[i] = NULL;
    return table;
}
//doesnt free the tables within!
void deleteHashTable(HashTable_t* table){
    clear(table);
    free((*table).buckets);
    free(table);
}
void put(HashTable_t* table, Board_t* board){
    int bucket = ((*board).hash)%((*table).nBuckets);
    HashNode_t* node = newHashNode(board);
    if((*table).buckets[bucket] == NULL)
        (*table).buckets[bucket] = node;
    else if(!append((*table).buckets[bucket], node))
        deleteHashNode(node);
}
void table_remove(HashTable_t* table, Board_t* board){
    int bucket = ((*board).hash)%((*table).nBuckets);
    if((*table).buckets[bucket] != NULL){
        (*table).buckets[bucket] = node_remove(
            (*table).buckets[bucket], board
        );
    }
}
int table_contains(HashTable_t* table, Board_t* board){
    int bucket = ((*board).hash)%((*table).nBuckets);
    if((*table).buckets[bucket] == NULL)
        return 0;
    else
        return node_contains((*table).buckets[bucket], board);
}
void clear(HashTable_t* table){
    int i;
    for(i=0; i<(*table).nBuckets; i++){
        if((*table).buckets[i] != NULL){
            deleteHashNode((*table).buckets[i]);
            (*table).buckets[i] = NULL;
        }
    }
}
void printHashTable(HashTable_t* table){
    printf("### Hash Table ###\n");
    int i;
    for(i=0; i<(*table).nBuckets; i++){
        if((*table).buckets[i] != NULL)
            printHashNode((*table).buckets[i]);
    }
}
