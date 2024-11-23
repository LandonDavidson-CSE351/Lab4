/*
 * CSE 351 Lab 4 (Caches and Cache-Friendly Code)
 * Part 2 - Optimizing Matrix Transpose
 *
 * Name(s):  Landon Davidson
 * NetID(s): landond
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[M][N], int B[N][M]);
 * and compute B = A^T.
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1 KiB direct mapped cache with a block size of 32 bytes.
 */

#include <stdio.h>
#include "support/cachelab.h"

int is_transpose(int M, int N, int A[M][N], int B[N][M]);


/*
 * transpose_submit - This is the transpose function that you will be graded
 *     on. Do not change the description string "Transpose submission", as the
 *     driver searches for that string to identify the transpose function to be
 *     graded.
 */
#define BLOCK_SIZE_32 8
#define BLOCK_SIZE_64 4
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[M][N], int B[N][M]) {
    if (M != N) return;
    if (M == 32) {
        for (int x_block = 0; x_block < M / BLOCK_SIZE_32; x_block++) {
            for (int y_block = 0; y_block < N / BLOCK_SIZE_32; y_block++) {
                for (int i = x_block * BLOCK_SIZE_32; i < (x_block + 1) * BLOCK_SIZE_32; i++) {
                    int Ai[BLOCK_SIZE_32];
                    for (int element = 0; element < BLOCK_SIZE_32; element++) {
                        Ai[element] = A[i][element + y_block * BLOCK_SIZE_32];
                    }
                    for (int j = y_block * BLOCK_SIZE_32; j < (y_block + 1) * BLOCK_SIZE_32; j++) {
                        B[j][i] = Ai[j % BLOCK_SIZE_32];
                    }
                }
            }
        }
    } else if (M == 64) {
        for (int x_block = 0; x_block < M / BLOCK_SIZE_64; x_block++) {
            for (int y_block = 0; y_block < N / BLOCK_SIZE_64; y_block++) {
                for (int i = x_block * BLOCK_SIZE_64; i < (x_block + 1) * BLOCK_SIZE_64; i++) {
                    int Ai[BLOCK_SIZE_64];
                    for (int element = 0; element < BLOCK_SIZE_64; element++) {
                        Ai[element] = A[i][element + y_block * BLOCK_SIZE_64];
                    }
                    for (int j = y_block * BLOCK_SIZE_64; j < (y_block + 1) * BLOCK_SIZE_64; j++) {
                        B[j][i] = Ai[j % BLOCK_SIZE_64];
                    }
                }
            }
        }
    }

}


// You can define additional transpose functions below. We've defined a simple
// one below to help you get started.

/*
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[M][N], int B[N][M]) {
    int i, j, tmp;

    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }

}


/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions() {
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc);

    /* Register any additional transpose functions */
    registerTransFunction(trans, trans_desc);

}


/*
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[M][N], int B[N][M]) {
    int i, j;

    for (i = 0; i < M; i++) {
        for (j = 0; j < N; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}
