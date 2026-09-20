#include "game.h"

static void game(void)
{
	char show[rows][cols];
	char mine[rows][cols];

	initboard(show, rows, cols, '*');
	initboard(mine, rows, cols, '0');
	setgame(mine, row, col);

	display_game(show, row, col);
	findmind(mine, show, row, col);
}

static void menu(void)
{
	printf("----------------------\n");
	printf("------- 1.start ------\n");
	printf("------- 0.exit  ------\n");
	printf("----------------------\n");
}

int main(void)
{
	int input = 0;

	srand((unsigned int)time(NULL));
	do
	{
		menu();
		printf("请选择：");
		if (scanf("%d", &input) != 1)
		{
			printf("输入无效，游戏结束。\n");
			return 1;
		}

		switch (input)
		{
		case 1:
			game();
			break;
		case 0:
			printf("游戏结束\n");
			break;
		default:
			printf("你输入错了，请重新输入\n");
			break;
		}
	} while (input);

	return 0;
}
