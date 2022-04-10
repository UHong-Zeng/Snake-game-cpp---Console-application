#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <vector>
#include <queue>
#include <Windows.h>
#include "snake.h"
using namespace std;
void cn() {
	int i = 10;
	while (i--)
		cout << "\n";
}
#define ct cout<<"\t\t"
#define right 'r'
#define left 'l'
#define up 'u'
#define down 'd'

class itf {
private:
	string start[3] = { "1. Play the game","2. Settings","e. Exit" };
	string settings[3] = { "1. Visual settings", "2. Snake's settigs", "e.Exit" };
public:
	void printstart();
	void printsettings();
};

int main() {
	srand(time(NULL));
	itf inter;
	snake snake;
	char ch;
	while (1) {
		inter.printstart();
		ch = _getch();
		cout << ch;
		//Sleep(1000);
		if (ch == 'e')
			return 0;
		if (ch > '0' && ch <= '2') {
			if (ch == '1') {
				snake.init();
				system("cls");
				snake.screan();
			}
			if (ch == '2') {
			
			}
		}
	}
}

void snake::screan() {
	while (1) {
		printval();
		if (eaten()) {
			foodcount++;
			if (!(foodcount % eat_to_long))
				length++;
			food();
		}
		//autogetkey();
		while (_kbhit())
			getkey();
		move();
		body_to_xy();
		printgame();
		if (die()) {
			system("cls");
			cn();
			ct << "\t\tYou lose the game!!";
			Sleep(3000);
			break;
		}
		if (postion == right || postion == left)
			Sleep(speed / 2 + 100);
		else
			Sleep(speed);
		system("cls");
	}
}
void snake::init() {
	for (int i = 1; i < 21; i++) {
		for (int j = 1; j < 21; j++) {
			xy[i][j] = 0;
		}
	}
	length = 3;
	food();
	for (int i = 0; i < maxlen; i++) {
		snake_xy[i].x = -1;
		snake_xy[i].y = -1;
	}
	for (int i = 0; i < 3; i++) {
		snake_xy[i].x = 3 - i;
		snake_xy[i].y = 1;
	}

	//print +++++++++...
	for (int i = 0; i < 22; i++) {
		xy[0][i] = 3;
		xy[21][i] = 3;
		xy[i][0] = 3;
		xy[i][21] = 3;
	}
	postion = right;
}
bool snake::die() {
	for (int i = 0; i < 22; i++) {
		if (xy[0][i] == 1 || xy[i][0] == 1 || xy[i][21] == 1 || xy[21][i] == 1)
			return true;
	}
	return false;
}
void snake::move() {
	queue<point> que;
	for (int i = 0; i < length; i++) {
		que.push(snake_xy[i]);
	}
	switch (postion)
	{
		case up: {
			snake_xy[0].y -= 1;
		}break;
		case down: {
			snake_xy[0].y += 1;
		}break;
		case left: {
			snake_xy[0].x -= 1;
		}break;
		case right: {
			snake_xy[0].x += 1;
		}break;
	default:
		break;
	}

	xy[snake_xy[length - 1].y][snake_xy[length - 1].x] = 0;
	for (int i = 1; i < length; i++) {
		snake_xy[i] = que.front();
		que.pop();
	}
	
}
void snake::getkey() {
	int key1, key2;
	key1 = _getch();
	key2 = _getch();
	if (key1 == 224)
		switch (key2)
		{
			case 72:
			case 'w':
			case 'W':
				if (postion != down)
					postion = up;
				break;
			case 75:
			case 'a':
			case 'A':
				if (postion != right)
					postion = left;
				break;
			case 77:
			case 'd':
			case 'D':
				if (postion != left)
					postion = right;
				break;
			case 80:
			case 's':
			case 'S':
				if (postion != up)
					postion = down;
				break;
		}
}
void snake::autogetkey() {
	int turn;//up 1,down 2,left 3,right 4
	turn = 1;
	switch (turn)
	{
		case 1: 
			postion = up;
			break;
		case 2:
			postion = down;
			break;
		case 3:
			postion = left;
			break;
		case 4:
			postion = right;
			break;
	}
}
void snake::printval() {//one value
	cout << "Health: " << health << '\n';
	cout << "Food: " << foodcount << '\n';
}
void snake::printgame() {
	for (int i = 0; i < 22; i++)/*print screan*/ {
		for (int j = 0; j < 22; j++) {
			if (!xy[i][j])
				cout << " ";
			else if (xy[i][j] == 3) {
				cout << "+";
			}
			else if (xy[i][j] == 1) {
				cout << "*";
			}
			else if (xy[i][j] == 2) {
				cout << "@";
			}
			else
				continue;
		}
		cout << "\n";
	}

}
void snake::food() {
	do {
		foodx = rand() % 20 + 1;
		foody = rand() % 20 + 1;
	} while (xy[foodx][foody]);
	xy[foodx][foody] = 2;
}
bool snake::eaten() {
	if (xy[foodx][foody] == 1)
		return true;
	else
		return false;
}
void snake::body_to_xy() {
	for (int i = 0; i < length; i++) {
		//if (snake_xy[i].x == -1 || snake_xy[i].y == -1)
			//continue;
		xy[snake_xy[i].y][snake_xy[i].x] = 1;
	}
}
void itf::printstart() {
	system("cls");
	cn();
	for (int i = 0; i < 3; i++) {
		ct;
		cout << start[i] << "\n";
	}
	cn();
}