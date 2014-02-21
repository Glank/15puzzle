#include <stdio.h>
#include <stdlib.h>
#include "constants.h"
#include "zobrist.h"
#include "board.h"

void swap(INT_8 *a, INT_8 *b){
    INT_8 temp = *a;
    *a = *b;
    *b = temp;
}
Board_t* newBoard(){
    Board_t* board = (Board_t*)malloc(sizeof(Board_t));
    int r,c;
    int n = 0;
    int hash = 0;
    for(r=0; r<BOARD_SIZE; r++){
        for(c=0; c<BOARD_SIZE; c++){
            hash = hash^(ZOBRIST_TABLE[r][c][n]);
            (*board).squares[r][c] = n++;
        }
    }
    (*board).zero_r = 0;
    (*board).zero_c = 0;
    (*board).hash = (zob_hash_t) hash;
    return board;
}
void deleteBoard(Board_t* board){
    free(board);
}
int equalsBoard(Board_t* a, Board_t* b){
    if((*a).hash != (*b).hash)
        return 0;
    if((*a).zero_r != (*b).zero_r)
        return 0;
    if((*a).zero_c != (*b).zero_c)
        return 0;
    int r,c;
    for(r=0; r<BOARD_SIZE; r++){
        for(c=0; c<BOARD_SIZE; c++){
            if((*a).squares[r][c] != (*b).squares[r][c])
                return 0;
        }
    }
    return 1;
}
Board_t* cloneBoard(const Board_t* board){
    Board_t* newBoard = (Board_t*)malloc(sizeof(Board_t));
    int r,c;
    for(r=0; r<BOARD_SIZE; r++){
        for(c=0; c<BOARD_SIZE; c++){
            (*newBoard).squares[r][c] = (*board).squares[r][c];
        }
    }
    (*newBoard).zero_r = (*board).zero_r;
    (*newBoard).zero_c = (*board).zero_c;
    (*newBoard).hash = (*board).hash;
    return newBoard;
}
void move(Board_t* board, int dr, int dc){
    int r = (*board).zero_r, c = (*board).zero_c;
    int r2 = r+dr, c2 = c+dc;
    INT_8 *n1,*n2;
    n1 = &((*board).squares[r][c]);
    n2 = &((*board).squares[r2][c2]);
    int hash = (*board).hash;
    hash = hash^ZOBRIST_TABLE[r][c][*n1];
    hash = hash^ZOBRIST_TABLE[r2][c2][*n2];
    hash = hash^ZOBRIST_TABLE[r][c][*n2];
    hash = hash^ZOBRIST_TABLE[r2][c2][*n1];
    swap(n1,n2);
    (*board).zero_r = r2;
    (*board).zero_c = c2;
    (*board).hash = (zob_hash_t) hash;
}
void moveUp(Board_t* board){
    move(board, -1, 0);
}
void moveDown(Board_t* board){
    move(board, 1, 0);
}
void moveLeft(Board_t* board){
    move(board, 0, -1);
}
void moveRight(Board_t* board){
    move(board, 0, 1);
}
void scramble(Board_t* board){
    int times = 100*BOARD_SIZE*BOARD_SIZE;
    scramble_times(board, times);
}
void scramble_times(Board_t* board, int times){
    int i;
    for(i=0; i<times; i++){
        switch(rand()%4){
        case 0: 
            if((*board).zero_r>0)
                moveUp(board);
            break;
        case 1:
            if((*board).zero_r<(BOARD_SIZE-1))
                moveDown(board);
            break;
        case 2: 
            if((*board).zero_c>0)
                moveLeft(board);
            break;
        case 3:
            if((*board).zero_c<(BOARD_SIZE-1))
                moveRight(board);
            break;
        }
    }
}
void printBoard(const Board_t* board){
    int r,c;
    for(r=0; r<BOARD_SIZE; r++){
        for(c=0; c<BOARD_SIZE; c++){
            printf("%d\t", (int)(*board).squares[r][c]);
        }
        printf("\n");
    }
    printf("r:%d, c:%d, hash:%d\n\n",
        (int)(*board).zero_r,
        (int)(*board).zero_c,
        (int)(*board).hash);
}
