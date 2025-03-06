#include<iostream>
#include<windows.h>
#include<conio.h>
#include<time.h>
using namespace std;
int enemy1limity1, enemy1limity2, enemy2limity1, enemy2limity2, enemy3limity1, enemy3limity2, enemy4limity1, enemy4limity2, enemy5limity1, enemy5limity2, enemy6limity1, enemy6limity2, timemissile = 0;
int enemy1limitx1, enemy1limitx2, enemy2limitx1, enemy2limitx2, enemy3limitx1, enemy3limitx2, enemy4limitx1, enemy4limitx2, enemy5limitx1, enemy5limitx2, enemy6limitx1, enemy6limitx2;
int ethenx, etheny, obstaclestatus = 1, missilestatus = 0;
static int bulletx = -1, bullety = -1, enemy1bulletx, enemy1bullety, enemy1bulletdir = 0, enemy2bulletdir = 0, enemy2bulletx, enemy2bullety, enemy3bulletx, enemy3bullety, enemy4bulletx, enemy4bullety, enemy5bulletx, enemy5bullety, enemy6bulletx, enemy6bullety, enemy3bulletdir = 0, enemy4bulletdir = 0, enemy5bulletdir = 0, enemy6bulletdir = 0;
int dir = 0, status = 1, enemy1status = 1, enemy3status = 1, enemy4status = 1, enemy5status = 1, enemy6status = 1, enemy2status = 1, enemy1bulletstatus = 1, enemy2bulletstatus = 1, enemy3bulletstatus = 1, enemy4bulletstatus = 1, enemy5bulletstatus = 1, enemy6bulletstatus = 1, bulletcollidestatus = 0, missiletrack = 0;
int enemy1x, enemy1y, enemy2x, enemy2y, enemy3x, enemy3y, enemy4x, enemy4y, enemy5x, enemy5y, enemy6x, enemy6y, gameend = 0;
int missilex, missiley, survivaltime = 0, score = 0;
int track = 0, level = 0;
static int solox = 5, soloy = 15, missile = 1;
int bulletsolostatusup = 0, bulletsolostatusdown = 0, bulletsolostatusright = 0, bulletsolostatusleft = 0, flag1 = 0, flag2 = 0, flag3 = 0, flag4 = 0, flag5 = 0, flag6 = 0;
int solobulletupx, solobulletupy, solobulletdownx, solobulletdowny, solobulletrightx, solobulletrighty, solobulletleftx, solobulletlefty;
int flag = 0, solomenlifestatus = 1;
int ismove = 0, solospeed = 1, enemyspeed = 1;
int life = 3;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
// Function to set the cursor position
void setCursorPosition(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void erasesolomenbullets(char map[][50]) {
	bulletsolostatusup = 0, bulletsolostatusdown = 0, bulletsolostatusright = 0, bulletsolostatusleft = 0;
	map[solobulletupx][solobulletupy] = ' ';
	map[solobulletdownx][solobulletdowny] = ' ';
	map[solobulletleftx][solobulletlefty] = ' ';
	map[solobulletrightx][solobulletrighty] = ' ';


}
void mapformation(char map[][50])
{

	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 50; j++) {
			map[i][j] = ' ';
		}
	}
	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 50; j++) {
			map[0][j] = '-';
			map[49][j] = '-';
			map[i][0] = '|';
			map[i][49] = '|';
		}
	}
	for (int i = 18; i < 25; i++) {
		map[0][i] = ' ';

	}
}

void movesolobullet(char map[][50])
{
	if (map[solobulletupx - 1][solobulletupy] == ' ')
	{
		map[solobulletupx][solobulletupy] = ' ';
		solobulletupx--;
		map[solobulletupx][solobulletupy] = '|';
		bulletsolostatusup = 1;
	}
	else
	{
		map[solobulletupx][solobulletupy] = ' ';
		bulletsolostatusup = 0;
	}
	if (map[solobulletdownx + 1][solobulletdowny] == ' ')
	{
		map[solobulletdownx][solobulletdowny] = ' ';
		solobulletdownx++;
		map[solobulletdownx][solobulletdowny] = '|';
		bulletsolostatusdown = 1;
	}
	else
	{
		map[solobulletdownx][solobulletdowny] = ' ';
		bulletsolostatusdown = 0;
	}
	if (map[solobulletrightx][solobulletrighty + 1] == ' ')  // Change +2 to +1
	{
		map[solobulletrightx][solobulletrighty] = ' ';  // Clear the previous position
		solobulletrighty++;  // Move the bullet to the right
		map[solobulletrightx][solobulletrighty] = '-';  // Place the new bullet
		bulletsolostatusright = 1;
	}
	else
	{
		map[solobulletrightx][solobulletrighty] = ' ';  // Clear the bullet if blocked
		bulletsolostatusright = 0;  // Stop the movement if there's an obstacle
	}

	if (map[solobulletleftx][solobulletlefty - 1] == ' ')
	{
		map[solobulletleftx][solobulletlefty] = ' ';
		solobulletlefty--;
		map[solobulletleftx][solobulletlefty] = '-';
		bulletsolostatusleft = 1;
	}
	else
	{
		map[solobulletleftx][solobulletlefty] = ' ';
		bulletsolostatusleft = 0;
	}
}

void solomenlifecheck(char map[][50]) {
	if (map[solox][soloy + 5] == '*' || map[solox - 1][soloy + 3] == '*' || map[solox - 1][soloy + 4] == '*' || map[solox + 1][soloy + 4] == '*' || map[solox + 1][soloy + 3] == '*') {
		solomenlifestatus = 0;
	}
	if (map[solox + 2][soloy + 1] == '*' || map[solox + 2][soloy - 1] == '*' || map[solox + 2][soloy] == '*') {
		solomenlifestatus = 0;

	}
	if (map[solox - 2][soloy + 1] == '*' || map[solox - 2][soloy - 1] == '*' || map[solox - 2][soloy] == '*') {
		solomenlifestatus = 0;

	}
	if (map[solox][soloy - 5] == '*' || map[solox - 1][soloy - 3] == '*' || map[solox - 1][soloy - 4] == '*' || map[solox + 1][soloy - 4] == '*' || map[solox + 1][soloy - 3] == '*') {
		solomenlifestatus = 0;
	}

}

void killenemy1(char map[][50], int enemy1x, int enemy1y)
{
	map[enemy1x][enemy1y] = ' ';
	map[enemy1x][enemy1y - 1] = ' ';
	map[enemy1x][enemy1y + 1] = ' ';
	map[enemy1x + 1][enemy1y] = ' ';
	map[enemy1x + 1][enemy1y - 1] = ' ';
	map[enemy1x + 1][enemy1y + 1] = ' ';
}
void killenemy2(char map[][50], int enemy1x, int enemy1y, int enemy2x, int enemy2y) {

	map[enemy2x][enemy2y] = ' ';
	map[enemy2x][enemy2y - 1] = ' ';
	map[enemy2x][enemy2y + 1] = ' ';
	map[enemy2x + 1][enemy2y] = ' ';
	map[enemy2x + 1][enemy2y - 1] = ' ';
	map[enemy2x + 1][enemy2y + 1] = ' ';
}
void movemissile(char map[][50]) {

	switch (missile) {

	case 1:

		if (missilestatus == 1) {

			map[missilex][missiley] = ' ';
			if (missiletrack == 0) {
				if (missilex < enemy1x)
				{
					missilex++;

				}
				else if (missilex > enemy1x)
				{
					missilex--;

				}
				map[missilex][missiley] = '^';
				if (missilex == enemy1x) {
					missiletrack = 1;
					map[missilex][missiley] = ' ';

				}
			}
			if (missiletrack == 1) {
				if (missiley < enemy1y)
				{
					missiley++;
					map[missilex][missiley] = '>';

				}
				else if (missiley > enemy1y)
				{
					missiley--;
					map[missilex][missiley] = '<';

				}
				if (missiley == enemy1y) {
					missiletrack = 0;
					map[missilex][missiley] = ' ';

				}


			}
			//if (enemy1status == 1) {
			//	survivaltime = 0;
			//}

		}
		break;
	case 2:

		if (missilestatus == 1) {

			map[missilex][missiley] = ' ';
			if (missiletrack == 0) {
				if (missilex < enemy2x) {
					missilex++;
				}
				else if (missilex > enemy2x) {
					missilex--;
				}
				map[missilex][missiley] = '^';
				if (missilex == enemy2x) {
					missiletrack = 1;
					map[missilex][missiley] = ' ';
				}
			}
			if (missiletrack == 1) {
				if (missiley < enemy2y) {
					missiley++;
					map[missilex][missiley] = '>';
				}
				else if (missiley > enemy2y) {
					missiley--;
					map[missilex][missiley] = '<';
				}
				if (missiley == enemy2y) {
					missiletrack = 0;
					map[missilex][missiley] = ' ';
				}
			}
			//if (enemy2status == 1) {
			//	survivaltime = 0;

			//}
		}
		break;

	case 3:
		if (missilestatus == 1) {

			map[missilex][missiley] = ' ';
			if (missiletrack == 0) {
				if (missilex < enemy3x) {
					missilex++;
				}
				else if (missilex > enemy3x) {
					missilex--;
				}
				map[missilex][missiley] = '^';
				if (missilex == enemy3x) {
					missiletrack = 1;
					map[missilex][missiley] = ' ';
				}
			}
			if (missiletrack == 1) {
				if (missiley < enemy3y) {
					missiley++;
					map[missilex][missiley] = '>';
				}
				else if (missiley > enemy3y) {
					missiley--;
					map[missilex][missiley] = '<';
				}
				if (missiley == enemy3y) {
					missiletrack = 0;
					map[missilex][missiley] = ' ';
				}
			}
			//if (enemy3status == 1) {
			//	survivaltime = 0;

			//}
		}
		break;


	case 4:
		if (missilestatus == 1) {

			map[missilex][missiley] = ' ';
			if (missiletrack == 0) {
				if (missilex < enemy4x) {
					missilex++;
				}
				else if (missilex > enemy4x) {
					missilex--;
				}
				map[missilex][missiley] = '^';
				if (missilex == enemy4x) {
					missiletrack = 1;
					map[missilex][missiley] = ' ';
				}
			}
			if (missiletrack == 1) {
				if (missiley < enemy4y) {
					missiley++;
					map[missilex][missiley] = '>';
				}
				else if (missiley > enemy4y) {
					missiley--;
					map[missilex][missiley] = '<';
				}
				if (missiley == enemy4y) {
					missiletrack = 0;
					map[missilex][missiley] = ' ';
				}
			}
			//if (enemy4status == 1) {
			//	survivaltime = 0;

			//}
		}
		break;

	case5:

		if (missilestatus == 1) {

			map[missilex][missiley] = ' ';
			if (missiletrack == 0) {
				if (missilex < enemy5x) {
					missilex++;
				}
				else if (missilex > enemy5x) {
					missilex--;
				}
				map[missilex][missiley] = '^';
				if (missilex == enemy5x) {
					missiletrack = 1;
					map[missilex][missiley] = ' ';
				}
			}
			if (missiletrack == 1) {
				if (missiley < enemy5y) {
					missiley++;
					map[missilex][missiley] = '>';
				}
				else if (missiley > enemy5y) {
					missiley--;
					map[missilex][missiley] = '<';
				}
				if (missiley == enemy5y) {
					missiletrack = 0;
					map[missilex][missiley] = ' ';
				}
			}
			//if (enemy5status == 1) {
			//	survivaltime = 0;

			//}
		}

		break;


	case6:
		if (missilestatus == 1) {

			map[missilex][missiley] = ' ';
			if (missiletrack == 0) {
				if (missilex < enemy6x) {
					missilex++;
				}
				else if (missilex > enemy6x) {
					missilex--;
				}
				map[missilex][missiley] = '^';
				if (missilex == enemy6x) {
					missiletrack = 1;
					map[missilex][missiley] = ' ';
				}
			}
			if (missiletrack == 1) {
				if (missiley < enemy6y) {
					missiley++;
					map[missilex][missiley] = '>';
				}
				else if (missiley > enemy6y) {
					missiley--;
					map[missilex][missiley] = '<';
				}
				if (missiley == enemy6y) {
					missiletrack = 0;
					map[missilex][missiley] = ' ';
				}
			}
			//if (enemy6status == 1) {
			//	survivaltime = 0;

			//}
		}
		break;
	}


	//if (map[missilex - 1][missiley+1] == ']' || map[missilex - 1][missiley-1] == '[' || map[missilex - 1][missiley] == 'V' ) {

	//	if (map[missilex - 1][missiley] == '1' || map[missilex - 1][missiley + 1] == '1' || map[missilex - 1][missiley - 1] == '1') {
	//		killenemy1(map, enemy1x, enemy1y);
	//		killenemy1(map, enemy1x, enemy1y);
	//		killenemy1(map, enemy1x, enemy1y);

	//		enemy1status = 0;
	//	}
	//	//if (map[missilex - 2][missiley] == '1' || map[missilex - 2][missiley + 1] == '1' || map[missilex - 2][missiley - 1] == '1') {
	//	//	killenemy1(map, enemy1x, enemy1y, enemy2x, enemy2y);
	//	//	enemy1status = 0;
	//	//}

	//	if (map[missilex - 1][missiley] == '2' || map[missilex - 1][missiley + 1] == '2' || map[missilex - 1][missiley - 1] == '2') {

	//		killenemy1(map,  enemy2x, enemy2y);
	//		killenemy1(map,  enemy2x, enemy2y);
	//		killenemy1(map,  enemy2x, enemy2y);


	//		enemy2status = 0;

	//	}

	//	//if (map[missilex - 2][missiley] == '2' || map[missilex - 2][missiley + 1] == '2' || map[missilex - 2][missiley - 1] == '2') {

	//	//	killenemy2(map, enemy1x, enemy1y, enemy2x, enemy2y);
	//	//	enemy2status = 0;


	//	//}

	//	status = 1;
	//	dir = 0;
	//	map[missilex][missiley] = ' ';
	//}

}


