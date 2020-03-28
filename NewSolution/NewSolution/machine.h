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
	else if (direction == 4) {
		if (headX + 1 >= 28)
			return false;
		if (map[headY + 1][headX + 1] == 2)
			return false;
		if (map[headY + 1][headX] == 2 && map[headY][headX + 1] == 2)
			return false;
	}
	else if (direction == 5) {
		if (headX - 1 < 0)
			return false;
		if (map[headY + 1][headX - 1] == 2)
			return false;
		if (map[headY + 1][headX] == 2 && map[headY][headX - 1] == 2)
			return false;
	}
	else if (direction == 6) {
		if (headX - 1 < 0)
			return false;
		if (map[headY - 1][headX - 1] == 2)
			return false;
		if (map[headY - 1][headX] == 2 && map[headY][headX - 1] == 2)
			return false;
	}
	else if (direction == 7) {
		if (headX + 1 >= 28)
			return false;
		if (map[headY - 1][headX + 1] == 2)
			return false;
		if (map[headY - 1][headX] == 2 && map[headY][headX + 1] == 2)
			return false;
	}

	return true;
}


void calculate(point snake[5][100], int len[5], int t, GamePanel& gp, int heatPanel[50][100]) {
	//初始化
	for (int i = 0; i < 28; ++i) {
		for (int j = 0; j < 38; ++j) {
			heatPanel[i][j] = 0;
		}
	}

	//转化地图
	for (int i = 0; i < gp.totalfoodnum; ++i) {	//转化食物
		if (gp.panel[gp.food[i].x][gp.food[i].y] == 1) {
			int x = gp.food[i].x - 1;
			int y = gp.food[i].y / 2 - 1;
			heatPanel[x][y] += 500;
			for (int k = x - 3; k < x + 3; ++k) {
				for (int p = y - 3; p < y + 3; p++) {
					if (gp.panel[k + 1][(p + 1) * 2] != 2) {
						if (k >= 0 && k < 28 && p >= 0 && p < 38) {
							heatPanel[k][p] += 30;
						}
					}
				}
			}
			for (int k = x - 7; k < x + 7; ++k) {
				for (int p = y - 7; p < y + 7; p++) {
					if (gp.panel[k + 1][(p + 1) * 2] == 1) {
						if (k >= 0 && k < 28 && p >= 0 && p < 38) {
							heatPanel[k][p] += 50;
						}
					}
				}
			}
		}
	}
	for (int i = 0; i < 28; ++i) {
		for (int j = 0; j < 38; ++j) {
			if (gp.panel[i + 1][(j + 1) * 2] == 2) {	//障碍物
				heatPanel[i][j] -= 1000;
				for (int k = i - 1; k < i + 1; ++k) {
					for (int p = j - 1; p < j + 1; p++) {
						if (k >= 0 && k < 28 && p >= 0 && p < 38) {
							heatPanel[k][p] -= 35;	//	
						}
					}
				}
			}
		}
	}

	//边框
	for (int i = 0; i < 28; ++i) {
		for (int j = 0; j < 38; ++j) {
			if (i == 0 || j == 0) {
				if (gp.panel[i + 1][(j + 1) * 2] != 1)
					heatPanel[i][j] -= 35;	//
			}
		}
	}

	//转化加速道具
	for (int i = 0; i < 38; ++i) {
		for (int j = 0; j < 28; ++j) {
			if (gp.panel[i + 1][(j + 1) * 2] == 3)
				heatPanel[i][j] += 650;
		}
	}

	//转化斜走道具
	for (int i = 0; i < gp.obliquenum; ++i) {
		if (gp.panel[gp.obliqueprops[i].x][gp.obliqueprops[i].y] == 4) {
			int x = gp.obliqueprops[i].x - 1;
			int y = gp.obliqueprops[i].y / 2 - 1;
			heatPanel[x][y] += 5000;
			for (int k = x - 3; k < x + 3; ++k) {
				for (int p = y - 3; p < y + 3; p++) {
					if (gp.panel[k + 1][(p + 1) * 2] == 1) {
						if (k >= 0 && k < 28 && p >= 0 && p < 38) {
							heatPanel[k][p] += 50;
						}
					}
				}
			}
		}
	}

	for (int i = 1; i <= len[t]; ++i) {	//自己身体
		int x = snake[t][i].x - 1;
		int y = snake[t][i].y / 2 - 1;
		heatPanel[x][y] -= 1000;
		for (int k = x - 1; k < x + 1; ++k) {
			for (int p = y - 1; p < y + 1; p++) {
				if (k >= 0 && k < 28 && p >= 0 && p < 38) {
					heatPanel[k][p] -= 35;	//
				}
			}
		}
		if (i == 1) {
			for (int k = x - 5; k < x + 5; ++k) {
				for (int p = y - 5; p < y + 5; p++) {
					if (gp.panel[k + 1][(p + 1) * 2] == 1 || gp.panel[k + 1][(p + 1) * 2] == 4)
						if (k >= 0 && k < 28 && p >= 0 && p < 38) {
							int headX = snake[t][1].x - 1;
							int headY = snake[t][1].y / 2 - 1;
							int n;
							if (gp.obliqueowner[t] == 1) {
								n = sqrt((headX - k) * (headX - k) + (headY - p) * (headY - p));
							}
							else {
								n = abs(headX - k) + abs(headY - p);
							}
							heatPanel[k][p] += (10 - n) * 100;
						}
				}
			}
		}
	}
	for (int i = 1; i <= len[abs(t - 1)]; ++i) {	//对方身体
		int x = snake[abs(t - 1)][i].x - 1;
		int y = snake[abs(t - 1)][i].y / 2 - 1;
		heatPanel[x][y] -= 1000;
		for (int k = x - 1; k < x + 1; ++k) {
			for (int p = y - 1; p < y + 1; p++) {
				if (k >= 0 && k < 28 && p >= 0 && p < 38) {
					heatPanel[k][p] -= 35;	//
				}
			}
		}
		if (i == 1) {
			for (int k = x - 5; k < x + 5; ++k) {
				for (int p = y - 5; p < y + 5; p++) {
					if (k >= 0 && k < 28 && p >= 0 && p < 38) {
						heatPanel[k][p] -= 50;
					}
				}
			}
		}
	}
	return;
}


