#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "constants.h"
#include "zobrist.h"
#include "board.h"
#include "hash.h"
#include "search.h"

extern int TOTAL_SEARCH_NODES;
SearchNode_t* newSearchNode(Board_t* board, int depth, SearchNode_t* parent){
    TOTAL_SEARCH_NODES++;
	SearchNode_t* node = (SearchNode_t*) malloc(sizeof(SearchNode_t));
	(*node).state = board;
	(*node).parent = parent;
	(*node).depth = depth;
	(*node).children = NULL;
    return node;
}
void deleteSearchNodeChildren(SearchNode_t* node, HashTable_t* visited){
	if((*node).children != NULL){
		int i;
		for(i = 0; i < (*node).nChildren; i++)
            if((*node).children[i]!=NULL)
                deleteSearchNode((*node).children[i], visited);
        free((*node).children);
        (*node).children = NULL;
	}
}
void deleteSearchNode(SearchNode_t* node, HashTable_t* visited){
    TOTAL_SEARCH_NODES--;
    deleteSearchNodeChildren(node, visited);
	table_remove(visited, (*node).state);
	deleteBoard((*node).state);
	free(node);
}
void expand(SearchNode_t* node, HashTable_t* visited){
    assert((*node).children==NULL);
	int nChildren = 0;
	Board_t* children[4];
	Board_t* from = (*node).state;
	Board_t* child;
	//directions: up, down, left, right
	int drs[] = {-1,1,0,0};
	int dcs[] = {0,0,-1,1};
	int i,nr,nc;
	for(i = 0; i < 4; i++){ //for each direction
		nr = (*from).zero_r+drs[i];
		nc = (*from).zero_c+dcs[i];
		if(nr>=0 && nr<BOARD_SIZE && nc>=0 && nc<BOARD_SIZE){ //if the move isnt out of bounds
			child = cloneBoard(from);
			move(child,drs[i],dcs[i]);
			if(table_contains(visited, child))
				deleteBoard(child);
			else{
				put(visited, child);
				children[nChildren++] = child;
			}
		}
	}
	(*node).nChildren = nChildren;
	(*node).children = (SearchNode_t**)malloc(sizeof(SearchNode_t*)*nChildren);
	for(i = 0; i < nChildren; i++)
		(*node).children[i] = newSearchNode(children[i], (*node).depth+1, node);
}
void prune_nonancestors(SearchNode_t* node, HashTable_t* visited){
	if((*node).parent == NULL)
		return;
	//kill all siblings and their decendants (god that's brutal)
	SearchNode_t* parent = (*node).parent;
	int i;
	for(i = 0; i < (*parent).nChildren; i++){
		if((*parent).children[i]!=NULL && (*parent).children[i]!=node)
			deleteSearchNode((*parent).children[i], visited);
	}
	free((*parent).children);
	(*parent).children = (SearchNode_t**)malloc(sizeof(SearchNode_t*));
	(*parent).nChildren = 1;
	(*parent).children[0] = node;
	prune_nonancestors(parent, visited);
}
void printSearchNode(SearchNode_t* node){
	if((*node).parent != NULL)
		printSearchNode((*node).parent);
	printBoard((*node).state);
}
SearchNode_t* df_search(SearchNode_t* start, Board_t* goal, HashTable_t* visited, int depth_limit){
    if(equalsBoard((*start).state, goal)){
        prune_nonancestors(start, visited);
        return start;
    }
    if((*start).depth >= depth_limit){
        return NULL;
    }
    expand(start, visited);
    SearchNode_t* result = NULL;
    int i;
    for(i=0; i<(*start).nChildren; i++){
        result = df_search((*start).children[i], goal, visited, depth_limit);
        if(result==NULL){
            deleteSearchNode((*start).children[i], visited);
            (*start).children[i] = NULL;
        }
        else
            return result;
    }
    return NULL;
}
SearchNode_t* idf_search(SearchNode_t* start, Board_t* goal, HashTable_t* visited, int depth_limit){
    SearchNode_t* result;
    int depth;
    for(depth=1; depth<=depth_limit; depth++){
        deleteSearchNodeChildren(start,visited);
        result = df_search(start, goal, visited, depth);
        if(result!=NULL)
            return result;
    }
    return NULL;
}