void mapdisplay(char map[][50])
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 });


	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 50; j++) {
			if ((i == 0 && map[i][j] == '-') || (j == 0 && map[i][j] == '|') || (i == 49 && map[i][j] == '-') || (j == 49 && map[i][j] == '|'))
			{
				SetConsoleTextAttribute(hConsole, 15);
				cout << map[i][j];
			}
			else if (map[i][j] == '|' || map[i][j] == '/' || map[i][j] == '\\' || map[i][j] == 'O')
			{
				SetConsoleTextAttribute(hConsole, 1);
				cout << map[i][j];
			}
			else if (map[i][j] == '[' || map[i][j] == ']' || map[i][j] == 'X')
			{
				SetConsoleTextAttribute(hConsole, 4);
				cout << map[i][j];
			}
			else if (map[i][j] == 'V' || map[i][j] == '1' || map[i][j] == '2')
			{
				SetConsoleTextAttribute(hConsole, 6);
				cout << map[i][j];
			}
			else if (map[i][j] == '-')
			{
				SetConsoleTextAttribute(hConsole, 2);
				cout << map[i][j];
			}
			else
				cout << map[i][j];
		}

		cout << endl;
	}
}

void addobstaclesagain(char map[][50], int x, int y, int x1, int y1, int x2, int y2, int x3, int y3) {
	if (level == 1) {


		map[x][y] = '-';
		map[x][y + 1] = '-';
		map[x][y + 2] = '-';
		map[x][y - 1] = '[';
		map[x][y + 3] = ']';


		map[x1][y1] = '-';
		map[x1][y1 + 1] = '-';
		map[x1][y1 + 2] = '-';
		map[x1][y1 - 1] = '[';
		map[x1][y1 + 3] = ']';
	}

	if (level == 2) {
		map[x][y] = '-';
		map[x][y + 1] = '-';
		map[x][y + 2] = '-';
		map[x][y - 1] = '[';
		map[x][y + 3] = ']';

		map[x1][y1] = '-';
		map[x1][y1 + 1] = '-';
		map[x1][y1 + 2] = '-';
		map[x1][y1 - 1] = '[';
		map[x1][y1 + 3] = ']';

		map[x2][y2] = '-';
		map[x2][y2 + 1] = '-';
		map[x2][y2 + 2] = '-';
		map[x2][y2 - 1] = '[';
		map[x2][y2 + 3] = ']';
	}

	if (level == 3) {

		map[x][y] = '-';
		map[x][y + 1] = '-';
		map[x][y + 2] = '-';
		map[x][y + 3] = '-';
		map[x][y - 1] = '[';
		map[x][y + 4] = ']';

		map[x1][y1] = '-';
		map[x1][y1 + 1] = '-';
		map[x1][y1 + 2] = '-';
		map[x1][y1 + 3] = '-';
		map[x1][y1 - 1] = '[';
		map[x1][y1 + 4] = ']';

		map[x2][y2] = '-';
		map[x2][y2 + 1] = '-';
		map[x2][y2 + 2] = '-';
		map[x2][y2 + 3] = '-';
		map[x2][y2 - 1] = '[';
		map[x2][y2 + 4] = ']';
	}

	if (level == 4) {
		map[x][y] = '-';
		map[x][y + 1] = '-';
		map[x][y + 2] = '-';
		map[x][y + 3] = '-';
		map[x][y - 1] = '[';
		map[x][y + 4] = ']';

		map[x1][y1] = '-';
		map[x1][y1 + 1] = '-';
		map[x1][y1 + 2] = '-';
		map[x1][y1 + 3] = '-';
		map[x1][y1 - 1] = '[';
		map[x1][y1 + 4] = ']';

		map[x2][y2] = '-';
		map[x2][y2 + 1] = '-';
		map[x2][y2 + 2] = '-';
		map[x2][y2 + 3] = '-';
		map[x2][y2 - 1] = '[';
		map[x2][y2 + 4] = ']';


		map[x3][y3] = '-';
		map[x3][y3 + 1] = '-';
		map[x3][y3 + 2] = '-';
		map[x3][y3 + 3] = '-';
		map[x3][y3 - 1] = '[';
		map[x3][y3 + 4] = ']';
	}

	if (level == 5) {
		map[x][y] = '-';
		map[x][y + 1] = '-';
		map[x][y + 2] = '-';
		map[x][y + 3] = '-';
		map[x][y + 4] = '-';
		map[x][y - 1] = '[';
		map[x][y + 5] = ']';

		map[x1][y1] = '-';
		map[x1][y1 + 1] = '-';
		map[x1][y1 + 2] = '-';
		map[x1][y1 + 3] = '-';
		map[x1][y1 + 4] = '-';
		map[x1][y1 - 1] = '[';
		map[x1][y1 + 5] = ']';

		map[x2][y2] = '-';
		map[x2][y2 + 1] = '-';
		map[x2][y2 + 2] = '-';
		map[x2][y2 + 3] = '-';
		map[x2][y2 + 4] = '-';
		map[x2][y2 - 1] = '[';
		map[x2][y2 + 5] = ']';


		map[x3][y3] = '-';
		map[x3][y3 + 1] = '-';
		map[x3][y3 + 2] = '-';
		map[x3][y3 + 3] = '-';
		map[x3][y3 + 4] = '-';
		map[x3][y3 - 1] = '[';
		map[x3][y3 + 5] = ']';
	}




}

void addobstacle(char map[][50], int x, int y, int x1, int y1, int x2, int y2, int x3, int y3) {

	if (level == 1) {

		if (map[x][y] == ' ') {
			map[x][y] = '-';
			map[x][y + 1] = '-';
			map[x][y + 2] = '-';
			map[x][y - 1] = '[';
			map[x][y + 3] = ']';

		}
		if (map[x1][y1] == ' ') {
			map[x1][y1] = '-';
			map[x1][y1 + 1] = '-';
			map[x1][y1 + 2] = '-';
			map[x1][y1 - 1] = '[';
			map[x1][y1 + 3] = ']';
		}
	}

	if (level == 2) {
		if (map[x][y] == ' ') {
			map[x][y] = '-';
			map[x][y + 1] = '-';
			map[x][y + 2] = '-';
			map[x][y - 1] = '[';
			map[x][y + 3] = ']';

		}
		if (map[x1][y1] == ' ') {
			map[x1][y1] = '-';
			map[x1][y1 + 1] = '-';
			map[x1][y1 + 2] = '-';
			map[x1][y1 - 1] = '[';
			map[x1][y1 + 3] = ']';
		}
		if (map[x2][y2] == ' ') {
			map[x2][y2] = '-';
			map[x2][y2 + 1] = '-';
			map[x2][y2 + 2] = '-';
			map[x2][y2 - 1] = '[';
			map[x2][y2 + 3] = ']';
		}
	}

	if (level == 3) {
		if (map[x][y] == ' ') {
			map[x][y] = '-';
			map[x][y + 1] = '-';
			map[x][y + 2] = '-';
			map[x][y + 3] = '-';
			map[x][y - 1] = '[';
			map[x][y + 4] = ']';

		}
		if (map[x1][y1] == ' ') {
			map[x1][y1] = '-';
			map[x1][y1 + 1] = '-';
			map[x1][y1 + 2] = '-';
			map[x1][y1 + 3] = '-';
			map[x1][y1 - 1] = '[';
			map[x1][y1 + 4] = ']';
		}
		if (map[x2][y2] == ' ') {
			map[x2][y2] = '-';
			map[x2][y2 + 1] = '-';
			map[x2][y2 + 2] = '-';
			map[x2][y2 + 3] = '-';
			map[x2][y2 - 1] = '[';
			map[x2][y2 + 4] = ']';
		}
	}

	if (level == 4) {
		if (map[x][y] == ' ') {
			map[x][y] = '-';
			map[x][y + 1] = '-';
			map[x][y + 2] = '-';
			map[x][y + 3] = '-';
			map[x][y - 1] = '[';
			map[x][y + 4] = ']';

		}
		if (map[x1][y1] == ' ') {
			map[x1][y1] = '-';
			map[x1][y1 + 1] = '-';
			map[x1][y1 + 2] = '-';
			map[x1][y1 + 3] = '-';
			map[x1][y1 - 1] = '[';
			map[x1][y1 + 4] = ']';
		}
		if (map[x2][y2] == ' ') {
			map[x2][y2] = '-';
			map[x2][y2 + 1] = '-';
			map[x2][y2 + 2] = '-';
			map[x2][y2 + 3] = '-';
			map[x2][y2 - 1] = '[';
			map[x2][y2 + 4] = ']';
		}
		if (map[x3][y3] == ' ') {
			map[x3][y3] = '-';
			map[x3][y3 + 1] = '-';
			map[x3][y3 + 2] = '-';
			map[x3][y3 + 3] = '-';
			map[x3][y3 - 1] = '[';
			map[x3][y3 + 4] = ']';
		}
	}

	if (level == 5) {
		if (map[x][y] == ' ') {
			map[x][y] = '-';
			map[x][y + 1] = '-';
			map[x][y + 2] = '-';
			map[x][y + 3] = '-';
			map[x][y + 4] = '-';
			map[x][y - 1] = '[';
			map[x][y + 5] = ']';

		}
		if (map[x1][y1] == ' ') {
			map[x1][y1] = '-';
			map[x1][y1 + 1] = '-';
			map[x1][y1 + 2] = '-';
			map[x1][y1 + 3] = '-';
			map[x1][y1 + 4] = '-';
			map[x1][y1 - 1] = '[';
			map[x1][y1 + 5] = ']';
		}
		if (map[x2][y2] == ' ') {
			map[x2][y2] = '-';
			map[x2][y2 + 1] = '-';
			map[x2][y2 + 2] = '-';
			map[x2][y2 + 3] = '-';
			map[x2][y2 + 4] = '-';
			map[x2][y2 - 1] = '[';
			map[x2][y2 + 5] = ']';
		}
		if (map[x3][y3] == ' ') {
			map[x3][y3] = '-';
			map[x3][y3 + 1] = '-';
			map[x3][y3 + 2] = '-';
			map[x3][y3 + 3] = '-';
			map[x3][y3 + 4] = '-';
			map[x3][y3 - 1] = '[';
			map[x3][y3 + 5] = ']';
		}
	}





}
void createenemy1(char map[][50], int enemy1x, int enemy1y, int enemy2x, int enemy2y) {
	if (map[enemy1x][enemy1y] == ' ' && (map[enemy1x][enemy1y] != '|' || map[enemy1x][enemy1y] != '-'))
	{
		map[enemy1x][enemy1y] = 'I';
		map[enemy1x][enemy1y - 1] = '[';
		map[enemy1x][enemy1y + 1] = ']';
		map[enemy1x + 1][enemy1y] = 'V';
		map[enemy1x + 1][enemy1y - 1] = '[';
		map[enemy1x + 1][enemy1y + 1] = ']';
	}
}
void solomen(char map[][50], int solox, int soloy) {

	map[solox][soloy] = 'X';
	map[solox - 1][soloy + 1] = ']';
	map[solox - 1][soloy - 1] = '[';
	map[solox][soloy + 1] = ']';
	map[solox][soloy - 1] = '[';
	map[solox][soloy + 2] = '[';
	map[solox][soloy + 4] = ']';
	map[solox][soloy - 2] = ']';
	map[solox][soloy - 4] = '[';
	map[solox + 1][soloy - 1] = '[';
	map[solox + 1][soloy + 1] = ']';

}

void spacesolo(char map[][50], int solox, int soloy) {
	map[solox][soloy] = ' ';
	map[solox - 1][soloy + 1] = ' ';
	map[solox - 1][soloy - 1] = ' ';
	map[solox][soloy + 1] = ' ';
	map[solox][soloy - 1] = ' ';
	map[solox][soloy + 2] = ' ';
	map[solox][soloy + 4] = ' ';
	map[solox][soloy - 2] = ' ';
	map[solox][soloy - 4] = ' ';
	map[solox + 1][soloy - 1] = ' ';
	map[solox + 1][soloy + 1] = ' ';
}

