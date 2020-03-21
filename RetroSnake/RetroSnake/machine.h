#include "snake.h"
using namespace std;


bool check(point snake[5][100], int len[5], int t, GamePanel gp, int direction)
{
	if (snake[t][1].y == gp.m && direction == 1) return false;
	if (snake[t][1].y == 2 && direction == 2) return false;
	if (snake[t][1].x == 1 && direction == 3) return false;
	if (snake[t][1].x == gp.n && direction == 4) return false;
	if (direction == 0) {	//下
		if (gp.panel[snake[t][1].x + 1][snake[t][1].y] == 2)
			return false;
		for (int i = 0; i < len[1 - t]; ++i) {
			if (snake[t][1].x + 1 == snake[1 - t][i].x && snake[t][1].y == snake[1 - t][i].y)
				return false;
		}
		for (int i = 0; i < len[t]; ++i) {
			if (snake[t][1].x + 1 == snake[t][i].x && snake[t][1].y == snake[t][i].y)
				return false;
		}
		return true;
	}
	else if (direction == 1) {	//右	
		if (gp.panel[snake[t][1].x][snake[t][1].y + 2] == 2)
			return false;
		for (int i = 0; i < len[1 - t]; ++i) {
			if (snake[t][1].x == snake[1 - t][i].x && snake[t][1].y + 2 == snake[1 - t][i].y)
				return false;
		}
		for (int i = 0; i < len[t]; ++i) {
			if (snake[t][1].x == snake[t][i].x && snake[t][1].y + 2 == snake[t][i].y)
				return false;
		}
		return true;
	}
	else if (direction == 2) {	//左	
		if (gp.panel[snake[t][1].x][snake[t][1].y - 2] == 2)
			return false;
		for (int i = 0; i < len[1 - t]; ++i) {
			if (snake[t][1].x == snake[1 - t][i].x && snake[t][1].y - 2 == snake[1 - t][i].y)
				return false;
		}
		for (int i = 0; i < len[t]; ++i) {
			if (snake[t][1].x == snake[t][i].x && snake[t][1].y - 2 == snake[t][i].y)
				return false;
		}
		return true;
	}
	else if (direction == 3) {	//上
		if (gp.panel[snake[t][1].x - 1][snake[t][1].y] == 2)
			return false;
		for (int i = 0; i < len[1 - t]; ++i) {
			if (snake[t][1].x - 1 == snake[1 - t][i].x && snake[t][1].y == snake[1 - t][i].y)
				return false;
		}
		for (int i = 0; i < len[t]; ++i) {
			if (snake[t][1].x - 1 == snake[t][i].x && snake[t][1].y == snake[t][i].y)
				return false;
		}
		return true;
	}
	else {
		if (gp.obliqueowner[t] == 0) {
			return false;
		}
		else {

		}
	}
	//将你的check函数体放在此处，并删去下面示例代码
	if (snake[t][1].y == gp.m && direction == 1) return false;
	if (snake[t][1].y == 2 && direction == 2) return false;
	return true;
}

void initial(int map[1200][1200], GamePanel& gp,point snake[5][100]) {
	for (int i = 0; i < gp.n * gp.m / 2; ++i) {
		for (int j = 0; j < gp.n * gp.m / 2; ++j) {
			if (i == j) map[i][j] = 0;
			map[i][j] = -1;
			if (i / gp.n != 0 && i / gp.n == j / gp.n && i % gp.n == j + 1 && gp.panel[2 * (i / gp.n + 1) - 2][i % gp.n + 1] == 0) {	//下方
				map[i][j] = 1;
			}
			else if (i / gp.n != 0 && i / gp.n == j / gp.n && i % gp.n == j + 1 && gp.panel[2 * (i / gp.n + 1) - 2][i % gp.n + 1] == 2) {	//下方
				map[i][j] = -1;
			}
			if (i / gp.n != gp.m / 2 && i / gp.n == j / gp.n && i % gp.n == j - 1 && gp.panel[2 * (i / gp.n + 1) + 2][i % gp.n + 1] == 0) {	//上方
				map[i][j] = 1;
			}
			else if (i / gp.n != gp.m / 2 && i / gp.n == j / gp.n && i % gp.n == j - 1 && gp.panel[2 * (i / gp.n + 1) - 2][i % gp.n + 1] == 2) {	//上方
				map[i][j] = -1;
			}
			if (i % gp.n != 0 && i / gp.n - 1 == j / gp.n && i % gp.n == j && gp.panel[2 * (i / gp.n + 1)][i % gp.n] == 0) {	//左边
				map[i][j] = 1;
			}
			else if (i % gp.n != 0 && i / gp.n - 1 == j / gp.n && i % gp.n == j && gp.panel[2 * (i / gp.n + 1) - 2][i % gp.n + 1] == 2) {	//左方
				map[i][j] = -1;
			}
			if (i % gp.n != gp.n && i / gp.n + 1 == j / gp.n && i % gp.n == j && gp.panel[2 * (i / gp.n + 1)][i % gp.n + 2] == 0) {	//右边
				map[i][j] = 1;
			}
			else if (i % gp.n != gp.n && i / gp.n + 1 == j / gp.n && i % gp.n == j && gp.panel[2 * (i / gp.n + 1) - 2][i % gp.n + 1] == 2) {	//右方
				map[i][j] = -1;
			}

		}
	}
	return;
}

void AllLength(int n,int map[1200][1200]) {
	int A[1200][1200];
	int path[1200][1200];
	int max=9999;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			A[i][j] = map[i][j];
			if (i != j && A[i][j] < max) {
				path[i][j] = i;
			}
			else {
				path[i][j] = -1;
			}
		}
	}
	for (int k = 0; k < n; ++k) {
		for (int i = 0; i < n; ++i) {
			if (i != k) {
				for (int j = 0; j < n; ++j) {
					if (j != k && j != i && A[i][k] < max && A[k][j] < max && A[i][j] + A[k][j] < A[i][j]) {
						A[i][j] = A[i][k] + A[k][j];
						path[i][j] = path[k][j];
					}
				}
			}
		}
	}
}

int machine_move(point snake[5][100], int len[5], int direct[5], int t, GamePanel gp)
{
	int map[1200][1200];
	initial(map, gp, snake);
	AllLength(gp.n * gp.m / 2, map);
	//将你的check函数体放在此处，并删去下面示例代码
	if (t == 0) return 2;
	else return 1;
}
