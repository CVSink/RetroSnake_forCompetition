#include "snake.h"
using namespace std;

<<<<<<< HEAD
<<<<<<< HEAD
bool check(point snake[5][100], int len[5], int t, GamePanel gp, int direction ) 
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
=======
=======
>>>>>>> parent of ceaf48b... 1st test project commit

bool check(point snake[5][100], int len[5], int t, GamePanel gp, int direction ) 
{
>>>>>>> parent of ceaf48b... 1st test project commit
	//将你的check函数体放在此处，并删去下面示例代码
	if (snake[t][1].y == gp.m && direction == 1) return false;
	if (snake[t][1].y == 2 && direction == 2) return false;
	return true;
}

<<<<<<< HEAD
<<<<<<< HEAD
class graph {
public:

private:
	
};

int machine_move(point snake[5][100], int len[5], int direct[5], int t, GamePanel gp)	
{
//	int map[2500][2500];
	return 3;
=======
int machine_move(point snake[5][100], int len[5], int direct[5], int t, GamePanel gp)	
{
>>>>>>> parent of ceaf48b... 1st test project commit
=======
int machine_move(point snake[5][100], int len[5], int direct[5], int t, GamePanel gp)	
{
>>>>>>> parent of ceaf48b... 1st test project commit
	//将你的check函数体放在此处，并删去下面示例代码
	if (t == 0) return 2;
	else return 1;
}
