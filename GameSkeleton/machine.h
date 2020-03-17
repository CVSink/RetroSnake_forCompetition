#include "snake.h"
using namespace std;


class tools {
public:
	tools(int n, int m, int t);
	void ini(GamePanel& gp,point snake[][100]);
	void shortestPath();
private:
	int map[50][50];
	int target[20];
	int map_n;
	int map_m;
	int tem_t;
	int count;
};

tools::tools(int n, int m, int t)
	:map_n(n), map_m(m / 2), tem_t(t) {}

void tools::ini(GamePanel& gp,point snake[][100]) {
	int c = 0;
	for (int i = 0; i < map_n; ++i) {
		for (int j = 0; j < map_m; j+=2) {
			if (gp.panel[i][j] == 1) {
				c++;
			}
		}
	}
	count = c;

	for (int i = 0; i < 20; ++i) {
		if (gp.panel[gp.food[i].x][gp.food[i].y] == 1) {
			target[i] = 1;
		}
		else {
			target[i] = 0;
		}
	}

	int k = 1;
	int p = 1;
	for (int i = 0; i < 20; ++i) {
		if (target[i] == 1) {
			for (int j = 0; j < 20; ++j) {
				if (target[j] == 1) {
					map[k][p++] = abs(gp.food[i].x - gp.food[j].x) + abs(gp.food[i].y - gp.food[j].y);
				}
			}
			++k;
		}
	}
	k = 0;
	for (int i = 0; i < 20; i++) {
		if (target[i] == 1) {
			int tem = abs(gp.food[i].x - snake[tem_t][1].x) + abs(gp.food[i].y - snake[tem_t][1].y);
			map[0][k] = tem;
			map[k++][0] = tem;
		}
	}
	return;
}


void tools::shortestPath() {

}

bool check(point snake[5][100], int len[5], int t, GamePanel gp, int direction ) 
{
	//将你的check函数体放在此处，并删去下面示例代码
	if (snake[t][1].y == gp.m && direction == 1) return false;
	if (snake[t][1].y == 2 && direction == 2) return false;
	return true;
}

int machine_move(point snake[5][100], int len[5], int direct[5], int t, GamePanel gp)	
{
	tools tool(gp.n, gp.m, t);






	//将你的check函数体放在此处，并删去下面示例代码
	if (t == 0) return 2;
	else return 1;
}
