#include "snake.h"
using namespace std;

bool check(point snake[5][100], int len[5], int t, GamePanel gp, int direction)
{
	//转化地图
	int map[38][28];
	for (int i = 0; i < 38; ++i) {
		for (int j = 0; j < 28; ++j) {
			if (gp.panel[j + 1][(i + 1) * 2] == 0)	//空地
				map[i][j] = 0;
			else if (gp.panel[j + 1][(i + 1) * 2] == 2)	//障碍物
				map[i][j] = 2;
		}
	}
	for (int i = 2; i <= len[t]; ++i) {	//自己身体
		int x = snake[t][i].x - 1;
		int y = snake[t][i].y / 2 - 1;
		map[y][x] = 2;
	}
	for (int i = 1; i <= len[abs(t - 1)]; ++i) {	//对方身体
		int x = snake[abs(t - 1)][i].x - 1;
		int y = snake[abs(t - 1)][i].y / 2 - 1;
		map[y][x] = 2;
	}
	for (int i = 0; i < gp.totalfoodnum; ++i) {	//转化食物
		if (gp.panel[gp.food[i].x][gp.food[i].y] == 1) {
			int x = gp.food[i].x - 1;
			int y = gp.food[i].y / 2 - 1;
			map[y][x] = 1;
		}
	}

	int headX = snake[t][1].x;
	int headY = snake[t][1].y;
	headX = headX - 1;
	headY = headY / 2 - 1;
	

	if (direction == 0) {
		if (headX + 1 >= 28)
			return false;
		if (map[headY][headX + 1] == 2)
			return false;
	}
	else if (direction == 1) {
		if (headY + 1 >= 38)
			return false;
		if (map[headY + 1][headX] == 2)
			return false;
	}
	else if (direction == 2) {
		if (headY - 1 < 0)
			return false;
		if (map[headY - 1][headX] == 2)
			return false;
	}
	else if (direction == 3) {
		if (headX - 1 < 0)
			return false;
		if (map[headY][headX - 1] == 2)
			return false;
	}

	


	return true;

	//将你的check函数体放在此处，并删去下面示例代码
	if (snake[t][1].y == gp.m && direction == 1) return false;
	if (snake[t][1].y == 2 && direction == 2) return false;
	return true;
}




