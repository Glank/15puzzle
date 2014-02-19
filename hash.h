typedef struct hashNode{
    Board_t* load;
    struct hashNode *next;
} HashNode_t;
HashNode_t* newHashNode(Board_t* load);
void deleteHashNode(HashNode_t* node);
void append(HashNode_t* node, HashNode_t* other);
int node_contains(HashNode_t* node, Board_t* load);

typedef struct hashTable{
    HashNode_t** buckets;
    int size, nBuckets;
} HashTable_t;
HashTable_t* newHashTable(int nBuckets);
void deleteHashTable(HashTable_t* table);
void put(HashTable_t* table, Board_t* board);
int table_contains(HashTable_t* table, Board_t* board);
void clear(HashTable_t* table);