int machine_move(point snake[5][100], int len[5], int direct[5], int t, GamePanel gp)
{
	int heatPanel[50][100];
	calculate(snake, len, t, gp, heatPanel);

	int max = -500;
	int targetX = 0;
	int targetY = 0;
	for (int i = 0; i < 28; ++i) {	//寻找目标
		for (int j = 0; j < 38; ++j) {
			if (heatPanel[i][j] > max) {
				max = heatPanel[i][j];
				targetX = i;
				targetY = j;
			}
		}
	}

	//寻找路径
	max = -500;
	int nextX = snake[t][1].x;
	int nextY = snake[t][1].y;
	int headX = snake[t][1].x - 1;
	int headY = snake[t][1].y / 2 - 1;
	int next;


	if (gp.obliqueowner[t] == 1) {
		if (headX > targetX&& headY > targetY) {
			if (check(snake, len, t, gp, 6) && heatPanel[nextX - 1 - 1][(nextY - 2) / 2 - 1] > -100)
				return 6;
		}
		else if (headX < targetX && headY < targetY) {
			if (check(snake, len, t, gp, 4) && heatPanel[nextX + 1 - 1][(nextY + 2) / 2 - 1] > -100)
				return 4;
		}
		else if (headX > targetX&& headY < targetY) {
			if (check(snake, len, t, gp, 5) && heatPanel[nextX - 1 - 1][(nextY + 2) / 2 - 1] > -100)
				return 5;
		}
		else if (headX<targetX && headY>targetY) {
			if (check(snake, len, t, gp, 7) && heatPanel[nextX + 1 - 1][(nextY - 2) / 2 - 1] > -100)
				return 7;
		}
	}

	if (headX > targetX) {
		if (gp.panel[headX][(headY + 1) * 2] != 2) {
			next = 3;
			nextX = headX - 1;
			nextY = headY;
		}
		else {
			if (headY > targetY) {
				next = 2;
				nextX = headX;
				nextY = headY - 1;
			}
			else {
				next = 1;
				nextX = headX;
				nextY = headY + 1;
			}
		}
	}
	else if (headX < targetX) {
		if (gp.panel[headX + 2][(headY + 1) * 2] != 2) {
			next = 0;
			nextX = headX + 1;
			nextY = headY;
		}
		else {
			if (headY > targetY) {
				next = 2;
				nextX = headX;
				nextY = headY - 1;
			}
			else {
				next = 1;
				nextX = headX;
				nextY = headY + 1;
			}
		}
	}
	else if (headX == targetX && headY > targetY) {
		if (gp.panel[headX + 1][(headY) * 2] != 2) {
			next = 2;
			nextX = headX;
			nextY = headY - 1;
		}
		else {
			if (gp.panel[headX + 2][(headY + 1) * 2] != 2) {
				next = 0;
				nextX = headX + 1;
				nextY = headY;
			}
			else {
				next = 3;
				nextX = headX - 1;
				nextY = headY;
			}
		}
	}
	else if (headX == targetX && headY < targetY) {
		if (gp.panel[headX + 1][(headY + 2) * 2] != 2) {
			next = 1;
			nextX = headX;
			nextY = headY + 1;
		}
		else {
			if (gp.panel[headX + 2][(headY + 1) * 2] != 2) {
				next = 0;
				nextX = headX + 1;
				nextY = headY;
			}
			else {
				next = 3;
				nextX = headX - 1;
				nextY = headY;
			}
		}
	}
	if (heatPanel[nextX][nextY] > -100 && check(snake, len, t, gp, next))
		return next;

	max = -500;
	if (headX - 1 >= 0) {	//上
		if((snake[t][1].x - 1 - 1 - 1>=0&&heatPanel[snake[t][1].x-1-1-1][snake[t][1].y/2-1]>-500)||
			(snake[t][1].y / 2 - 1 - 1>=0&& snake[t][1].x - 1 - 1>=0&&heatPanel[snake[t][1].x - 1 - 1][snake[t][1].y / 2 - 1-1] > -500)||
			(snake[t][1].x - 1 - 1>=0&& snake[t][1].y / 2 - 1 + 1<38&&heatPanel[snake[t][1].x - 1 - 1][snake[t][1].y / 2 - 1+1] > -500))
			
			if (heatPanel[headX - 1][headY] > max) {
			max = heatPanel[headX - 1][headY];
			nextX = headX - 1;
			nextY = headY;
			next = 3;
		}
	}
	if (headX + 1 < 28) {	//下
		if ((snake[t][1].x - 1 + 1 + 1 < 28 && heatPanel[snake[t][1].x - 1 + 1 + 1][snake[t][1].y / 2 - 1] > -500) ||
			(snake[t][1].y / 2 - 1 - 1 >= 0  && heatPanel[snake[t][1].x - 1 + 1][snake[t][1].y / 2 - 1 - 1] > -500) ||
			(snake[t][1].x - 1 + 1 < 28 && snake[t][1].y / 2 - 1 + 1 < 38 && heatPanel[snake[t][1].x - 1 + 1][snake[t][1].y / 2 - 1 + 1] > -500))

		if (heatPanel[headX + 1][headY] > max) {
			max = heatPanel[headX + 1][headY];
			nextX = headX + 1;
			nextY = headY;
			next = 0;
		}
	}
	if (headY - 1 >= 0) {	//左
		if((snake[t][1].y / 2 - 1 - 1 - 1>=0 && heatPanel[snake[t][1].x - 1][snake[t][1].y / 2 - 1 -1 -1] > -500) ||
			(snake[t][1].y / 2 - 1 - 1 >= 0 && snake[t][1].x - 1 - 1 >= 0 && heatPanel[snake[t][1].x - 1 - 1][snake[t][1].y / 2 - 1 - 1] > -500) ||
			(snake[t][1].y / 2 - 1 - 1 >= 0 && heatPanel[snake[t][1].x - 1 + 1][snake[t][1].y / 2 - 1 - 1] > -500))

		if (heatPanel[headX][headY - 1] > max) {
			max = heatPanel[headX][headY - 1];
			nextX = headX;
			nextY = headY - 1;
			next = 2;
		}
	}
	if (headY + 1 < 38) {	//右
		if ((snake[t][1].y / 2 - 1 + 1 + 1 < 38 && heatPanel[snake[t][1].x - 1][snake[t][1].y / 2 - 1 + 1 + 1] > -500) ||
			(snake[t][1].y / 2 - 1 + 1 < 28 && snake[t][1].x - 1 - 1 >= 0 && heatPanel[snake[t][1].x - 1 - 1][snake[t][1].y / 2 - 1 + 1] > -500) ||
			(snake[t][1].y / 2 - 1 + 1 <28 && heatPanel[snake[t][1].x - 1 + 1][snake[t][1].y / 2 - 1 + 1] > -500))
		if (heatPanel[headX][headY + 1] > max) {
			max = heatPanel[headX][headY + 1];
			nextX = headX;
			nextY = headY + 1;
			next = 1;
		}
	}
	
	if (heatPanel[nextX][nextY] > -100 && check(snake, len, t, gp, next))
		return next;
	

	max = -999;
	next = 0;
	if (heatPanel[headX + 1][headY] > max&& check(snake, len, t, gp, 0)) {
		next = 0;
		max = heatPanel[headX + 1][headY];
	}
	if (heatPanel[headX][headY + 1] > max&& check(snake, len, t, gp, 1)) {
		next = 1;
		max = heatPanel[headX][headY + 1];
	}
	if (heatPanel[headX - 1][headY] > max&& check(snake, len, t, gp, 3)) {
		next = 3;
		max = heatPanel[headX - 1][headY];
	}
	if (heatPanel[headX][headY - 1] > max&& check(snake, len, t, gp, 2)) {
		next = 2;
		max = heatPanel[headX][headY - 1];
	}
	if (check(snake, len, t, gp, next))
		return next;
	return 1;

}

