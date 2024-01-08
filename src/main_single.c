#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define ROWS 1000
#define COLS 1000
#define STEPS 100

void initializeGame(bool grid[ROWS][COLS]) {
    srand(time(NULL));
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            grid[i][j] = rand() % 2;
        }
    }
}

void printGame(bool grid[ROWS][COLS]) {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            printf("%c ", grid[i][j] ? 'X' : '.');
        }
        printf("\n");
    }
}

int countNeighbors(bool grid[ROWS][COLS], int row, int col) {
    int count = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) continue;
            int newRow = row + i;
            int newCol = col + j;

            if (newRow >= 0 && newRow < ROWS && newCol >= 0 && newCol < COLS) {
                count += grid[newRow][newCol];
            }
        }
    }
    return count;
}

void updateGame(bool grid[ROWS][COLS]) {
    bool newGrid[ROWS][COLS];

    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            int neighbors = countNeighbors(grid, i, j);

            if (grid[i][j]) {
                newGrid[i][j] = (neighbors == 2 || neighbors == 3);
            } else {
                newGrid[i][j] = (neighbors == 3);
            }
        }
    }

    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            grid[i][j] = newGrid[i][j];
        }
    }
}

int main() {
    bool gameGrid[ROWS][COLS];

    initializeGame(gameGrid);
    printf("Initial state of the game:\n");
    // printGame(gameGrid);

    clock_t start_time = clock();

    for (int step = 1; step <= STEPS; ++step) {
        updateGame(gameGrid);
    }

    clock_t end_time = clock();
    double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    // printf("\nFinal state of the game:\n");
    // printGame(gameGrid);

    printf("Execution time for %d steps: %f seconds\n", STEPS, elapsed_time);

    FILE *file = fopen("result.txt", "w");
    if (file != NULL) {
        for (int i = 0; i < ROWS; ++i) {
            for (int j = 0; j < COLS; ++j) {
                fprintf(file, "%c ", gameGrid[i][j] ? 'X' : '.');
            }
            fprintf(file, "\n");
        }
        fprintf(file, "Execution time for %d steps: %f seconds\n", STEPS, elapsed_time);
        fclose(file);
    } else {
        fprintf(stderr, "Error while saving to the file.\n");
        return EXIT_FAILURE;
    }

    return 0;
}
