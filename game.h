#pragma once

#define row 9
#define col 9
#define mine_count 10

#define rows (row + 2)
#define cols (col + 2)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


// 初始化棋盘
void initboard(char board[rows][cols], int a, int b, char set);

// 打印棋盘
void display_game(char board[rows][cols], int a, int b);

// 布置雷
void setgame(char board[rows][cols], int a, int b);

// 排查雷、标记雷并显示用时
void findmind(char mine[rows][cols], char show[rows][cols], int a, int b);
