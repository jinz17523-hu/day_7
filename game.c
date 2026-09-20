#include "game.h"

void initboard(char board[rows][cols], int a, int b, char set)
{
	int x = 0;
	int y = 0;

	for (x = 0; x < a; x++)
	{
		for (y = 0; y < b; y++)
		{
			board[x][y] = set;
		}
	}
}

void display_game(char board[rows][cols], int a, int b)
{
	int x = 0;
	int y = 0;
	int d = 0;

	printf("   ");
	for (d = 1; d <= b; d++)
	{
		printf("%d ", d);
	}
	printf("\n");

	for (x = 1; x <= a; x++)
	{
		printf("%2d ", x);
		for (y = 1; y <= b; y++)
		{
			printf("%c ", board[x][y]);
		}
		printf("\n");
	}
	printf("\n");
}

void setgame(char board[rows][cols], int a, int b)
{
	int count = mine_count;

	while (count)
	{
		int x = rand() % a + 1;
		int y = rand() % b + 1;

		if (board[x][y] == '0')
		{
			board[x][y] = '1';
			count--;
		}
	}
}

static int getminecount(char mine[rows][cols], int x, int y)
{
	int dx = 0;
	int dy = 0;
	int count = 0;

	for (dx = -1; dx <= 1; dx++)
	{
		for (dy = -1; dy <= 1; dy++)
		{
			if ((dx != 0 || dy != 0) && mine[x + dx][y + dy] == '1')
			{
				count++;
			}
		}
	}

	return count;
}

static void expand_blank_area(char mine[rows][cols], char show[rows][cols], int x, int y, int a, int b)
{
	int dx = 0;
	int dy = 0;
	int count = 0;

	if (x < 1 || x > a || y < 1 || y > b)
	{
		return;
	}

	if (show[x][y] != '*' || mine[x][y] == '1')
	{
		return;
	}

	count = getminecount(mine, x, y);
	show[x][y] = (char)(count + '0');

	if (count != 0)
	{
		return;
	}

	for (dx = -1; dx <= 1; dx++)
	{
		for (dy = -1; dy <= 1; dy++)
		{
			if (dx != 0 || dy != 0)
			{
				expand_blank_area(mine, show, x + dx, y + dy, a, b);
			}
		}
	}
}

static int is_win(char show[rows][cols], int a, int b)
{
	int x = 0;
	int y = 0;
	int unopened = 0;

	for (x = 1; x <= a; x++)
	{
		for (y = 1; y <= b; y++)
		{
			if (show[x][y] == '*' || show[x][y] == 'F')
			{
				unopened++;
			}
		}
	}

	return unopened == mine_count;
}

static void clear_input_buffer(void)
{
	int ch = 0;

	while ((ch = getchar()) != '\n' && ch != EOF)
	{
	}
}

void findmind(char mine[rows][cols], char show[rows][cols], int a, int b)
{
	int action = 0;
	int x = 0;
	int y = 0;
	time_t start_time = time(NULL);

	while (1)
	{
		long elapsed = (long)difftime(time(NULL), start_time);

		printf("已用时：%ld 秒\n", elapsed);
		printf("请选择操作（1.排查  2.标记/取消标记）：");
		if (scanf("%d", &action) != 1)
		{
			printf("输入无效，请输入数字。\n");
			clear_input_buffer();
			continue;
		}

		if (action != 1 && action != 2)
		{
			printf("操作无效，请输入 1 或 2。\n");
			continue;
		}

		printf("请输入坐标（行 列）：");
		if (scanf("%d%d", &x, &y) != 2)
		{
			printf("输入无效，请输入两个数字。\n");
			clear_input_buffer();
			continue;
		}

		if (x < 1 || x > a || y < 1 || y > b)
		{
			printf("坐标超出棋盘范围，请重新输入。\n");
			continue;
		}

		if (action == 2)
		{
			if (show[x][y] == '*')
			{
				show[x][y] = 'F';
				printf("已标记坐标（%d，%d）。\n", x, y);
			}
			else if (show[x][y] == 'F')
			{
				show[x][y] = '*';
				printf("已取消坐标（%d，%d）的标记。\n", x, y);
			}
			else
			{
				printf("该坐标已经排查过，不能标记。\n");
			}

			display_game(show, a, b);
			continue;
		}

		if (show[x][y] == 'F')
		{
			printf("该坐标已被标记，请先取消标记。\n");
			continue;
		}

		if (show[x][y] != '*')
		{
			printf("该坐标已经被排查过，不用重复排查。\n");
			continue;
		}

		if (mine[x][y] == '1')
		{
			printf("很遗憾，你踩到雷了！总用时：%ld 秒\n", (long)difftime(time(NULL), start_time));
			display_game(mine, a, b);
			break;
		}

		expand_blank_area(mine, show, x, y, a, b);
		display_game(show, a, b);

		if (is_win(show, a, b))
		{
			printf("恭喜你，排雷成功！总用时：%ld 秒\n", (long)difftime(time(NULL), start_time));
			break;
		}
	}
}
