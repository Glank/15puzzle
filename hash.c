#include <stdlib.h>
#include "constants.h"
#include "zobrist.h"
#include "board.h"
#include "hash.h"

//#### HashNode_t Methods ####
HashNode_t* newHashNode(Board_t* load){
    HashNode_t* node = (HashNode_t*) malloc(sizeof(HashNode_t));
    (*node).load = load;
    (*node).next = NULL;
    return node;
}
//Doesn't free the boards!
void deleteHashNode(HashNode_t* node){
    if((*node).next != NULL)
        deleteHashNode((*node).next);
    free(node);
}
void append(HashNode_t* node, HashNode_t* other){
    if((*node).next == NULL)
        (*node).next = other;
    else
        append((*node).next, other);
}
int node_contains(HashNode_t* node, Board_t* load){
    if(equalsBoard((*node).load, load))
        return 1;
    else if((*node).next != NULL)
        return node_contains((*node).next, load);
    return 0;
}

//#### HashTable_t Methods ####
HashTable_t* newHashTable(int nBuckets){
    HashTable_t* table = (HashTable_t*) malloc(sizeof(HashTable_t));
    (*table).buckets = (HashNode_t**) malloc(sizeof(HashNode_t*)*nBuckets);
    (*table).nBuckets = nBuckets;
    return table;
}
//doesnt free the tables within!
void deleteHashTable(HashTable_t* table){
    clear(table);
    free((*table).buckets);
    free(table);
}
void put(HashTable_t* table, Board_t* board){
    int bucket = (*board).hash%(*table).nBuckets;
    HashNode_t* node = newHashNode(board);
    if((*table).buckets[bucket] == NULL)
        (*table).buckets[bucket] = node;
    else
        append((*table).buckets[bucket], node);
}
int table_contains(HashTable_t* table, Board_t* board){
    int bucket = (*board).hash%(*table).nBuckets;
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