void movesolomen(char map[][50], int& solox, int& soloy, int& count, int x, int y, int x1, int y1, int x2, int y2, int x3, int y3)
{
	if (ismove % solospeed == 0)
	{
		if (solomenlifestatus == 1) {

			if (count == 0)
			{
				if (soloy < 40)
				{
					spacesolo(map, solox, soloy);
					soloy += 1;
					//solomen(map, solox, soloy);
				}
				else
				{
					count = 1;
				}


			}
			else  if (count == 1)
			{
				if (solox < 20.)
				{
					spacesolo(map, solox, soloy);
					solox++;
					//solomen(map, solox, soloy);
				}
				else
				{
					spacesolo(map, solox, soloy);
					solox--;
					//solomen(map, solox, soloy);
				}
				count = 2;
			}
			else if (count == 2)
			{
				if (soloy > 6)
				{
					spacesolo(map, solox, soloy);
					soloy -= 1;
					//solomen(map, solox, soloy);

				}
				else
				{
					count = 3;
				}
			}
			else if (count == 3)
			{
				spacesolo(map, solox, soloy);
				solox++;
				count = 0;
			}
			solomen(map, solox, soloy);


			if (bulletsolostatusup == 0)
			{
				solobulletupx = solox - 2;
				solobulletupy = soloy;
				if (map[solobulletupx][solobulletupy] == ' ')
				{
					map[solobulletupx][solobulletupy] = '|';
					bulletsolostatusup = 1;
				}
			}
			else
			{
				movesolobullet(map);
			}
			if (bulletsolostatusdown == 0)
			{
				solobulletdownx = solox + 2;
				solobulletdowny = soloy;
				if (map[solobulletdownx][solobulletdowny] == ' ')
				{
					map[solobulletdownx][solobulletdowny] = '|';
					bulletsolostatusdown = 1;
				}
			}
			else
			{
				movesolobullet(map);
			}
			if (bulletsolostatusright == 0)
			{
				solobulletrightx = solox;
				solobulletrighty = soloy + 5;
				if (map[solobulletrightx][solobulletrighty] == ' ')
				{
					map[solobulletrightx][solobulletrighty] = '-';
					bulletsolostatusright = 1;
				}
			}
			else
			{
				movesolobullet(map);
			}
			if (bulletsolostatusleft == 0)
			{
				solobulletleftx = solox;
				solobulletlefty = soloy - 5;
				if (map[solobulletleftx][solobulletlefty] == ' ')
				{
					map[solobulletleftx][solobulletlefty] = '-';
					bulletsolostatusleft = 1;
				}
			}
			else
			{
				movesolobullet(map);
			}
		}
	}
	addobstacle(map, x, y, x1, y1, x2, y2, x3, y3);

}
void createenemy2(char map[][50], int enemy1x, int enemy1y, int enemy2x, int enemy2y) {

	if (map[enemy2x][enemy2y] == ' ' && (map[enemy2x][enemy2y] != '|' || map[enemy2x][enemy2y] != '-'))
	{
		map[enemy2x][enemy2y] = 'I';
		map[enemy2x][enemy2y - 1] = '[';
		map[enemy2x][enemy2y + 1] = ']';
		map[enemy2x + 1][enemy2y] = 'V';
		map[enemy2x + 1][enemy2y - 1] = '[';
		map[enemy2x + 1][enemy2y + 1] = ']';
	}
}
void moveenemy1bullet(char map[][50]) {
	if (enemy1bulletdir == 1) {



		if ((map[enemy1bulletx + 2][enemy1bullety] != ' ') || (map[enemy1bulletx + 2][enemy1bullety] == '*') || (map[enemy1bulletx + 1][enemy1bullety] == '*') || (map[enemy1bulletx + 4][enemy1bullety] == '*')) {

			enemy1bulletstatus = 1;
			enemy1bulletdir = 0;

			map[enemy1bulletx][enemy1bullety] = ' ';
		}
		else {
			map[enemy1bulletx][enemy1bullety] = ' ';
			enemy1bulletx++;
			map[enemy1bulletx][enemy1bullety] = '|';
			enemy1bulletstatus = 0;


		}
	}
	if (enemy1bulletdir == 2) {



		if ((map[enemy1bulletx - 2][enemy1bullety] != ' ') || (map[enemy1bulletx - 2][enemy1bullety] == '*') || (map[enemy1bulletx - 1][enemy1bullety] == '*') || (map[enemy1bulletx - 4][enemy1bullety] == '*')) {

			enemy1bulletstatus = 1;
			enemy1bulletdir = 0;

			map[enemy1bulletx][enemy1bullety] = ' ';

		}
		else {

			map[enemy1bulletx][enemy1bullety] = ' ';
			enemy1bulletx--;
			map[enemy1bulletx][enemy1bullety] = '|';
			enemy1bulletstatus = 0;



		}
	}
	if (enemy1bulletdir == 3) {


		if (map[enemy1bulletx][enemy1bullety - 2] != ' ' || map[enemy1bulletx][enemy1bullety - 2] == '*' || map[enemy1bulletx][enemy1bullety - 1] == '*' || map[enemy1bulletx][enemy1bullety - 0] == '*') {
			enemy1bulletstatus = 1;
			enemy1bulletdir = 0;

			map[enemy1bulletx][enemy1bullety] = ' ';
		}
		else {
			map[enemy1bulletx][enemy1bullety] = ' ';
			enemy1bullety--;
			map[enemy1bulletx][enemy1bullety] = '-';
			enemy1bulletstatus = 0;
		}
	}
	if (enemy1bulletdir == 4) {


		if (map[enemy1bulletx][enemy1bullety + 2] != ' ' || map[enemy1bulletx][enemy1bullety + 2] == '*') {
			enemy1bulletstatus = 1;
			enemy1bulletdir = 0;
			map[enemy1bulletx][enemy1bullety] = ' ';
		}
		else {
			map[enemy1bulletx][enemy1bullety] = ' ';
			enemy1bullety++;
			map[enemy1bulletx][enemy1bullety] = '-';
			enemy1bulletstatus = 0;
		}
	}
}
void moveenemy2bullet(char map[][50]) {
	if (enemy2bulletdir == 1) {


		if (map[enemy2bulletx + 2][enemy2bullety] != ' ' || map[enemy2bulletx + 2][enemy2bullety] == '*') {
			enemy2bulletstatus = 1;
			enemy2bulletdir = 0;
			map[enemy2bulletx][enemy2bullety] = ' ';
		}
		else {
			map[enemy2bulletx][enemy2bullety] = ' ';
			enemy2bulletx++;
			map[enemy2bulletx][enemy2bullety] = '|';
			enemy2bulletstatus = 0;
		}
	}
	if (enemy2bulletdir == 2) {


		if (map[enemy2bulletx - 2][enemy2bullety] != ' ' || map[enemy2bulletx - 2][enemy2bullety] == '*') {
			enemy2bulletstatus = 1;
			enemy2bulletdir = 0;
			map[enemy2bulletx][enemy2bullety] = ' ';
		}
		else {
			map[enemy2bulletx][enemy2bullety] = ' ';
			enemy2bulletx--;
			map[enemy2bulletx][enemy2bullety] = '|';
			enemy2bulletstatus = 0;
		}
	}
	if (enemy2bulletdir == 3) {


		if (map[enemy2bulletx][enemy2bullety - 2] != ' ' || map[enemy2bulletx][enemy2bullety - 2] == '*') {
			enemy2bulletstatus = 1;
			enemy2bulletdir = 0;
			map[enemy2bulletx][enemy2bullety] = ' ';
		}
		else {
			map[enemy2bulletx][enemy2bullety] = ' ';
			enemy2bullety--;
			map[enemy2bulletx][enemy2bullety] = '-';
			enemy2bulletstatus = 0;
		}
	}
	if (enemy2bulletdir == 4) {


		if (map[enemy2bulletx][enemy2bullety + 2] != ' ' || map[enemy2bulletx][enemy2bullety + 2] == '*') {
			enemy2bulletstatus = 1;
			enemy2bulletdir = 0;
			map[enemy2bulletx][enemy2bullety] = ' ';
		}
		else {
			map[enemy2bulletx][enemy2bullety] = ' ';
			enemy2bullety++;
			map[enemy2bulletx][enemy2bullety] = '-';
			enemy2bulletstatus = 0;
		}
	}
}


void moveenemy3bullet(char map[][50]) {
	if (enemy3bulletdir == 1) {

		if ((map[enemy3bulletx + 2][enemy3bullety] != ' ') || (map[enemy3bulletx + 2][enemy3bullety] == '*') || (map[enemy3bulletx + 1][enemy3bullety] == '*') || (map[enemy3bulletx + 4][enemy3bullety] == '*')) {

			enemy3bulletstatus = 1;
			enemy3bulletdir = 0;

			map[enemy3bulletx][enemy3bullety] = ' ';
		}
		else {
			map[enemy3bulletx][enemy3bullety] = ' ';
			enemy3bulletx++;
			map[enemy3bulletx][enemy3bullety] = '|';
			enemy3bulletstatus = 0;
		}
	}
	if (enemy3bulletdir == 2) {

		if ((map[enemy3bulletx - 2][enemy3bullety] != ' ') || (map[enemy3bulletx - 2][enemy3bullety] == '*') || (map[enemy3bulletx - 1][enemy3bullety] == '*') || (map[enemy3bulletx - 4][enemy3bullety] == '*')) {

			enemy3bulletstatus = 1;
			enemy3bulletdir = 0;

			map[enemy3bulletx][enemy3bullety] = ' ';
		}
		else {

			map[enemy3bulletx][enemy3bullety] = ' ';
			enemy3bulletx--;
			map[enemy3bulletx][enemy3bullety] = '|';
			enemy3bulletstatus = 0;
		}
	}
	if (enemy3bulletdir == 3) {

		if (map[enemy3bulletx][enemy3bullety - 2] != ' ' || map[enemy3bulletx][enemy3bullety - 2] == '*' || map[enemy3bulletx][enemy3bullety - 1] == '*' || map[enemy3bulletx][enemy3bullety - 0] == '*') {
			enemy3bulletstatus = 1;
			enemy3bulletdir = 0;

			map[enemy3bulletx][enemy3bullety] = ' ';
		}
		else {
			map[enemy3bulletx][enemy3bullety] = ' ';
			enemy3bullety--;
			map[enemy3bulletx][enemy3bullety] = '-';
			enemy3bulletstatus = 0;
		}
	}
	if (enemy3bulletdir == 4) {

		if (map[enemy3bulletx][enemy3bullety + 2] != ' ' || map[enemy3bulletx][enemy3bullety + 2] == '*') {
			enemy3bulletstatus = 1;
			enemy3bulletdir = 0;
			map[enemy3bulletx][enemy3bullety] = ' ';
		}
		else {
			map[enemy3bulletx][enemy3bullety] = ' ';
			enemy3bullety++;
			map[enemy3bulletx][enemy3bullety] = '-';
			enemy3bulletstatus = 0;
		}
	}
}

void moveenemy4bullet(char map[][50]) {
	if (enemy4bulletdir == 1) {
		if ((map[enemy4bulletx + 2][enemy4bullety] != ' ') || (map[enemy4bulletx + 2][enemy4bullety] == '*') || (map[enemy4bulletx + 1][enemy4bullety] == '*') || (map[enemy4bulletx + 4][enemy4bullety] == '*')) {
			enemy4bulletstatus = 1;
			enemy4bulletdir = 0;
			map[enemy4bulletx][enemy4bullety] = ' ';
		}
		else {
			map[enemy4bulletx][enemy4bullety] = ' ';
			enemy4bulletx++;
			map[enemy4bulletx][enemy4bullety] = '|';
			enemy4bulletstatus = 0;
		}
	}
	if (enemy4bulletdir == 2) {
		if ((map[enemy4bulletx - 2][enemy4bullety] != ' ') || (map[enemy4bulletx - 2][enemy4bullety] == '*') || (map[enemy4bulletx - 1][enemy4bullety] == '*') || (map[enemy4bulletx - 4][enemy4bullety] == '*')) {
			enemy4bulletstatus = 1;
			enemy4bulletdir = 0;
			map[enemy4bulletx][enemy4bullety] = ' ';
		}
		else {
			map[enemy4bulletx][enemy4bullety] = ' ';
			enemy4bulletx--;
			map[enemy4bulletx][enemy4bullety] = '|';
			enemy4bulletstatus = 0;
		}
	}
	if (enemy4bulletdir == 3) {
		if (map[enemy4bulletx][enemy4bullety - 2] != ' ' || map[enemy4bulletx][enemy4bullety - 2] == '*' || map[enemy4bulletx][enemy4bullety - 1] == '*' || map[enemy4bulletx][enemy4bullety - 0] == '*') {
			enemy4bulletstatus = 1;
			enemy4bulletdir = 0;
			map[enemy4bulletx][enemy4bullety] = ' ';
		}
		else {
			map[enemy4bulletx][enemy4bullety] = ' ';
			enemy4bullety--;
			map[enemy4bulletx][enemy4bullety] = '-';
			enemy4bulletstatus = 0;
		}
	}
	if (enemy4bulletdir == 4) {
		if (map[enemy4bulletx][enemy4bullety + 2] != ' ' || map[enemy4bulletx][enemy4bullety + 2] == '*') {
			enemy4bulletstatus = 1;
			enemy4bulletdir = 0;
			map[enemy4bulletx][enemy4bullety] = ' ';
		}
		else {
			map[enemy4bulletx][enemy4bullety] = ' ';
			enemy4bullety++;
			map[enemy4bulletx][enemy4bullety] = '-';
			enemy4bulletstatus = 0;
		}
	}
}