void initial(point snake[5][100], int len[5], int t, GamePanel& gp, int map[38][28], int block1[300][300], int block2[300][300], int block3[300][300], int block4[300][300]) {
	int num = gp.n * gp.m / 2;
	int max = 9999;
	//转化地图
	for (int i = 0; i < 38; ++i) {
		for (int j = 0; j < 28; ++j) {
			if (gp.panel[j + 1][(i + 1) * 2] == 0)	//空地
				map[i][j] = 0;
			else if (gp.panel[j + 1][(i + 1) * 2] == 2)	//障碍物
				map[i][j] = 2;
		}
	}
	for (int i = 2; i <= len[t]; ++i) {	//自己身体
		int x = snake[t][i].x - 1;
		int y = snake[t][i].y / 2 - 1;
		map[y][x] = 2;
	}
	for (int i = 1; i <= len[abs(t - 1)]; ++i) {	//对方身体
		int x = snake[abs(t - 1)][i].x - 1;
		int y = snake[abs(t - 1)][i].y / 2 - 1;
		map[y][x] = 2;
	}
	for (int i = 0; i < gp.totalfoodnum; ++i) {	//转化食物
		if (gp.panel[gp.food[i].x][gp.food[i].y] == 1) {
			int x = gp.food[i].x - 1;
			int y = gp.food[i].y / 2 - 1;
			map[y][x] = 1;
		}
	}
	/*
		for (int i = 0; i < 28; ++i) {
			for (int j = 0; j < 38; ++j) {
				cout << map[i][j] << " ";
			}
			cout << endl;
		}

*/		//第一块分割
	for (int i = 0; i < 19; ++i) {
		for (int j = 0; j < 14; ++j) {
			if (map[i][j] == 2) {	//map[i][j]是障碍物
				for (int k = 0; k < 19 * 14; ++k) {
					block1[j + i * 14][k] = max;
				}
				block1[j + i * 14][j + i * 14] = 0;
			}
			else {	//不是障碍物
				block1[j + i * 14][j + i * 14] = 0;
				if (i - 1 >= 0) {	//下方块
					if (map[i - 1][j] == 2) {
						block1[j + i * 14][j + (i - 1) * 14] = max;
					}
					else {
						block1[j + i * 14][j + (i - 1) * 14] = 1;
					}
				}
				if (i + 1 < 19) {	//上方块
					if (map[i + 1][j] == 2) {
						block1[j + i * 14][j + (i + 1) * 14] = max;
					}
					else {
						block1[j + i * 14][j + (i + 1) * 14] = 1;
					}
				}
				if (j - 1 >= 0) {	//左方块
					if (map[i][j - 1] == 2) {
						block1[j + i * 14][(j - 1) + i * 14] = max;
					}
					else {
						block1[j + i * 14][(j - 1) + i * 14] = 1;
					}
				}
				if (j + 1 < 14) {	//右方块
					if (map[i][j + 1] == 2) {
						block1[j + i * 14][(j + 1) + i * 14] = max;
					}
					else {
						block1[j + i * 14][(j + 1) + i * 14] = 1;
					}
				}
				for (int k = 0; k < 19 * 14; ++k) {	//上下左右以外的其他块
					if (block1[j + i * 14][k] != 1)
						block1[j + i * 14][k] = max;
				}
			}
		}
	}
	//第二块分割
	for (int i = 0; i < 19; ++i) {
		for (int j = 14; j < 28; ++j) {
			if (map[i][j] == 2) {	//map[i][j]是障碍物
				for (int k = 0; k < 19 * 14; ++k) {
					block2[j - 14 + i * 14][k] = max;
				}
				block2[j - 14 + i * 14][j - 14 + i * 14] = 0;
			}
			else {	//不是障碍物
				block2[j - 14 + i * 14][j - 14 + i * 14] = 0;
				if (i - 1 >= 0) {	//下方块
					if (map[i - 1][j] == 2) {
						block2[j - 14 + i * 14][j - 14 + (i - 1) * 14] = max;
					}
					else {
						block2[j - 14 + i * 14][j - 14 + (i - 1) * 14] = 1;
					}
				}
				if (i + 1 < 19) {	//上方块
					if (map[i + 1][j] == 2) {
						block2[j - 14 + i * 14][j - 14 + (i + 1) * 14] = max;
					}
					else {
						block2[j - 14 + i * 14][j - 14 + (i + 1) * 14] = 1;
					}
				}
				if (j - 1 >= 14) {	//左方块
					if (map[i][j - 1] == 2) {
						block2[j - 14 + i * 14][(j - 14 - 1) + i * 14] = max;
					}
					else {
						block2[j - 14 + i * 14][(j - 14 - 1) + i * 14] = 1;
					}
				}
				if (j + 1 < 28) {	//右方块
					if (map[i][j + 1] == 2) {
						block2[j - 14 + i * 14][(j - 14 + 1) + i * 14] = max;
					}
					else {
						block2[j - 14 + i * 14][(j - 14 + 1) + i * 14] = 1;
					}
				}
				for (int k = 0; k < 19 * 14; ++k) {	//上下左右以外的其他块
					if (block2[j - 14 + i * 14][k] != 1)
						block2[j - 14 + i * 14][k] = max;
				}
			}
		}
	}
	//第三块分割
	for (int i = 19; i < 38; ++i) {
		for (int j = 0; j < 14; ++j) {
			if (map[i][j] == 2) {	//map[i][j]是障碍物
				for (int k = 0; k < 19 * 14; ++k) {
					block3[j + (i - 19) * 14][k] = max;
				}
				block3[j + (i - 19) * 14][j + (i - 19) * 14] = 0;
			}
			else {	//不是障碍物
				block3[j + (i - 19) * 14][j + (i - 19) * 14] = 0;
				if (i - 1 >= 19) {	//下方块
					if (map[i - 1][j] == 2) {
						block3[j + (i - 19) * 14][j + (i - 19 - 1) * 14] = max;
					}
					else {
						block3[j + (i - 19) * 14][j + (i - 19 - 1) * 14] = 1;
					}
				}
				if (i + 1 < 38) {	//上方块
					if (map[i + 1][j] == 2) {
						block3[j + (i - 19) * 14][j + (i - 19 + 1) * 14] = max;
					}
					else {
						block3[j + (i - 19) * 14][j + (i - 19 + 1) * 14] = 1;
					}
				}
				if (j - 1 >= 0) {	//左方块
					if (map[i][j - 1] == 2) {
						block3[j + (i - 19) * 14][(j - 1) + (i - 19) * 14] = max;
					}
					else {
						block3[j + (i - 19) * 14][(j - 1) + (i - 19) * 14] = 1;
					}
				}
				if (j + 1 < 14) {	//右方块
					if (map[i][j + 1] == 2) {
						block3[j + (i - 19) * 14][(j + 1) + (i - 19) * 14] = max;
					}
					else {
						block3[j + (i - 19) * 14][(j + 1) + (i - 19) * 14] = 1;
					}
				}
				for (int k = 0; k < 19 * 14; ++k) {	//上下左右以外的其他块
					if (block3[j + (i - 19) * 14][k] != 1)
						block3[j + (i - 19) * 14][k] = max;
				}
			}
		}
	}
	//第四块分割
	for (int i = 19; i < 38; ++i) {
		for (int j = 14; j < 28; ++j) {
			if (map[i][j] == 2) {	//map[i][j]是障碍物
				for (int k = 0; k < 19 * 14; ++k) {
					block4[j - 14 + (i - 19) * 14][k] = max;
				}
				block4[j - 14 + (i - 19) * 14][j - 14 + (i - 19) * 14] = 0;
			}
			else {	//不是障碍物
				block4[j - 14 + (i - 19) * 14][j - 14 + (i - 19) * 14] = 0;
				if (i - 1 >= 19) {	//下方块
					if (map[i - 1][j] == 2) {
						block4[j - 14 + (i - 19) * 14][j - 14 + (i - 19 - 1) * 14] = max;
					}
					else {
						block4[j - 14 + (i - 19) * 14][j - 14 + (i - 19 - 1) * 14] = 1;
					}
				}
				if (i + 1 < 38) {	//上方块
					if (map[i + 1][j] == 2) {
						block4[j - 14 + (i - 19) * 14][j - 14 + (i - 19 + 1) * 14] = max;
					}
					else {
						block4[j - 14 + (i - 19) * 14][j - 14 + (i - 19 + 1) * 14] = 1;
					}
				}
				if (j - 1 >= 14) {	//左方块
					if (map[i][j - 1] == 2) {
						block4[j - 14 + (i - 19) * 14][(j - 14 - 1) + (i - 19) * 14] = max;
					}
					else {
						block4[j - 14 + (i - 19) * 14][(j - 14 - 1) + (i - 19) * 14] = 1;
					}
				}
				if (j + 1 < 28) {	//右方块
					if (map[i][j + 1] == 2) {
						block4[j - 14 + (i - 19) * 14][(j - 14 + 1) + (i - 19) * 14] = max;
					}
					else {
						block4[j - 14 + (i - 19) * 14][(j - 14 + 1) + (i - 19) * 14] = 1;
					}
				}
				for (int k = 0; k < 19 * 14; ++k) {	//上下左右以外的其他块
					if (block4[j - 14 + (i - 19) * 14][k] != 1)
						block4[j - 14 + (i - 19) * 14][k] = max;
				}
			}
		}
	}

	return;
}


