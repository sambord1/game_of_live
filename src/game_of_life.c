#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define ROWS 25
#define COLS 80
void initializeGrid(int grid[ROWS][COLS]);
void printGrid(int grid[ROWS][COLS]);
int toroidalIndex(int i, int max);
void updateGrid(int grid[ROWS][COLS], int newGrid[ROWS][COLS]);
void copy(int grid[ROWS][COLS], int newGrid[ROWS][COLS]);
void check_end(int grid[ROWS][COLS], int newGrid[ROWS][COLS], int gen);
void setup();
void getkey(int *time, char c, int gen);

int main() {
    setup();
    int grid[ROWS][COLS];
    initializeGrid(grid);
    int time = 10000000;
    printGrid(grid);
    usleep(time);

    FILE *f;
    f = freopen("/dev/tty", "r", stdin);

    int gen = 0;
    while (1) {
        clear();
        printGrid(grid);
        refresh();
        int newGrid[ROWS][COLS] = {0};
        updateGrid(grid, newGrid);
        gen++;
        //check_end(grid, newGrid, gen);
        copy(grid, newGrid);
        char c = getch();
        getkey(&time, c, gen);
        usleep(time);
    }
    fclose(f);
    endwin();
    return 0;
}

void initializeGrid(int grid[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            grid[i][j] = 0;
        }
    }

    for (int i = ROWS / 2 - 2; i < ROWS / 2 + 3; i++) {
        for (int j = COLS / 2 - 2; j < COLS / 2 + 3; j++) {
            scanf("%d", &grid[i][j]);
        }
    }
}

//вывод матрицы на экран с * и пробелами в зависимости от значения
void printGrid(int grid[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (grid[i][j] == 1) {
                printw("*");
                // refresh();
            } else {
                printw(" ");
                // refresh();
            }
        }
        printw("\n");
        // refresh();
    }
}

int toroidalIndex(int i, int max) {
    int a;
    if (i < 0)
        a = max - 1;
    else if (i >= max)
        a = 0;
    else
        a = i;
    return a;
}

void updateGrid(int grid[ROWS][COLS], int newGrid[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            int neighbours = 0;
            for (int x = -1; x <= 1; x++) {
                for (int y = -1; y <= 1; y++) {
                    if (x != 0 || y != 0) {
                        int ni = toroidalIndex(i + x, ROWS);
                        int nj = toroidalIndex(j + y, COLS);
                        if (grid[ni][nj] == 1) {
                            neighbours++;
                        }
                    }
                }
            }

            if (grid[i][j] == 1 && (neighbours == 3 || neighbours == 2)) {
                newGrid[i][j] = 1;
            } else if (grid[i][j] == 0 && neighbours == 3) {
                newGrid[i][j] = 1;
            } else {
                newGrid[i][j] = 0;
            }
        }
    }
    printw("A - speed up\nZ - speed down\nQ - exit\n");
}

void copy(int grid[ROWS][COLS], int newGrid[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            grid[i][j] = newGrid[i][j];
        }
    }
}

void check_end(int grid[ROWS][COLS], int newGrid[ROWS][COLS], int gen) {
    int count = 0;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (grid[i][j] == newGrid[i][j]) {
                count++;
            }
        }
    }
    if (count == 80 * 25) {
        printf("Игра окончена. Количество поколений - %d.", gen);
        exit(1);
    }
}

void setup() {
    initscr();
    noecho();
    keypad(stdscr, 1);
    curs_set(0);
    nodelay(stdscr, 1);
    cbreak();
}

void getkey(int *time, char c, int gen) {
    if (c == 'z') {
        if (*time > 200000) {
            *time = 200000;
        } else {
            *time *= 2;
        }
    }
    if (c == 'a') {
        if (*time < 1) {
            *time = 1;
        } else {
            *time /= 2;
        }
    }
    if (c == 'q') {
        printf("Игра окончена. Количество поколений - %d.", gen);
        exit(1);
    }
}