void moveenemy5bullet(char map[][50]) {
	if (enemy5bulletdir == 1) {
		if ((map[enemy5bulletx + 2][enemy5bullety] != ' ') || (map[enemy5bulletx + 2][enemy5bullety] == '*') || (map[enemy5bulletx + 1][enemy5bullety] == '*') || (map[enemy5bulletx + 4][enemy5bullety] == '*')) {
			enemy5bulletstatus = 1;
			enemy5bulletdir = 0;
			map[enemy5bulletx][enemy5bullety] = ' ';
		}
		else {
			map[enemy5bulletx][enemy5bullety] = ' ';
			enemy5bulletx++;
			map[enemy5bulletx][enemy5bullety] = '|';
			enemy5bulletstatus = 0;
		}
	}
	if (enemy5bulletdir == 2) {
		if ((map[enemy5bulletx - 2][enemy5bullety] != ' ') || (map[enemy5bulletx - 2][enemy5bullety] == '*') || (map[enemy5bulletx - 1][enemy5bullety] == '*') || (map[enemy5bulletx - 4][enemy5bullety] == '*')) {
			enemy5bulletstatus = 1;
			enemy5bulletdir = 0;
			map[enemy5bulletx][enemy5bullety] = ' ';
		}
		else {
			map[enemy5bulletx][enemy5bullety] = ' ';
			enemy5bulletx--;
			map[enemy5bulletx][enemy5bullety] = '|';
			enemy5bulletstatus = 0;
		}
	}
	if (enemy5bulletdir == 3) {
		if (map[enemy5bulletx][enemy5bullety - 2] != ' ' || map[enemy5bulletx][enemy5bullety - 2] == '*' || map[enemy5bulletx][enemy5bullety - 1] == '*' || map[enemy5bulletx][enemy5bullety - 0] == '*') {
			enemy5bulletstatus = 1;
			enemy5bulletdir = 0;
			map[enemy5bulletx][enemy5bullety] = ' ';
		}
		else {
			map[enemy5bulletx][enemy5bullety] = ' ';
			enemy5bullety--;
			map[enemy5bulletx][enemy5bullety] = '-';
			enemy5bulletstatus = 0;
		}
	}
	if (enemy5bulletdir == 4) {
		if (map[enemy5bulletx][enemy5bullety + 2] != ' ' || map[enemy5bulletx][enemy5bullety + 2] == '*') {
			enemy5bulletstatus = 1;
			enemy5bulletdir = 0;
			map[enemy5bulletx][enemy5bullety] = ' ';
		}
		else {
			map[enemy5bulletx][enemy5bullety] = ' ';
			enemy5bullety++;
			map[enemy5bulletx][enemy5bullety] = '-';
			enemy5bulletstatus = 0;
		}
	}
}


void moveenemy6bullet(char map[][50]) {
	if (enemy6bulletdir == 1) {
		if ((map[enemy6bulletx + 2][enemy6bullety] != ' ') || (map[enemy6bulletx + 2][enemy6bullety] == '*') || (map[enemy6bulletx + 1][enemy6bullety] == '*') || (map[enemy6bulletx + 4][enemy6bullety] == '*')) {
			enemy6bulletstatus = 1;
			enemy6bulletdir = 0;
			map[enemy6bulletx][enemy6bullety] = ' ';
		}
		else {
			map[enemy6bulletx][enemy6bullety] = ' ';
			enemy6bulletx++;
			map[enemy6bulletx][enemy6bullety] = '|';
			enemy6bulletstatus = 0;
		}
	}
	if (enemy6bulletdir == 2) {
		if ((map[enemy6bulletx - 2][enemy6bullety] != ' ') || (map[enemy6bulletx - 2][enemy6bullety] == '*') || (map[enemy6bulletx - 1][enemy6bullety] == '*') || (map[enemy6bulletx - 4][enemy6bullety] == '*')) {
			enemy6bulletstatus = 1;
			enemy6bulletdir = 0;
			map[enemy6bulletx][enemy6bullety] = ' ';
		}
		else {
			map[enemy6bulletx][enemy6bullety] = ' ';
			enemy6bulletx--;
			map[enemy6bulletx][enemy6bullety] = '|';
			enemy6bulletstatus = 0;
		}
	}
	if (enemy6bulletdir == 3) {
		if (map[enemy6bulletx][enemy6bullety - 2] != ' ' || map[enemy6bulletx][enemy6bullety - 2] == '*' || map[enemy6bulletx][enemy6bullety - 1] == '*' || map[enemy6bulletx][enemy6bullety - 0] == '*') {
			enemy6bulletstatus = 1;
			enemy6bulletdir = 0;
			map[enemy6bulletx][enemy6bullety] = ' ';
		}
		else {
			map[enemy6bulletx][enemy6bullety] = ' ';
			enemy6bullety--;
			map[enemy6bulletx][enemy6bullety] = '-';
			enemy6bulletstatus = 0;
		}
	}
	if (enemy6bulletdir == 4) {
		if (map[enemy6bulletx][enemy6bullety + 2] != ' ' || map[enemy6bulletx][enemy6bullety + 2] == '*') {
			enemy6bulletstatus = 1;
			enemy6bulletdir = 0;
			map[enemy6bulletx][enemy6bullety] = ' ';
		}
		else {
			map[enemy6bulletx][enemy6bullety] = ' ';
			enemy6bullety++;
			map[enemy6bulletx][enemy6bullety] = '-';
			enemy6bulletstatus = 0;
		}
	}
}

void enemiesspeed(char map[][50])
{
	if (level == 1)
	{
		solospeed = 12;
		enemyspeed = 20;
	}
	if (level == 2)
	{
		solospeed = 10;
		enemyspeed = 17;
	}
	if (level == 3)
	{
		solospeed = 8;
		enemyspeed = 15;
	}
	if (level == 4)
	{
		solospeed = 5;
		enemyspeed = 10;
	}
	if (level == 5)
	{
		solospeed = 2;
		enemyspeed = 7;
	}
}