void AllLength(int n, int block[300][300],int A[300][300],int path[300][300]) {
	int max = 9999;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			A[i][j] = block[i][j];
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
					if (j != k && j != i && A[i][k] < max && A[k][j] < max && A[i][k] + A[k][j] < A[i][j]) {
						A[i][j] = A[i][k] + A[k][j];
						path[i][j] = path[k][j];
					}
				}
			}
		}
	}
	return;
}


int machine_move(point snake[5][100], int len[5], int direct[5], int t, GamePanel gp)
{
	int map[38][28];
	int block1[300][300];
	int block2[300][300];
	int block3[300][300];
	int block4[300][300];
	initial(snake, len, t, gp, map, block1, block2, block3, block4);
	int A[300][300];
	int path[300][300];
	int headX = snake[t][1].x;
	int headY = snake[t][1].y;

	//统计食物数
	int num1 = 0, num2 = 0, num3 = 0, num4 = 0;
	for (int i = 0; i < gp.totalfoodnum; i++) {
		if (gp.panel[gp.food[i].x][gp.food[i].y] == 1) {
			if (gp.food[i].x < 14 && gp.food[i].y < 38)
				num1++;
			else if (gp.food[i].x >= 14 && gp.food[i].y < 38)
				num2++;
			else if (gp.food[i].x < 14 && gp.food[i].y >= 38)
				num3++;
			else if (gp.food[i].x >= 14 && gp.food[i].y >= 38)
				num4++;
		}
	}


	//前往高价值区域
	if (snake[t][1].x < 14 && snake[t][1].y < 38) {
		if (num2 - num1 >= 2 || (num1 == 0 && num2 > 0)) {
			if (check(snake, len, t, gp, 0))
				return 0;
			if (check(snake, len, t, gp, 1))
				return 1;
			if (check(snake, len, t, gp, 2))
				return 2;
			if (check(snake, len, t, gp, 3))
				return 3;
		}
		if (num3 - num1 >= 2 || (num1 == 0 && num3 > 0)) {
			if (check(snake, len, t, gp, 1))
				return 1;
			if (check(snake, len, t, gp, 2))
				return 2;
			if (check(snake, len, t, gp, 3))
				return 3;
			if (check(snake, len, t, gp, 4))
				return 0;
		}
	}
	else if (snake[t][1].x >= 14 && snake[t][1].y < 38) {
		if (num1 - num2 >= 2 || (num2 == 0 && num1 > 0)) {
			if (check(snake, len, t, gp, 3))
				return 3;
			if (check(snake, len, t, gp, 1))
				return 1;
			if (check(snake, len, t, gp, 2))
				return 2;
			if (check(snake, len, t, gp, 0))
				return 0;
		}
		if (num4 - num2 >= 2 || (num2 == 0 && num4 > 0)) {
			if (check(snake, len, t, gp, 1))
				return 1;
			if (check(snake, len, t, gp, 3))
				return 3;
			if (check(snake, len, t, gp, 2))
				return 2;
	//		if (check(snake, len, t, gp, 0))
	//			return 0;
		}
	}
	else if (snake[t][1].x < 14 && snake[t][1].y >= 38) {
		if (num1 - num3 >= 2 || (num3 == 0 && num1 > 0)) {
			if (check(snake, len, t, gp, 2))
				return 2;
			if (check(snake, len, t, gp, 1))
				return 1;
			if (check(snake, len, t, gp, 3))
				return 3;
			if (check(snake, len, t, gp, 0))
				return 0;
		}
		if (num4 - num3 >= 2 || (num3 == 0 && num4 > 0)) {
			if (check(snake, len, t, gp, 0))
				return 0;
			if (check(snake, len, t, gp, 1))
				return 1;
			if (check(snake, len, t, gp, 2))
				return 2;
			if (check(snake, len, t, gp, 3))
				return 3;
		}
	}
	else if (snake[t][1].x >= 14 && snake[t][1].y >= 38) {
		if (num2 - num4 >= 2 || (num4 == 0 && num2 > 0)) {
			if (check(snake, len, t, gp, 2))
				return 2;
			if (check(snake, len, t, gp, 1))
				return 1;
			if (check(snake, len, t, gp, 3))
				return 3;
			if (check(snake, len, t, gp, 0))
				return 0;
		}
		if (num3 - num4 >= 2 || (num4 == 0 && num3 > 0)) {
			if (check(snake, len, t, gp, 3))
				return 3;
			if (check(snake, len, t, gp, 1))
				return 1;
			if (check(snake, len, t, gp, 2))
				return 2;
			if (check(snake, len, t, gp, 0))
				return 0;
		}
	}


	int j = -1;
	if (snake[t][1].x < 14 && snake[t][1].y < 38 && num1 > 0) {
		AllLength(19 * 14, block1, A, path);
		headX = headX - 1;
		headY = headY / 2 - 1;
	

		int min = 9999;
		int target = -1;
		for (int i = 0; i < gp.totalfoodnum; ++i) {
			if (gp.panel[gp.food[i].x][gp.food[i].y] == 1) {
				if (gp.food[i].x - 1 < 14 && (gp.food[i].y / 2 - 1)< 19) {
					if (A[headX + headY * 14][gp.food[i].x - 1 + (gp.food[i].y / 2 - 1) * 14] < min) {
						min = A[headX + headY * 14][gp.food[i].x - 1 + (gp.food[i].y / 2 - 1) * 14];
						target = i;
					}
				}
			}
		}
		if (headX >= 0 && headY >= 0)
		if (target != -1) {
			j = gp.food[target].x - 1 + (gp.food[target].y / 2 - 1) * 14;
			while (path[headX + headY * 14][j] != headX + headY * 14) {
				j = path[headX + headY * 14][j];
			}
		}
	}
	else if (snake[t][1].x >= 14 && snake[t][1].y < 38 && num2 > 0) {
		AllLength(19 * 14, block2, A, path);
		headX = headX - 14 - 1;
		//	if (headY % 2 == 0)
		headY = headY / 2 - 1;
		//	else
		//		headY = headY / 2;

		int min = 9999;
		int target = -1;
		for (int i = 0; i < gp.totalfoodnum; ++i) {
			if (gp.panel[gp.food[i].x][gp.food[i].y] == 1) {
				if (gp.food[i].x - 1 >= 14 && (gp.food[i].y / 2 - 1) < 19) {
					if (A[headX + headY * 14][gp.food[i].x - 14 - 1 + (gp.food[i].y / 2 - 1) * 14] < min) {
						min = A[headX + headY * 14][gp.food[i].x - 14 - 1 + (gp.food[i].y / 2 - 1) * 14];
						target = i;
					}
				}
			}
		}
		if (headX >= 0 && headY >= 0)
		if (target != -1) {
			j = gp.food[target].x - 14 - 1 + (gp.food[target].y / 2 - 1) * 14;
			while (path[headX + headY * 14][j] != headX + headY * 14) {
				j = path[headX + headY * 14][j];
			}
		}
	}
	else if (snake[t][1].x < 14 && snake[t][1].y >= 38 && num3 > 0) {
		AllLength(19 * 14, block3, A, path);
		headX = headX - 1;
		//	if (headY % 2 == 0)
		headY = headY / 2 - 19 - 1;
		//	else
		//		headY = headY / 2 - 19;

		int min = 9999;
		int target = -1;
		for (int i = 0; i < gp.totalfoodnum; ++i) {
			if (gp.panel[gp.food[i].x][gp.food[i].y] == 1) {
				if (gp.food[i].x - 1 < 14 && (gp.food[i].y / 2 - 1) >= 19) {
					if (A[headX + headY * 14][gp.food[i].x - 1 + (gp.food[i].y / 2 - 19 - 1) * 14] < min) {
						min = A[headX + headY * 14][gp.food[i].x - 1 + (gp.food[i].y / 2 - 19 - 1) * 14];
						target = i;
					}
				}
			}
		}
		if (headX >= 0 && headY >= 0)
		if (target != -1) {
			j = gp.food[target].x - 1 + (gp.food[target].y / 2 - 19 - 1) * 14;
			if (j > 0)
				while (path[headX + headY * 14][j] != headX + headY * 14) {
					j = path[headX + headY * 14][j];
				}
		}
	}
	else if (snake[t][1].x >= 14 && snake[t][1].y >= 38 && num4 > 0) {
		AllLength(19 * 14, block4, A, path);
		headX = headX - 14 - 1;
	//		if (headY % 2 == 0)
		headY = headY / 2 - 19 - 1;
	//		else
	//			headY = headY / 2 - 19;

		int min = 9999;
		int target = -1;
		for (int i = 0; i < gp.totalfoodnum; ++i) {
			if (gp.panel[gp.food[i].x][gp.food[i].y] == 1) {
				if (gp.food[i].x - 1 >= 14 && (gp.food[i].y / 2 - 1) >= 19) {
					if (A[headX + headY * 14][gp.food[i].x - 1 + (gp.food[i].y / 2 - 19 - 1) * 14] < min) {
						min = A[headX + headY * 14][gp.food[i].x - 14 - 1 + (gp.food[i].y / 2 - 19 - 1) * 14];
						target = i;
					}
				}
			}
		} 
		if (headX >= 0 && headY >= 0) 
		if (target != -1) {
			j = gp.food[target].x - 14 - 1 + (gp.food[target].y / 2 - 19 - 1) * 14;
			if (j > 0)
				while (path[headX + headY * 14][j] != headX + headY * 14) {
					//	if (j < 0) system("pause");
					j = path[headX + headY * 14][j];
				}
		}
	}
	if (j != -1) {
		int x = j % 14;
		int y = j / 14;
		if (y > headY) {
			if (check(snake, len, t, gp, 1))
				return 1;
		}
		if (y < headY) {
			if (check(snake, len, t, gp, 2))
				return 2;
		}
		if (y == headY && x < headX) {
			if (check(snake, len, t, gp, 3))
				return 3;
		}
		if (y == headY && x > headX) {
			if (check(snake, len, t, gp, 0))
				return 0;
		}
	}

	int d;
	int count = 0;
	do {
		d = rand() % 4;
		count++;
	} while (!check(snake, len, t, gp, d) && count < 200);
	return d;

	//选择价值大的区域
	if (check(snake, len, t, gp, 0))
		return 0;
	if (check(snake, len, t, gp, 1))
		return 1;
	if (check(snake, len, t, gp, 3))
		return 3;
	if (check(snake, len, t, gp, 2))
		return 2;



	//将你的check函数体放在此处，并删去下面示例代码
	if (t == 0) return 2;
	else return 1;
}

