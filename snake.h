struct point {
	int x;
	int y;
};
#define maxlen 20
class snake {//0 = air, 1 = body, 2 = food, 3 = + ->(edge)
private: 
	int speed = 500;
	int health = 3;
	int length = 3;
	int xy[22][22] = { 0 };
	char postion;
	int foodcount = 0;
	int eat_to_long = 2;
	int foodx;
	int foody;
	point snake_xy[maxlen];
public:
	bool die();
	void screan();
	void printval();
	void printgame();
	void food();
	bool eaten();//have eaten = 1 else = 0
	void move();
	void autogetkey();
	void getkey();
	void body_to_xy();
	void init();
	void settings();
};