void moveenemy(char map[][50], int& enemy1x, int& enemy1y, int& enemy2x, int& enemy2y, int x, int y, int x1, int y1) {

	if (enemy1status == 1 && level >= 1) {

		killenemy1(map, enemy1x, enemy1y);
		if (ismove % enemyspeed == 0)
		{
			if (ethenx > enemy1x)
			{
				enemy1x++;
				if (map[enemy1x + 3][enemy1y] == '-' || map[enemy1x + 3][enemy1y - 1] == '-' || map[enemy1x + 3][enemy1y + 1] == '-')
				{
					killenemy1(map, enemy1x, enemy1y);

					enemy1x = rand() % (25 - 5 + 2) + 6;
					enemy1y = rand() % 15 + 2;
					createenemy1(map, enemy1x, enemy1y, enemy2x, enemy2y);
					killenemy1(map, enemy1x, enemy1y);
				}
				else if (map[enemy1x + 3][enemy1y] != ' ' || map[enemy1x + 3][enemy1y - 1] != ' ' || map[enemy1x + 3][enemy1y + 1] != ' ' || map[enemy1x + 5][enemy1y] == 'O')
				{
					enemy1x--;

				}

			}
			else
			{
				enemy1x--;
				if (map[enemy1x - 1][enemy1y] == '-' || map[enemy1x - 1][enemy1y - 1] == '-' || map[enemy1x - 1][enemy1y + 1] == '-')
				{
					killenemy1(map, enemy1x, enemy1y);

					enemy1x = rand() % (25 - 5 + 2) + 6;
					enemy1y = rand() % 15 + 2;
					createenemy1(map, enemy1x, enemy1y, enemy2x, enemy2y);
					killenemy1(map, enemy1x, enemy1y);
				}
				else if (map[enemy1x + 2][enemy1y] != ' ' || map[enemy1x + 2][enemy1y + 1] != ' ' || map[enemy1x + 2][enemy1y - 1] != ' ')
				{
					enemy1x++;
				}

			}
			if (etheny > enemy1limity1 && etheny < enemy1limity2) {
				if (etheny > enemy1y) {
					enemy1y++;
					if (map[enemy1x][enemy1y + 1] == '-' || map[enemy1x + 1][enemy1y + 1] == '-') {
						killenemy1(map, enemy1x, enemy1y);

						enemy1x = rand() % (25 - 5 + 2) + 6;
						enemy1y = rand() % 15 + 2;
						createenemy1(map, enemy1x, enemy1y, enemy2x, enemy2y);
						killenemy1(map, enemy1x, enemy1y);
					}
					else if (map[enemy1x][enemy1y + 2] != ' ' || map[enemy1x + 1][enemy1y + 2] != ' ')
					{
						enemy1y--;
					}
				}
				else {
					enemy1y--;
					if (map[enemy1x][enemy1y - 1] == '-' || map[enemy1x + 1][enemy1y - 1] == '-')
					{
						killenemy1(map, enemy1x, enemy1y);

						enemy1x = rand() % (25 - 5 + 2) + 6;
						enemy1y = rand() % 15 + 2;
						createenemy1(map, enemy1x, enemy1y, enemy2x, enemy2y);
						killenemy1(map, enemy1x, enemy1y);
					}
					else if (map[enemy1x][enemy1y - 2] != ' ' || map[enemy1x + 1][enemy1y - 2] != ' ') {
						enemy1y++;
					}
				}
			}

		}
		createenemy1(map, enemy1x, enemy1y, enemy2x, enemy2y);

		if (enemy1bulletstatus == 1) {

			if (enemy1x < ethenx && enemy1y == etheny) {
				enemy1bulletx = enemy1x + 2;
				enemy1bullety = enemy1y;
				map[enemy1bulletx][enemy1bullety] = '|';
				enemy1bulletdir = 1;
			}
			if (enemy1x > ethenx && enemy1y == etheny) {
				enemy1bulletx = enemy1x - 2;
				enemy1bullety = enemy1y;
				map[enemy1bulletx][enemy1bullety] = '|';
				enemy1bulletdir = 2;
			}
			if (enemy1y > etheny && ((enemy1x == ethenx) || (enemy1x + 1 == ethenx) || (enemy1x - 1 == ethenx))) {

				enemy1bulletx = enemy1x + 1;
				enemy1bullety = enemy1y - 2;
				map[enemy1bulletx][enemy1bullety] = '-';
				enemy1bulletdir = 3;
			}
			if (enemy1y < etheny && ((enemy1x == ethenx) || (enemy1x + 1 == ethenx) || (enemy1x - 1 == ethenx))) {

				enemy1bulletx = enemy1x + 1;
				enemy1bullety = enemy1y + 2;
				map[enemy1bulletx][enemy1bullety] = '-';
				enemy1bulletdir = 4;
			}

		}

		if (map[enemy1x + 2][enemy1y] == '*' || map[enemy1x + 2][enemy1y + 1] == '*' || map[enemy1x + 2][enemy1y - 1] == '*' || map[enemy1x + 5][enemy1y] == '^' || map[enemy1x + 5][enemy1y + 1] == '^' || map[enemy1x + 5][enemy1y - 1] == '^') {
			killenemy1(map, enemy1x, enemy1y);
			killenemy1(map, enemy1x, enemy1y);
			killenemy1(map, enemy1x, enemy1y);

			enemy1status = 0;
			score += 2;

		}





	}




	if (enemy2status == 1 && level >= 1) {

		killenemy1(map, enemy2x, enemy2y);


		if (ismove % enemyspeed == 0)
		{
			if (ethenx > enemy2x) {
				enemy2x++;
				if (map[enemy2x + 1][enemy2y] == '-' || map[enemy2x + 1][enemy2y - 1] == '-' || map[enemy2x + 1][enemy2y + 1] == '-')
				{
					killenemy1(map, enemy2x, enemy2y);

					enemy2x = rand() % (25 - 5 + 1) + 5;
					enemy2y = rand() % (26 - 16 + 1) + 16;
					createenemy2(map, enemy1x, enemy1y, enemy2x, enemy2y);
					killenemy1(map, enemy2x, enemy2y);

				}
				else if (map[enemy2x + 3][enemy2y] != ' ' || map[enemy2x + 3][enemy2y - 1] != ' ' || map[enemy2x + 3][enemy2y + 1] != ' ') {
					enemy2x--;
				}

			}
			else {
				enemy2x--;
				if (map[enemy2x - 1][enemy2y] == '-' || map[enemy2x - 1][enemy2y - 1] == '-' || map[enemy2x - 1][enemy2y + 1] == '-') {
					killenemy1(map, enemy2x, enemy2y);

					enemy2x = rand() % (25 - 5 + 1) + 5;
					enemy2y = rand() % (26 - 16 + 1) + 16;
					createenemy2(map, enemy1x, enemy1y, enemy2x, enemy2y);
					killenemy1(map, enemy2x, enemy2y);

				}
				else if (map[enemy2x - 3][enemy2y] != ' ' || map[enemy2x - 3][enemy2y + 1] != ' ' || map[enemy2x - 3][enemy2y - 1] != ' ') {
					enemy2x++;
				}

			}
			if (etheny > enemy2limity1 && etheny < enemy2limity2) {
				if (etheny > enemy2y) {
					enemy2y++;
					if (map[enemy2x][enemy2y + 1] == '-' || map[enemy2x + 1][enemy2y + 1] == '-') {
						killenemy1(map, enemy2x, enemy2y);

						enemy2x = rand() % (25 - 5 + 1) + 5;
						enemy2y = rand() % (26 - 16 + 1) + 16;
						createenemy2(map, enemy1x, enemy1y, enemy2x, enemy2y);
						killenemy1(map, enemy2x, enemy2y);

					}
					else if (map[enemy2x][enemy2y + 2] != ' ' || map[enemy2x + 1][enemy2y + 1] != ' ')
					{
						enemy2y--;
					}
				}
				else {
					enemy2y--;
					if (map[enemy2x][enemy2y - 1] == '-' || map[enemy2x + 1][enemy2y - 1] == '-') {
						killenemy1(map, enemy2x, enemy2y);

						enemy2x = rand() % (25 - 5 + 1) + 5;
						enemy2y = rand() % (26 - 16 + 1) + 16;
						createenemy2(map, enemy1x, enemy1y, enemy2x, enemy2y);
						killenemy1(map, enemy2x, enemy2y);

					}
					else if (map[enemy2x][enemy2y - 2] != ' ' || map[enemy2x + 1][enemy2y - 2] != ' ')
					{
						enemy2y++;
					}
				}
			}


		}
		createenemy2(map, enemy1x, enemy1y, enemy2x, enemy2y);

		if (enemy2bulletstatus == 1) {

			if (enemy2x < ethenx && enemy2y == etheny) {
				enemy2bulletx = enemy2x + 2;
				enemy2bullety = enemy2y;
				map[enemy2bulletx][enemy2bullety] = '|';
				enemy2bulletdir = 1;
			}
			if (enemy2x > ethenx && enemy2y == etheny) {
				enemy2bulletx = enemy2x - 2;
				enemy2bullety = enemy2y;
				map[enemy2bulletx][enemy2bullety] = '|';
				enemy2bulletdir = 2;
			}
			if (enemy2y > etheny && ((enemy2x == ethenx) || (enemy2x + 1 == ethenx) || (enemy2x - 1 == ethenx))) {

				enemy2bulletx = enemy2x + 1;
				enemy2bullety = enemy2y - 3;
				map[enemy2bulletx][enemy2bullety] = '-';
				enemy2bulletdir = 3;
			}
			if (enemy2y < etheny && ((enemy2x == ethenx) || (enemy2x + 1 == ethenx) || (enemy2x - 1 == ethenx))) {

				enemy2bulletx = enemy2x + 1;
				enemy2bullety = enemy2y + 3;
				map[enemy2bulletx][enemy2bullety] = '-';
				enemy2bulletdir = 4;
			}

		}


	}

	if (enemy3status == 1 && level >= 2) {
		killenemy1(map, enemy3x, enemy3y);
		if (ismove % enemyspeed == 0) {
			if (ethenx > enemy3x) {
				enemy3x++;
				if (map[enemy3x + 3][enemy3y] == '-' || map[enemy3x + 3][enemy3y - 1] == '-' || map[enemy3x + 3][enemy3y + 1] == '-') {
					killenemy1(map, enemy3x, enemy3y);

					enemy3x = rand() % (25 - 5 + 2) + 6;
					enemy3y = rand() % 15 + 2;
					createenemy1(map, enemy3x, enemy3y, enemy2x, enemy2y);
					killenemy1(map, enemy3x, enemy3y);

				}
				else if (map[enemy3x + 3][enemy3y] != ' ' || map[enemy3x + 3][enemy3y - 1] != ' ' || map[enemy3x + 3][enemy3y + 1] != ' ' || map[enemy3x + 5][enemy3y] == 'O') {
					enemy3x--;
				}
			}
			else {
				enemy3x--;
				if (map[enemy3x - 1][enemy3y] == '-' || map[enemy3x - 1][enemy3y - 1] == '-' || map[enemy3x - 1][enemy3y + 1] == '-') {
					killenemy1(map, enemy3x, enemy3y);

					enemy3x = rand() % (25 - 5 + 2) + 6;
					enemy3y = rand() % 15 + 2;
					createenemy1(map, enemy3x, enemy3y, enemy2x, enemy2y);
					killenemy1(map, enemy3x, enemy3y);

				}
				else if (map[enemy3x + 2][enemy3y] != ' ' || map[enemy3x + 2][enemy3y + 1] != ' ' || map[enemy3x + 2][enemy3y - 1] != ' ') {
					enemy3x++;
				}
			}
			if (etheny > enemy3limity1 && etheny < enemy3limity2) {
				if (etheny > enemy3y) {
					enemy3y++;
					if (map[enemy3x][enemy3y + 1] == '-' || map[enemy3x + 1][enemy3y + 1] == '-') {
						killenemy1(map, enemy3x, enemy3y);

						enemy3x = rand() % (25 - 5 + 2) + 6;
						enemy3y = rand() % 15 + 2;
						createenemy1(map, enemy3x, enemy3y, enemy2x, enemy2y);
						killenemy1(map, enemy3x, enemy3y);

					}
					else if (map[enemy3x][enemy3y + 2] != ' ' || map[enemy3x + 1][enemy3y + 2] != ' ') {
						enemy3y--;
					}
				}
				else {
					enemy3y--;
					if (map[enemy3x][enemy3y - 1] == '-' || map[enemy3x + 1][enemy3y - 1] == '-') {
						killenemy1(map, enemy3x, enemy3y);
						enemy3x = rand() % (25 - 5 + 2) + 6;
						enemy3y = rand() % 15 + 2;
						createenemy1(map, enemy3x, enemy3y, enemy2x, enemy2y);
						killenemy1(map, enemy3x, enemy3y);

					}
					else if (map[enemy3x][enemy3y - 2] != ' ' || map[enemy3x + 1][enemy3y - 2] != ' ') {
						enemy3y++;
					}
				}
			}
		}
		createenemy1(map, enemy3x, enemy3y, enemy2x, enemy2y);
		if (enemy3bulletstatus == 1) {
			if (enemy3x < ethenx && enemy3y == etheny) {
				enemy3bulletx = enemy3x + 2;
				enemy3bullety = enemy3y;
				map[enemy3bulletx][enemy3bullety] = '|';
				enemy3bulletdir = 1;
			}
			if (enemy3x > ethenx && enemy3y == etheny) {
				enemy3bulletx = enemy3x - 2;
				enemy3bullety = enemy3y;
				map[enemy3bulletx][enemy3bullety] = '|';
				enemy3bulletdir = 2;
			}
			if (enemy3y > etheny && ((enemy3x == ethenx) || (enemy3x + 1 == ethenx) || (enemy3x - 1 == ethenx))) {
				enemy3bulletx = enemy3x + 1;
				enemy3bullety = enemy3y - 2;
				map[enemy3bulletx][enemy3bullety] = '-';
				enemy3bulletdir = 3;
			}
			if (enemy3y < etheny && ((enemy3x == ethenx) || (enemy3x + 1 == ethenx) || (enemy3x - 1 == ethenx))) {
				enemy3bulletx = enemy3x + 1;
				enemy3bullety = enemy3y + 2;
				map[enemy3bulletx][enemy3bullety] = '-';
				enemy3bulletdir = 4;
			}
		}
		if (map[enemy3x + 2][enemy3y] == '*' || map[enemy3x + 2][enemy3y + 1] == '*' || map[enemy3x + 2][enemy3y - 1] == '*' || map[enemy3x + 5][enemy3y] == '^' || map[enemy3x + 5][enemy3y + 1] == '^' || map[enemy3x + 5][enemy3y - 1] == '^') {
			killenemy1(map, enemy3x, enemy3y);
			killenemy1(map, enemy3x, enemy3y);
			killenemy1(map, enemy3x, enemy3y);
			enemy3status = 0;
			score += 2;
		}
	}



	if (enemy4status == 1 && level >= 3) {
		killenemy1(map, enemy4x, enemy4y);
		if (ismove % enemyspeed == 0) {
			if (ethenx > enemy4x) {
				enemy4x++;
				if (map[enemy4x + 3][enemy4y] == '-' || map[enemy4x + 3][enemy4y - 1] == '-' || map[enemy4x + 3][enemy4y + 1] == '-') {
					killenemy1(map, enemy4x, enemy4y);
					enemy4x = rand() % (25 - 5 + 1) + 5;
					enemy4y = rand() % 14 + 1;
					createenemy1(map, enemy4x, enemy4y, enemy2x, enemy2y);
					killenemy1(map, enemy4x, enemy4y);

				}
				else if (map[enemy4x + 3][enemy4y] != ' ' || map[enemy4x + 3][enemy4y - 1] != ' ' || map[enemy4x + 3][enemy4y + 1] != ' ' || map[enemy4x + 5][enemy4y] == 'O') {
					enemy4x--;
				}
			}
			else {
				enemy4x--;
				if (map[enemy4x - 1][enemy4y] == '-' || map[enemy4x - 1][enemy4y - 1] == '-' || map[enemy4x - 1][enemy4y + 1] == '-') {
					killenemy1(map, enemy4x, enemy4y);

					enemy4x = rand() % (25 - 5 + 1) + 5;
					enemy4y = rand() % 14 + 1;
					createenemy1(map, enemy4x, enemy4y, enemy2x, enemy2y);
					killenemy1(map, enemy4x, enemy4y);

				}
				else if (map[enemy4x + 2][enemy4y] != ' ' || map[enemy4x + 2][enemy4y + 1] != ' ' || map[enemy4x + 2][enemy4y - 1] != ' ') {
					enemy4x++;
				}
			}
			if (etheny > enemy4limity1 && etheny < enemy4limity2) {
				if (etheny > enemy4y) {
					enemy4y++;
					if (map[enemy4x][enemy4y + 1] == '-' || map[enemy4x + 1][enemy4y + 1] == '-') {
						killenemy1(map, enemy4x, enemy4y);

						enemy4x = rand() % (25 - 5 + 1) + 5;
						enemy4y = rand() % 14 + 1;
						createenemy1(map, enemy4x, enemy4y, enemy2x, enemy2y);
						killenemy1(map, enemy4x, enemy4y);

					}
					else if (map[enemy4x][enemy4y + 2] != ' ' || map[enemy4x + 1][enemy4y + 2] != ' ') {
						enemy4y--;
					}
				}
				else {
					enemy4y--;
					if (map[enemy4x][enemy4y - 1] == '-' || map[enemy4x + 1][enemy4y - 1] == '-') {
						killenemy1(map, enemy4x, enemy4y);

						enemy4x = rand() % (25 - 5 + 1) + 5;
						enemy4y = rand() % 14 + 1;
						createenemy1(map, enemy4x, enemy4y, enemy2x, enemy2y);
						killenemy1(map, enemy4x, enemy4y);

					}
					else if (map[enemy4x][enemy4y - 2] != ' ' || map[enemy4x + 1][enemy4y - 2] != ' ') {
						enemy4y++;
					}
				}
			}
		}
		createenemy1(map, enemy4x, enemy4y, enemy2x, enemy2y);
		if (enemy4bulletstatus == 1) {
			if (enemy4x < ethenx && enemy4y == etheny) {
				enemy4bulletx = enemy4x + 2;
				enemy4bullety = enemy4y;
				map[enemy4bulletx][enemy4bullety] = '|';
				enemy4bulletdir = 1;
			}
			if (enemy4x > ethenx && enemy4y == etheny) {
				enemy4bulletx = enemy4x - 2;
				enemy4bullety = enemy4y;
				map[enemy4bulletx][enemy4bullety] = '|';
				enemy4bulletdir = 2;
			}
			if (enemy4y > etheny && ((enemy4x == ethenx) || (enemy4x + 1 == ethenx) || (enemy4x - 1 == ethenx))) {
				enemy4bulletx = enemy4x + 1;
				enemy4bullety = enemy4y - 2;
				map[enemy4bulletx][enemy4bullety] = '-';
				enemy4bulletdir = 3;
			}
			if (enemy4y < etheny && ((enemy4x == ethenx) || (enemy4x + 1 == ethenx) || (enemy4x - 1 == ethenx))) {
				enemy4bulletx = enemy4x + 1;
				enemy4bullety = enemy4y + 2;
				map[enemy4bulletx][enemy4bullety] = '-';
				enemy4bulletdir = 4;
			}
		}
		if (map[enemy4x + 2][enemy4y] == '*' || map[enemy4x + 2][enemy4y + 1] == '*' || map[enemy4x + 2][enemy4y - 1] == '*' || map[enemy4x + 5][enemy4y] == '^' || map[enemy4x + 5][enemy4y + 1] == '^' || map[enemy4x + 5][enemy4y - 1] == '^') {
			killenemy1(map, enemy4x, enemy4y);
			killenemy1(map, enemy4x, enemy4y);
			killenemy1(map, enemy4x, enemy4y);
			enemy4status = 0;
			score += 2;
		}
	}

	if (enemy5status == 1 && level >= 4) {
		killenemy1(map, enemy5x, enemy5y);
		if (ismove % enemyspeed == 0) {

			if (ethenx > enemy5x) {
				enemy5x++;
				if (map[enemy5x + 3][enemy5y] == '-' || map[enemy5x + 3][enemy5y - 1] == '-' || map[enemy5x + 3][enemy5y + 1] == '-') {
					killenemy1(map, enemy5x, enemy5y);

					enemy5x = rand() % (25 - 5 + 1) + 5;
					enemy5y = rand() % 14 + 1;
					createenemy1(map, enemy5x, enemy5y, enemy2x, enemy2y);
					killenemy1(map, enemy5x, enemy5y);

				}
				else if (map[enemy5x + 3][enemy5y] != ' ' || map[enemy5x + 3][enemy5y - 1] != ' ' || map[enemy5x + 3][enemy5y + 1] != ' ' || map[enemy5x + 5][enemy5y] == 'O') {
					enemy5x--;
				}
			}
			else {
				enemy5x--;
				if (map[enemy5x - 1][enemy5y] == '-' || map[enemy5x - 1][enemy5y - 1] == '-' || map[enemy5x - 1][enemy5y + 1] == '-') {
					killenemy1(map, enemy5x, enemy5y);

					enemy5x = rand() % (25 - 5 + 1) + 5;
					enemy5y = rand() % 14 + 1;
					createenemy1(map, enemy5x, enemy5y, enemy2x, enemy2y);
					killenemy1(map, enemy5x, enemy5y);

				}
				else if (map[enemy5x + 2][enemy5y] != ' ' || map[enemy5x + 2][enemy5y + 1] != ' ' || map[enemy5x + 2][enemy5y - 1] != ' ') {
					enemy5x++;
				}
			}
			if (etheny > enemy5limity1 && etheny < enemy5limity2) {
				if (etheny > enemy5y) {
					enemy5y++;
					if (map[enemy5x][enemy5y + 1] == '-' || map[enemy5x + 1][enemy5y + 1] == '-') {
						killenemy1(map, enemy5x, enemy5y);

						enemy5x = rand() % (25 - 5 + 1) + 5;
						enemy5y = rand() % 14 + 1;
						createenemy1(map, enemy5x, enemy5y, enemy2x, enemy2y);
						killenemy1(map, enemy5x, enemy5y);

					}
					else if (map[enemy5x][enemy5y + 2] != ' ' || map[enemy5x + 1][enemy5y + 2] != ' ') {
						enemy5y--;
					}
				}
				else {
					enemy5y--;
					if (map[enemy5x][enemy5y - 1] == '-' || map[enemy5x + 1][enemy5y - 1] == '-') {
						killenemy1(map, enemy5x, enemy5y);

						enemy5x = rand() % (25 - 5 + 1) + 5;
						enemy5y = rand() % 14 + 1;
						createenemy1(map, enemy5x, enemy5y, enemy2x, enemy2y);
						killenemy1(map, enemy5x, enemy5y);

					}
					else if (map[enemy5x][enemy5y - 2] != ' ' || map[enemy5x + 1][enemy5y - 2] != ' ') {
						enemy5y++;
					}
				}
			}
		}
		createenemy1(map, enemy5x, enemy5y, enemy2x, enemy2y);
		if (enemy5bulletstatus == 1) {
			if (enemy5x < ethenx && enemy5y == etheny) {
				enemy5bulletx = enemy5x + 2;
				enemy5bullety = enemy5y;
				map[enemy5bulletx][enemy5bullety] = '|';
				enemy5bulletdir = 1;
			}
			if (enemy5x > ethenx && enemy5y == etheny) {
				enemy5bulletx = enemy5x - 2;
				enemy5bullety = enemy5y;
				map[enemy5bulletx][enemy5bullety] = '|';
				enemy5bulletdir = 2;
			}
			if (enemy5y > etheny && ((enemy5x == ethenx) || (enemy5x + 1 == ethenx) || (enemy5x - 1 == ethenx))) {
				enemy5bulletx = enemy5x + 1;
				enemy5bullety = enemy5y - 2;
				map[enemy5bulletx][enemy5bullety] = '-';
				enemy5bulletdir = 3;
			}
			if (enemy5y < etheny && ((enemy5x == ethenx) || (enemy5x + 1 == ethenx) || (enemy5x - 1 == ethenx))) {
				enemy5bulletx = enemy5x + 1;
				enemy5bullety = enemy5y + 2;
				map[enemy5bulletx][enemy5bullety] = '-';
				enemy5bulletdir = 4;
			}
		}
		if (map[enemy5x + 2][enemy5y] == '*' || map[enemy5x + 2][enemy5y + 1] == '*' || map[enemy5x + 2][enemy5y - 1] == '*' || map[enemy5x + 5][enemy5y] == '^' || map[enemy5x + 5][enemy5y + 1] == '^' || map[enemy5x + 5][enemy5y - 1] == '^') {
			killenemy1(map, enemy5x, enemy5y);
			killenemy1(map, enemy5x, enemy5y);
			killenemy1(map, enemy5x, enemy5y);
			enemy5status = 0;
			score += 2;
		}
	}

	if (enemy6status == 1 && level >= 5) {
		killenemy1(map, enemy6x, enemy6y);
		if (ismove % enemyspeed == 0) {

			if (ethenx > enemy6x) {
				enemy6x++;
				if (map[enemy6x + 3][enemy6y] == '-' || map[enemy6x + 3][enemy6y - 1] == '-' || map[enemy6x + 3][enemy6y + 1] == '-') {
					killenemy1(map, enemy6x, enemy6y);

					enemy6x = rand() % (25 - 5 + 1) + 5;
					enemy6y = rand() % 14 + 1;
					createenemy1(map, enemy6x, enemy6y, enemy2x, enemy2y);
					killenemy1(map, enemy6x, enemy6y);

				}
				else if (map[enemy6x + 3][enemy6y] != ' ' || map[enemy6x + 3][enemy6y - 1] != ' ' || map[enemy6x + 3][enemy6y + 1] != ' ' || map[enemy6x + 5][enemy6y] == 'O') {
					enemy6x--;
				}
			}
			else {
				enemy6x--;
				if (map[enemy6x - 1][enemy6y] == '-' || map[enemy6x - 1][enemy6y - 1] == '-' || map[enemy6x - 1][enemy6y + 1] == '-') {
					killenemy1(map, enemy6x, enemy6y);

					enemy6x = rand() % (25 - 5 + 1) + 5;
					enemy6y = rand() % 14 + 1;
					createenemy1(map, enemy6x, enemy6y, enemy2x, enemy2y);
					killenemy1(map, enemy6x, enemy6y);

				}
				else if (map[enemy6x + 2][enemy6y] != ' ' || map[enemy6x + 2][enemy6y + 1] != ' ' || map[enemy6x + 2][enemy6y - 1] != ' ') {
					enemy6x++;
				}
			}
			if (etheny > enemy6limity1 && etheny < enemy6limity2) {
				if (etheny > enemy6y) {
					enemy6y++;
					if (map[enemy6x][enemy6y + 1] == '-' || map[enemy6x + 1][enemy6y + 1] == '-') {
						killenemy1(map, enemy6x, enemy6y);

						enemy6x = rand() % (25 - 5 + 1) + 5;
						enemy6y = rand() % 14 + 1;
						createenemy1(map, enemy6x, enemy6y, enemy2x, enemy2y);
						killenemy1(map, enemy6x, enemy6y);

					}
					else if (map[enemy6x][enemy6y + 2] != ' ' || map[enemy6x + 1][enemy6y + 2] != ' ') {
						enemy6y--;
					}
				}
				else {
					enemy6y--;
					if (map[enemy6x][enemy6y - 1] == '-' || map[enemy6x + 1][enemy6y - 1] == '-') {
						killenemy1(map, enemy6x, enemy6y);

						enemy6x = rand() % (25 - 5 + 1) + 5;
						enemy6y = rand() % 14 + 1;
						createenemy1(map, enemy6x, enemy6y, enemy2x, enemy2y);
						killenemy1(map, enemy6x, enemy6y);

					}
					else if (map[enemy6x][enemy6y - 2] != ' ' || map[enemy6x + 1][enemy6y - 2] != ' ') {
						enemy6y++;
					}
				}
			}
		}
		createenemy1(map, enemy6x, enemy6y, enemy2x, enemy2y);
		if (enemy6bulletstatus == 1) {
			if (enemy6x < ethenx && enemy6y == etheny) {
				enemy6bulletx = enemy6x + 2;
				enemy6bullety = enemy6y;
				map[enemy6bulletx][enemy6bullety] = '|';
				enemy6bulletdir = 1;
			}
			if (enemy6x > ethenx && enemy6y == etheny) {
				enemy6bulletx = enemy6x - 2;
				enemy6bullety = enemy6y;
				map[enemy6bulletx][enemy6bullety] = '|';
				enemy6bulletdir = 2;
			}
			if (enemy6y > etheny && ((enemy6x == ethenx) || (enemy6x + 1 == ethenx) || (enemy6x - 1 == ethenx))) {
				enemy6bulletx = enemy6x + 1;
				enemy6bullety = enemy6y - 2;
				map[enemy6bulletx][enemy6bullety] = '-';
				enemy6bulletdir = 3;
			}
			if (enemy6y < etheny && ((enemy6x == ethenx) || (enemy6x + 1 == ethenx) || (enemy6x - 1 == ethenx))) {
				enemy6bulletx = enemy6x + 1;
				enemy6bullety = enemy6y + 2;
				map[enemy6bulletx][enemy6bullety] = '-';
				enemy6bulletdir = 4;
			}
		}
		if (map[enemy6x + 2][enemy6y] == '*' || map[enemy6x + 2][enemy6y + 1] == '*' || map[enemy6x + 2][enemy6y - 1] == '*' || map[enemy6x + 5][enemy6y] == '^' || map[enemy6x + 5][enemy6y + 1] == '^' || map[enemy6x + 5][enemy6y - 1] == '^') {
			killenemy1(map, enemy6x, enemy6y);
			killenemy1(map, enemy6x, enemy6y);
			killenemy1(map, enemy6x, enemy6y);
			enemy6status = 0;
			score += 2;
		}
	}







}
void checkenemy1life(char map[][50]) {
	if (map[enemy1x - 1][enemy1y] == '*' || map[enemy1x - 1][enemy1y + 1] == '*' || map[enemy1x - 1][enemy1y - 1] == '*' || map[enemy1x - 1][enemy1y] == '^' || map[enemy1x - 1][enemy1y + 1] == '^' || map[enemy1x - 1][enemy1y - 1] == '^') {
		killenemy1(map, enemy1x, enemy1y);
		enemy1status = 0;
		score += 2;

	}
	if (map[enemy1x + 2][enemy1y] == '*' || map[enemy1x + 2][enemy1y + 1] == '*' || map[enemy1x + 2][enemy1y - 1] == '*' || map[enemy1x + 5][enemy1y] == '^' || map[enemy1x + 5][enemy1y + 1] == '^' || map[enemy1x + 5][enemy1y - 1] == '^') {
		killenemy1(map, enemy1x, enemy1y);
		killenemy1(map, enemy1x, enemy1y);
		killenemy1(map, enemy1x, enemy1y);


		enemy1status = 0;
		score += 2;

	}
	if (map[enemy1x][enemy1y + 2] == '*' || map[enemy1x + 1][enemy1y + 2] == '*' || map[enemy1x][enemy1y + 2] == '<' || map[enemy1x + 1][enemy1y + 2] == '<') {
		killenemy1(map, enemy1x, enemy1y);
		killenemy1(map, enemy1x, enemy1y);

		enemy1status = 0;
		score += 2;

	}
	if (map[enemy1x][enemy1y - 2] == '*' || map[enemy1x + 1][enemy1y - 2] == '*' || map[enemy1x][enemy1y - 2] == '>' || map[enemy1x + 1][enemy1y - 2] == '>') {
		killenemy1(map, enemy1x, enemy1y);

		enemy1status = 0;
		score += 2;

	}

}
void checkenemy2life(char map[][50]) {
	if (map[enemy2x - 1][enemy2y] == '*' || map[enemy2x - 1][enemy2y + 1] == '*' || map[enemy2x - 1][enemy2y - 1] == '*' || map[enemy2x - 1][enemy2y] == '^' || map[enemy2x - 1][enemy2y + 1] == '^' || map[enemy2x - 1][enemy2y - 1] == '^') {
		killenemy1(map, enemy2x, enemy2y);
		enemy2status = 0;
		score += 2;

	}
	if (map[enemy2x + 2][enemy2y] == '*' || map[enemy2x + 2][enemy2y + 1] == '*' || map[enemy2x + 2][enemy2y - 1] == '*' || map[enemy2x + 2][enemy2y] == '^' || map[enemy2x + 2][enemy2y + 1] == '^' || map[enemy2x + 2][enemy2y - 1] == '^') {
		killenemy1(map, enemy2x, enemy2y);
		enemy2status = 0;
		score += 2;

	}
	if (map[enemy2x][enemy2y + 2] == '*' || map[enemy2x + 1][enemy2y + 2] == '*' || map[enemy2x][enemy2y + 2] == '<' || map[enemy2x + 1][enemy2y + 2] == '<') {
		killenemy1(map, enemy2x, enemy2y);
		enemy2status = 0;
		score += 2;

	}
	if (map[enemy2x][enemy2y - 2] == '*' || map[enemy2x + 1][enemy2y - 2] == '*' || map[enemy2x][enemy2y - 2] == '>' || map[enemy2x + 1][enemy2y - 2] == '>') {
		killenemy1(map, enemy2x, enemy2y);
		enemy2status = 0;
		score += 2;

	}

}
void checkenemy3life(char map[][50]) {
	if (map[enemy3x - 1][enemy3y] == '*' || map[enemy3x - 1][enemy3y + 1] == '*' || map[enemy3x - 1][enemy3y - 1] == '*' || map[enemy3x - 1][enemy3y] == '^' || map[enemy3x - 1][enemy3y + 1] == '^' || map[enemy3x - 1][enemy3y - 1] == '^') {
		killenemy1(map, enemy3x, enemy3y);
		enemy3status = 0;
		score += 2;
	}
	if (map[enemy3x + 2][enemy3y] == '*' || map[enemy3x + 2][enemy3y + 1] == '*' || map[enemy3x + 2][enemy3y - 1] == '*' || map[enemy3x + 2][enemy3y] == '^' || map[enemy3x + 2][enemy3y + 1] == '^' || map[enemy3x + 2][enemy3y - 1] == '^') {
		killenemy1(map, enemy3x, enemy3y);
		enemy3status = 0;
		score += 2;
	}
	if (map[enemy3x][enemy3y + 2] == '*' || map[enemy3x + 1][enemy3y + 2] == '*' || map[enemy3x][enemy3y + 2] == '<' || map[enemy3x + 1][enemy3y + 2] == '<') {
		killenemy1(map, enemy3x, enemy3y);
		enemy3status = 0;
		score += 2;
	}
	if (map[enemy3x][enemy3y - 2] == '*' || map[enemy3x + 1][enemy3y - 2] == '*' || map[enemy3x][enemy3y - 2] == '>' || map[enemy3x + 1][enemy3y - 2] == '>') {
		killenemy1(map, enemy3x, enemy3y);
		enemy3status = 0;
		score += 2;
	}
}
void checkenemy4life(char map[][50]) {
	if (map[enemy4x - 1][enemy4y] == '*' || map[enemy4x - 1][enemy4y + 1] == '*' || map[enemy4x - 1][enemy4y - 1] == '*' || map[enemy4x - 1][enemy4y] == '^' || map[enemy4x - 1][enemy4y + 1] == '^' || map[enemy4x - 1][enemy4y - 1] == '^') {
		killenemy1(map, enemy4x, enemy4y);
		enemy4status = 0;
		score += 2;
	}
	if (map[enemy4x + 2][enemy4y] == '*' || map[enemy4x + 2][enemy4y + 1] == '*' || map[enemy4x + 2][enemy4y - 1] == '*' || map[enemy4x + 2][enemy4y] == '^' || map[enemy4x + 2][enemy4y + 1] == '^' || map[enemy4x + 2][enemy4y - 1] == '^') {
		killenemy1(map, enemy4x, enemy4y);
		enemy4status = 0;
		score += 2;
	}
	if (map[enemy4x][enemy4y + 2] == '*' || map[enemy4x + 1][enemy4y + 2] == '*' || map[enemy4x][enemy4y + 2] == '<' || map[enemy4x + 1][enemy4y + 2] == '<') {
		killenemy1(map, enemy4x, enemy4y);
		enemy4status = 0;
		score += 2;
	}
	if (map[enemy4x][enemy4y - 2] == '*' || map[enemy4x + 1][enemy4y - 2] == '*' || map[enemy4x][enemy4y - 2] == '>' || map[enemy4x + 1][enemy4y - 2] == '>') {
		killenemy1(map, enemy4x, enemy4y);
		enemy4status = 0;
		score += 2;
	}
}
void checkenemy5life(char map[][50]) {
	if (map[enemy5x - 1][enemy5y] == '*' || map[enemy5x - 1][enemy5y + 1] == '*' || map[enemy5x - 1][enemy5y - 1] == '*' || map[enemy5x - 1][enemy5y] == '^' || map[enemy5x - 1][enemy5y + 1] == '^' || map[enemy5x - 1][enemy5y - 1] == '^') {
		killenemy1(map, enemy5x, enemy5y);
		enemy5status = 0;
		score += 2;
	}
	if (map[enemy5x + 2][enemy5y] == '*' || map[enemy5x + 2][enemy5y + 1] == '*' || map[enemy5x + 2][enemy5y - 1] == '*' || map[enemy5x + 2][enemy5y] == '^' || map[enemy5x + 2][enemy5y + 1] == '^' || map[enemy5x + 2][enemy5y - 1] == '^') {
		killenemy1(map, enemy5x, enemy5y);
		enemy5status = 0;
		score += 2;
	}
	if (map[enemy5x][enemy5y + 2] == '*' || map[enemy5x + 1][enemy5y + 2] == '*' || map[enemy5x][enemy5y + 2] == '<' || map[enemy5x + 1][enemy5y + 2] == '<') {
		killenemy1(map, enemy5x, enemy5y);
		enemy5status = 0;
		score += 2;
	}
	if (map[enemy5x][enemy5y - 2] == '*' || map[enemy5x + 1][enemy5y - 2] == '*' || map[enemy5x][enemy5y - 2] == '>' || map[enemy5x + 1][enemy5y - 2] == '>') {
		killenemy1(map, enemy5x, enemy5y);
		enemy5status = 0;
		score += 2;
	}
}
void checkenemy6life(char map[][50]) {
	if (map[enemy6x - 1][enemy6y] == '*' || map[enemy6x - 1][enemy6y + 1] == '*' || map[enemy6x - 1][enemy6y - 1] == '*' || map[enemy6x - 1][enemy6y] == '^' || map[enemy6x - 1][enemy6y + 1] == '^' || map[enemy6x - 1][enemy6y - 1] == '^') {
		killenemy1(map, enemy6x, enemy6y);
		enemy6status = 0;
		score += 2;
	}
	if (map[enemy6x + 2][enemy6y] == '*' || map[enemy6x + 2][enemy6y + 1] == '*' || map[enemy6x + 2][enemy6y - 1] == '*' || map[enemy6x + 2][enemy6y] == '^' || map[enemy6x + 2][enemy6y + 1] == '^' || map[enemy6x + 2][enemy6y - 1] == '^') {
		killenemy1(map, enemy6x, enemy6y);
		enemy6status = 0;
		score += 2;
	}
	if (map[enemy6x][enemy6y + 2] == '*' || map[enemy6x + 1][enemy6y + 2] == '*' || map[enemy6x][enemy6y + 2] == '<' || map[enemy6x + 1][enemy6y + 2] == '<') {
		killenemy1(map, enemy6x, enemy6y);
		enemy6status = 0;
		score += 2;
	}
	if (map[enemy6x][enemy6y - 2] == '*' || map[enemy6x + 1][enemy6y - 2] == '*' || map[enemy6x][enemy6y - 2] == '>' || map[enemy6x + 1][enemy6y - 2] == '>') {
		killenemy1(map, enemy6x, enemy6y);
		enemy6status = 0;
		score += 2;
	}
}



