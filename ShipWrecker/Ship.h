#ifndef SHIP_H
#define SHIP_H


class Ship
{
public:
	Ship();
	void set(int TYPE, int x_cord, int y_cord);

	void move_to(int new_x, int new_y);
	void got_hit(double damage);
	void shoot(Ship &enemy1, Ship &enemy2);
	double hits(Ship &enemy);

	virtual ~Ship();
	bool alive;
	int type;

	double _health;
	double MAX_HEALTH;
	int _x, _y;
};

#endif // SHIP_H