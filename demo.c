#include <stdio.h>

// 棋盘参数
#define ROWS 6
#define COLS 7

// 0=空，1=红色棋子，2=黄色棋子
int board[ROWS][COLS] = {
    {0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 2, 0, 0, 0},
    {0, 0, 1, 1, 2, 0, 0},
    {0, 2, 2, 1, 1, 1, 0},
    {1, 2, 1, 2, 2, 2, 1}
};

// 最后落子位置（行、列）
int last_row = 2;
int last_col = 3;

void print_grid() {
    // 蓝色背景的列索引
    // printf("\033[44m   ");
    for (int col = 0; col < COLS; col++) {
        printf("\033[1;44;37m%2d \033[0m", col);
    }
    printf("\033[0m\n");
    // 蓝色背景的棋盘
    for (int row = 0; row < ROWS; row++) {
        printf("\033[44m");
        for (int col = 0; col < COLS; col++) {
            int cell = board[row][col];
            if (row == last_row && col == last_col) {
                // 最后落子高亮（青色背景，白色字体）
                if (cell == 1)
                    printf("\033[1;46;37m 1 \033[0m");
                else if (cell == 2)
                    printf("\033[1;46;30m 2 \033[0m");
                else
                    printf("\033[1;46;30m * \033[0m");
            } else if (cell == 1) {
                // 红色棋子
                printf("\033[1;41;37m 1 \033[0m");
            } else if (cell == 2) {
                // 黄色棋子
                printf("\033[1;43;30m 2 \033[0m");
            } else {
                // 空格子用蓝色背景
                printf("\033[1;44;37m   \033[0m");
            }
        }
        printf("\033[0m\n");
    }
}

int main() {
    print_grid();
    printf("Player 1 Make your Selection (0-6):\n");
    return 0;
}