void ethenlife(char map[][50]) {
	if ((map[ethenx - 3][etheny] == '|') || (map[ethenx - 2][etheny - 1] == '|') || (map[ethenx - 2][etheny + 1] == '|')) {
		life--;

	}
	if ((map[ethenx + 2][etheny] == '|') || (map[ethenx + 2][etheny - 1] == '|') || (map[ethenx + 2][etheny + 1] == '|')) {
		life--;
	}
	if ((map[ethenx][etheny - 3] == '-') || (map[ethenx + 1][etheny - 3] == '-') || (map[ethenx - 1][etheny - 2] == '-')) {
		life--;
	}
	if ((map[ethenx][etheny + 3] == '-') || (map[ethenx + 1][etheny + 3] == '-') || (map[ethenx - 1][etheny + 2] == '-')) {
		life--;
	}


}

void createethen(char map[][50], int ethenx, int etheny) {



	if (map[ethenx][etheny] == ' ' && (map[ethenx][etheny] != '-' || map[ethenx][etheny] != '|'))
	{

		map[ethenx][etheny] = '|';
		map[ethenx - 1][etheny] = 'O';
		map[ethenx][etheny - 1] = '/';
		map[ethenx][etheny + 1] = '\\';
		map[ethenx + 1][etheny + 1] = '\\';
		map[ethenx + 1][etheny - 1] = '/';
	}
}
void killethen(char map[][50])
{
	map[ethenx][etheny] = ' ';
	map[ethenx - 1][etheny] = ' ';
	map[ethenx][etheny - 1] = ' ';
	map[ethenx][etheny + 1] = ' ';
	map[ethenx + 1][etheny + 1] = ' ';
	map[ethenx + 1][etheny - 1] = ' ';
}
void movebullet(char map[][50]) {

	if (dir == 1) {

		if (map[bulletx][bullety - 1] != ' ' || map[bulletx][bullety - 1] == '-') {
			status = 1;
			dir = 0;
			map[bulletx][bullety] = ' ';
		}
		else {


			map[bulletx][bullety] = ' ';
			bullety--;
			map[bulletx][bullety] = '*';
			status = 0;
		}


	}
	if (dir == 2) {

		if (map[bulletx + 1][bullety] != ' ' || map[bulletx + 2][bullety] == '|' || map[bulletx + 1][bullety] == '|' || map[bulletx + 4][bullety] == '|') {
			status = 1;
			dir = 0;
			map[bulletx][bullety] = ' ';


		}
		else {


			map[bulletx][bullety] = ' ';
			bulletx++;
			map[bulletx][bullety] = '*';
			status = 0;

		}


	}
	if (dir == 3) {
		if (map[bulletx - 1][bullety] != ' ' || map[bulletx - 2][bullety] == '|' || map[bulletx - 1][bullety] == '|' || map[bulletx - 4][bullety] == '|') {
			status = 1;
			dir = 0;
			map[bulletx][bullety] = ' ';

		}

		else {

			map[bulletx][bullety] = ' ';
			bulletx--;
			map[bulletx][bullety] = '*';
			status = 0;

		}

	}
	if (dir == 4) {
		if (map[bulletx][bullety + 1] != ' ' || map[bulletx][bullety + 1] == '-') {
			status = 1;
			dir = 0;
			map[bulletx][bullety] = ' ';

		}
		else {

			map[bulletx][bullety] = ' ';
			bullety++;
			map[bulletx][bullety] = '*';
			status = 0;

		}



	}


}

