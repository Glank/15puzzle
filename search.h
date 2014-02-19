typedef struct searchNode{
    Board_t* state;
    struct searchNode *parent;
    struct searchNode **children;
    int nChildren;
    int depth;
} SearchNode_t;
SearchNode_t* newSearchNode(Board_t* board, int depth, SearchNode_t* parent);
//deletes node and state, and removes state from visited table
void deleteSearchNode(SearchNode_t* node, HashTable_t* visited);
void expand(SearchNode_t* node, HashTable_t* visited);
void prune_nonancestors(SearchNode_t* node, HashTable_t* visited);
void printSearchNode(SearchNode_t* node);

//return a non-ancestor-pruned leaf node at the goal state or NULL
SearchNode_t* df_search(SearchNode_t* start, Board_t* goal, HashTable_t* visited, int depth_limit);
SearchNode_t* idf_search(SearchNode_t* start, Board_t* goal, HashTable_t* visited, int depth_limit);
