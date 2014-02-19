#include <stdlib.h>
#include "constants.h"
#include "zobrist.h"

void init_zobrist(){
    srand(12345);
    int r,c,n;
    int n_bound = BOARD_SIZE*BOARD_SIZE;
    int mod = (1<<(sizeof(zob_hash_t)*8));
    for(r=0; r<BOARD_SIZE; r++){
        for(c=0; c<BOARD_SIZE; c++){
            for(n=0; n<n_bound; n++){
                ZOBRIST_TABLE[r][c][n] = (zob_hash_t)(rand()%mod);
            }
        }
    }
}
