typedef struct board{
    INT_8 squares[BOARD_SIZE][BOARD_SIZE];
    INT_8 zero_r;
    INT_8 zero_c;
    zob_hash_t hash;
} Board_t;
Board_t* newBoard();
void deleteBoard(Board_t* board);
Board_t* cloneBoard(const Board_t* board);
int equalsBoard(Board_t* a, Board_t* b);
void printBoard(const Board_t* board);
void move(Board_t* board, int dr, int dc);
void moveUp(Board_t* board);
void moveDown(Board_t* board);
void moveLeft(Board_t* board);
void moveRight(Board_t* board);
void scramble(Board_t* board);
void scramble_times(Board_t* board, int times);
