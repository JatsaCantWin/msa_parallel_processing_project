#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <mpi.h>
#include <omp.h>

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

void updateGame(bool localGrid[ROWS][COLS], bool newGrid[ROWS][COLS], int rank, int size) {
    int chunkSize = ROWS / size;
    int startRow = rank * chunkSize;
    int endRow = (rank + 1) * chunkSize;

    #pragma omp parallel for
    for (int i = startRow; i < endRow; ++i) {
        for (int j = 0; j < COLS; ++j) {
            int neighbors = countNeighbors(localGrid, i, j);

            if (localGrid[i][j]) {
                newGrid[i][j] = (neighbors == 2 || neighbors == 3);
            } else {
                newGrid[i][j] = (neighbors == 3);
            }
        }
    }

    MPI_Allgather(MPI_IN_PLACE, chunkSize * COLS, MPI_C_BOOL, newGrid, chunkSize * COLS, MPI_C_BOOL, MPI_COMM_WORLD);

    #pragma omp parallel for
    for (int i = startRow; i < endRow; ++i) {
        for (int j = 0; j < COLS; ++j) {
            localGrid[i][j] = newGrid[i][j];
        }
    }
}

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    bool gameGrid[ROWS][COLS];
    bool newGameGrid[ROWS][COLS];
    bool localGrid[ROWS][COLS];

    initializeGame(gameGrid);

    int num_threads = 1;
    int num_procs = size;

    if (argc >= 3) {
        num_procs = atoi(argv[1]);
        num_threads = atoi(argv[2]);
    }

    MPI_Barrier(MPI_COMM_WORLD);

    const char* omp_num_threads_str = getenv("OMP_NUM_THREADS");
    num_threads = omp_num_threads_str ? atoi(omp_num_threads_str) : num_threads;

    omp_set_num_threads(num_threads);

    double start_time = MPI_Wtime();

    int chunkSize = ROWS / size;
    MPI_Scatter(gameGrid, chunkSize * COLS, MPI_C_BOOL, localGrid, chunkSize * COLS, MPI_C_BOOL, 0, MPI_COMM_WORLD);

    for (int step = 1; step <= STEPS; ++step) {
        updateGame(localGrid, newGameGrid, rank, size);
    }

    MPI_Gather(localGrid, chunkSize * COLS, MPI_C_BOOL, gameGrid, chunkSize * COLS, MPI_C_BOOL, 0, MPI_COMM_WORLD);

    double end_time = MPI_Wtime();
    double elapsed_time = end_time - start_time;

    if (rank == 0) {
        printf("Execution time for %d steps with %d processes and %d threads: %f seconds\n", STEPS, num_procs, num_threads, elapsed_time);
    }

    MPI_Finalize();

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