void missiletarget(char map[][50]) {
	if (enemy1status == 1) {

		missile = 1;
		//missilestatus = 0;
	}
	else if (enemy2status == 1) {
		missile = 2;
		//missilestatus = 0;
	}
	else if (enemy3status == 1) {
		missile = 3;
		//missilestatus = 0;

	}
	else if (enemy4status == 1) {
		missile = 4;
		//missilestatus = 0;

	}
	else if (enemy5status == 1) {
		missile = 5;
		//missilestatus = 0;

	}
	else if (enemy6status == 1) {
		missile = 6;
		//missilestatus = 0;

	}
}

void erasebullethitenemy(char map[][50]) {
	if (enemy1status == 0 && flag1 == 0) {
		status = 1;
		dir = 0;
		map[bulletx][bullety] = ' ';
	}
	if (enemy2status == 0 && flag2 == 0) {
		status = 1;
		dir = 0;
		map[bulletx][bullety] = ' ';

	}
	if (enemy3status == 0 && flag3 == 0) {
		status = 1;
		dir = 0;
		map[bulletx][bullety] = ' ';
	}
	if (enemy4status == 0 && flag4 == 0) {
		status = 1;
		dir = 0;
		map[bulletx][bullety] = ' ';

	}
	if (enemy5status == 0 && flag5 == 0) {
		status = 1;
		dir = 0;
		map[bulletx][bullety] = ' ';
	}
	if (enemy6status == 0 && flag6 == 0) {
		status = 1;
		dir = 0;
		map[bulletx][bullety] = ' ';

	}

	if (enemy1status == 0) {
		flag1 = 1;
	}
	if (enemy2status == 0) {
		flag2 = 1;
	}
	if (enemy3status == 0) {
		flag3 = 1;
	}
	if (enemy4status == 0) {
		flag4 = 1;
	}
	if (enemy5status == 0) {
		flag5 = 1;
	}
	if (enemy6status == 0) {
		flag6 = 1;
	}
}
void enemymovinglimits(char map[][50])
{
	if (level == 1) {
		enemy1limity1 = 3;
		enemy1limity2 = 24;

		enemy2limity1 = 26;
		enemy2limity2 = 47;

	}
	if (level == 2) {
		enemy1limity1 = 3;
		enemy1limity2 = 18;

		enemy2limity1 = 20;
		enemy2limity2 = 33;

		enemy3limity1 = 35;
		enemy3limity2 = 47;
	}
	if (level == 3) {
		enemy1limity1 = 3;
		enemy1limity2 = 10;

		enemy2limity1 = 12;
		enemy2limity2 = 22;

		enemy3limity1 = 24;
		enemy3limity2 = 34;

		enemy4limity1 = 36;
		enemy4limity2 = 47;
	}
	if (level == 4)
	{
		enemy1limity1 = 3;
		enemy1limity2 = 18;

		enemy2limity1 = 20;
		enemy2limity2 = 33;

		enemy3limity1 = 35;
		enemy3limity2 = 47;

		enemy4limity1 = 3;
		enemy4limity2 = 18;


		enemy5limity1 = 20;
		enemy5limity2 = 33;


	}
	if (level == 5)
	{
		enemy1limity1 = 3;
		enemy1limity2 = 18;

		enemy2limity1 = 20;
		enemy2limity2 = 33;

		enemy3limity1 = 35;
		enemy3limity2 = 47;

		enemy4limity1 = 3;
		enemy4limity2 = 18;


		enemy5limity1 = 20;
		enemy5limity2 = 33;

		enemy6limity1 = 35;
		enemy6limity2 = 47;
	}

}
void createenemyranges(char map[][50])
{
	//to create enemy 4 coordinates are made
	if (level == 1)
	{
		enemy1x = rand() % (25 - 5 + 2) + 6;
		enemy1y = rand() % 15 + 2;

		enemy2x = rand() % (25 - 5 + 1) + 5;
		enemy2y = rand() % (26 - 16 + 1) + 16;
	}
	if (level == 2)
	{
		enemy1x = rand() % (25 - 5 + 2) + 6;
		enemy1y = rand() % 16 + 3;

		enemy2x = rand() % (25 - 5 + 1) + 5;
		enemy2y = rand() % 14 + 20;

		enemy3x = rand() % (25 - 5 + 2) + 6;
		enemy3y = rand() % 13 + 35;
	}
	if (level == 3)
	{
		enemy1x = rand() % (25 - 5 + 2) + 6;
		enemy1y = rand() % 8 + 3;

		enemy2x = rand() % (25 - 5 + 1) + 5;
		enemy2y = rand() % 11 + 12;

		enemy3x = rand() % (25 - 5 + 2) + 6;
		enemy3y = rand() % 11 + 24;

		enemy4x = rand() % (25 - 5 + 2) + 6;
		enemy4y = rand() % 12 + 36;
	}

	if (level == 4)
	{
		enemy1x = rand() % (25 - 5 + 2) + 6;
		enemy1y = rand() % 16 + 3;

		enemy2x = rand() % (25 - 5 + 1) + 5;
		enemy2y = rand() % 14 + 20;

		enemy3x = rand() % (25 - 5 + 2) + 6;
		enemy3y = rand() % 13 + 35;

		enemy4x = rand() % (25 - 5 + 2) + 6;
		enemy4y = rand() % 16 + 3;

		enemy5x = rand() % (25 - 5 + 2) + 6;
		enemy5y = rand() % 14 + 20;
	}

	if (level == 5)
	{
		enemy1x = rand() % (25 - 5 + 2) + 6;
		enemy1y = rand() % 16 + 3;

		enemy2x = rand() % (25 - 5 + 1) + 5;
		enemy2y = rand() % 14 + 20;

		enemy3x = rand() % (25 - 5 + 2) + 6;
		enemy3y = rand() % 13 + 35;

		enemy4x = rand() % (25 - 5 + 2) + 6;
		enemy4y = rand() % 16 + 3;

		enemy5x = rand() % (25 - 5 + 2) + 6;
		enemy5y = rand() % 14 + 20;

		enemy6x = rand() % (25 - 5 + 2) + 6;
		enemy6y = rand() % 13 + 35;
	}
}
void progresslevel(char map[][50])
{
	if ((ethenx - 1 == 0) && (etheny > 35 && etheny < 41))
	{
		level++;
	}
}
void mapredisplay(char map[][50])
{
	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 50; j++) {
			map[0][j] = '-';
			map[49][j] = '-';
			map[i][0] = '|';
			map[i][49] = '|';
		}
	}
	for (int i = 35; i < 41; i++) {
		map[0][i] = ' ';

	}
}
void moveethen(char map[][50], int x, int y, int x1, int y1, int x2, int y2, int x3, int y3)
{



	int ch;


	cout << "Press an arrow key:\n";



	ch = _getch();


	switch (ch) {

	case 72:  // Up arrow
		killethen(map);

		ethenx--;
		if (ethenx < 2 || map[ethenx - 1][etheny] != ' ' || map[ethenx][etheny - 1] != ' ' || map[ethenx][etheny + 1] != ' ')
		{
			ethenx++;
			life--;
		}
		createethen(map, ethenx, etheny);
		break;
	case 80:  // Down arrow
		killethen(map);

		ethenx++;
		if (ethenx > 47 || map[ethenx + 1][etheny + 1] != ' ' || map[ethenx + 1][etheny] != ' ' || map[ethenx + 1][etheny - 1] != ' ')
		{
			ethenx--;
			life--;
		}
		createethen(map, ethenx, etheny);
		break;
	case 77:  // Right arrow
		killethen(map);

		etheny++;
		if (etheny > 47 || map[ethenx][etheny + 1] != ' ' || map[ethenx + 1][etheny + 1] != ' ' || map[ethenx - 1][etheny + 1] != ' ')
		{
			etheny--;
			life--;
		}
		createethen(map, ethenx, etheny);
		break;
	case 75:  // Left arrow
		killethen(map);

		etheny--;
		if (etheny < 2 || map[ethenx][etheny - 1] != ' ' || map[ethenx + 1][etheny - 1] != ' ' || map[ethenx - 1][etheny - 1] != ' ')
		{
			etheny++;
			life--;
		}
		createethen(map, ethenx, etheny);
		break;


	case 97:
		if (status == 1) {
			bulletx = ethenx;
			bullety = etheny - 2;
			map[bulletx][bullety] = '*';
			dir = 1;
		}
		break;
	case 115:
		if (status == 1) {
			bulletx = ethenx + 1;
			bullety = etheny;
			map[bulletx][bullety] = '*';
			dir = 2;
		}



		break;
	case 119:
		if (status == 1) {
			bulletx = ethenx - 2;
			bullety = etheny;
			map[bulletx][bullety] = '*';
			dir = 3;
		}
		break;

	case 100:
		if (status == 1) {
			bulletx = ethenx;
			bullety = etheny + 2;
			map[bulletx][bullety] = '*';
			dir = 4;
		}
		break;

	case 32:
		if (timemissile == 0) {

			missiletarget(map);

			missilex = ethenx - 2;
			missiley = etheny;
			map[missilex][missiley] = '^';
			//movemissile(map);
			missilestatus = 1;
			survivaltime = 0;
			timemissile++;
		}

		break;
	}
	addobstacle(map, x, y, x1, y1, x2, y2, x3, y3);
	addobstacle(map, x, y, x1, y1, x2, y2, x3, y3);

}


int main()
{
	// Hide the cursor for a better game experience
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(consoleHandle, &cursorInfo);
	cursorInfo.bVisible = false; // Hide cursor
	SetConsoleCursorInfo(consoleHandle, &cursorInfo);
	srand(time(0));
	int i = 0;
	int newlife = 2;
	int count = 0;
	int levelcounter;
	int islost = 0;
	//static int x, y, x1, y1, x2, y2, x3, y3;





	int x = rand() % (38 - 25 + 1) + 25;  // x between 25 and 38
	int y = rand() % 8 + 2;               // y between 2 and 9

	int x1 = rand() % (38 - 25 + 1) + 25; // x1 between 25 and 38
	int y1 = rand() % 10 + 14;            // y1 between 14 and 23

	int x2 = rand() % (38 - 25 + 1) + 25; // x2 between 25 and 38
	int y2 = rand() % 11 + 26;             // y2 between 2 and 9

	int x3 = rand() % (38 - 25 + 1) + 25; // x3 between 25 and 38
	int y3 = rand() % 10 + 33;

	char map[50][50];
	ethenx = rand() % (45 - 35 + 1) + 35;
	etheny = rand() % (25 - 3 + 1) + 3;


	cout << "enter the level you wants to play from : " << endl;
	cin >> levelcounter;
	level = levelcounter;

	while (levelcounter <= 5)
	{
		createenemyranges(map);
		enemymovinglimits(map);
		solomenlifestatus = 1;
		enemy1status = 1;
		enemy2status = 1;
		enemy3status = 1;
		enemy4status = 1;
		enemy5status = 1;
		enemy6status = 1;
		flag1 = 0;
		flag2 = 0;
		flag3 = 0;
		flag4 = 0;
		flag5 = 0;
		flag6 = 0;
		missilestatus = 0;
		timemissile = 0;


		mapformation(map);
		addobstacle(map, x, y, x1, y1, x2, y2, x3, y3);
		createethen(map, ethenx, etheny);
		createenemy1(map, enemy1x, enemy1y, enemy2x, enemy2y);
		createenemy2(map, enemy2x, enemy2y, enemy2x, enemy2y);
		createenemy2(map, enemy3x, enemy3y, enemy3x, enemy3y);
		createenemy2(map, enemy4x, enemy4y, enemy4x, enemy4y);
		createenemy2(map, enemy5x, enemy5y, enemy5x, enemy5y);
		createenemy2(map, enemy6x, enemy6y, enemy6x, enemy6y);

		//moveenemy(map, enemy1x, enemy1y, enemy2x, enemy2y, x, y, x1, y1);

		//solomen(map, solox, soloy);
		//movesolomen(map, solox,  soloy,  count,  x,  y, x1, y1,  x2,  y2,  x3,  y3);
		mapdisplay(map);
		system("cls");
		setCursorPosition(0, 0);
		enemiesspeed(map);
		erasebullethitenemy(map);

		islost = 0;
		while (i <= 100000)
		{
			cout << endl;
			cout << "level" << level;
			checkenemy1life(map);
			checkenemy2life(map);
			checkenemy3life(map);
			checkenemy4life(map);
			checkenemy5life(map);
			checkenemy6life(map);


			erasebullethitenemy(map);
			erasebullethitenemy(map);


			setCursorPosition(0, 0);
			addobstacle(map, x, y, x1, y1, x2, y2, x3, y3);
			addobstaclesagain(map, x, y, x1, y1, x2, y2, x3, y3);

			if (_kbhit()) {
				moveethen(map, x, y, x1, y1, x2, y2, x3, y3);
			}
			movebullet(map);

			survivaltime++;
			if (survivaltime == 300) {
				score++;
				survivaltime = 0;
			}
			moveenemy(map, enemy1x, enemy1y, enemy2x, enemy2y, x, y, x1, y1);
			ismove++;
			//createethen(map, ethenx, etheny);


			moveenemy1bullet(map);
			moveenemy2bullet(map);
			moveenemy3bullet(map);
			moveenemy4bullet(map);
			moveenemy5bullet(map);
			moveenemy6bullet(map);



			//movemissile(map);
			movemissile(map);

			//solomen(map, solox, soloy);

			solomenlifecheck(map);



			movesolomen(map, solox, soloy, count, x, y, x1, y1, x2, y2, x3, y3);
			ethenlife(map);


			mapdisplay(map);
			createethen(map, ethenx, etheny);
			mapredisplay(map);

			if (solomenlifestatus == 1) {

				movesolobullet(map);
				movesolomen(map, solox, soloy, count, x, y, x1, y1, x2, y2, x3, y3);
			}
			else
			{
				spacesolo(map, solox, soloy);
				erasesolomenbullets(map);

			}


			erasebullethitenemy(map);


			cout << "life" << life << endl;
			if (newlife == life)
			{
				cout << "life decrease ---";
				newlife--;
			}
			if (life == 0)
			{
				islost = 1;
				break;
			}
			cout << endl << endl << endl << endl << "score is" << score;
			if ((ethenx - 2 == 0) && (etheny > 35 && etheny < 41))
			{
				life = 3;
				break;
			}
			i++;
		}
		if (islost == 1)
		{
			break;
		}
		else
		{
			level++;
			levelcounter++;
			system("cls");
			Sleep(200);
			cout << "you have reached level" << level << endl;
			cout << "get ready" << endl;
			//killethen(map);
			//killenemy1(map, enemy1x, enemy1y);

			//killenemy1(map, enemy2x, enemy2y);

			//killenemy1(map, enemy3x, enemy3y);

			//killenemy1(map, enemy4x, enemy4y);

			//killenemy1(map, enemy5x, enemy5y);

			//killenemy1(map, enemy6x, enemy6y);

			//moveenemy(map, enemy1x, enemy1y, enemy2x, enemy2y, x, y, x1, y1);

			//mapformation(map);
			//mapdisplay(map);



			ethenx = rand() % (45 - 35 + 1) + 35;
			etheny = rand() % (25 - 3 + 1) + 3;
		}
	}
	system("cls");
	cout << "you lose";
	system("pause");
	return 0;
}