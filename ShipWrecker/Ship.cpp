#include "Ship.h"
#include <cmath>
#include <cstdlib>
#include <time.h>

enum Classes { TANK, FIGHTER, SHOOTER, WORKER };

inline double distance(int x1, int x2, int y1, int y2)
{
	return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
}

Ship::Ship()
{
	
}

void Ship::set(int sType, int x_cord, int y_cord)
{
	_x = x_cord;
	_y = y_cord;

	type = sType;
	switch (type)
	{
	case TANK:
		MAX_HEALTH = 400;
		_health = 400;
		break;

	case FIGHTER:
		MAX_HEALTH = 300;
		_health = 300;
		break;

	case WORKER:
		MAX_HEALTH = 200;
		_health = 200;
		break;

	case SHOOTER:
		MAX_HEALTH = 100;
		_health = 100;
		break;
	}

	alive = true;
}

void Ship::move_to(int new_x, int new_y)
{
	double dist = distance(_x, new_x, _y, new_y);
	_x = new_x;
	_y = new_y;

	//Numbers
	switch (type)
	{
	case TANK:
		_health += dist / 40;
		if (_health > 400)
			_health = 400;
		break;

	case FIGHTER:
		_health += dist / 40;
		if (_health > 300)
			_health = 300;
		break;

	case WORKER:
		_health += dist * 4 / 40;
		if (_health > 200)
			_health = 200;
		break;

	case SHOOTER:
		_health += dist / 40;
		if (_health > 100)
			_health = 100;
		break;
	}

	//Play move animation
	//Health bar update
}

void Ship::got_hit(double damage)
{
	_health -= damage;
	//Play shoot animation 
	//Health bar update (show as dead if health<0
	if (_health <= 1)
	{
		_health = 0;
		alive = false;
		//Play death animation
	}
}

void Ship::shoot(Ship &enemy1, Ship &enemy2)
{
	if (enemy1.alive && enemy2.alive)
	{
		double d1 = distance(_x, enemy1._x, _y, enemy1._y);
		double d2 = distance(_x, enemy2._x, _y, enemy2._y);

		if (d1 < d2)
		{
			double damage = hits(enemy1);
			if (damage > 0)
				enemy1.got_hit(damage);
		}
		else
		{
			double damage = hits(enemy2);
			if (damage > 0)
				enemy2.got_hit(damage);
		}
	}

	else if (enemy1.alive)
	{
		double damage = hits(enemy1);
		if (damage > 0)
			enemy1.got_hit(damage);
	}

	else
	{
		double damage = hits(enemy2);
		if (damage > 0)
			enemy2.got_hit(damage);
	}
}

double Ship::hits(Ship &enemy)
{
	//Uses probability to check if a shot hits. If it hits then returns the damage. Otherwise returns -1;

	double dist = distance(_x, enemy._x, _y, enemy._y);

	double prob, damage;

	//Numbers
	if (dist < 50)
		return 400;	//To make sure all types die
	else
	{
		switch (type)
		{
		case TANK:
			if (dist < 200)
			{
				prob = 0.5;
				damage = 50;
			}
			else if (dist < 300)
			{
				prob = 0.4;
				damage = 45;
			}
			else if (dist < 400)
			{
				prob = 0.3;
				damage = 40;
			}
			else if (dist < 500)
			{
				prob = 0.25;
				damage = 35;
			}
			else if (dist < 600)
			{
				prob = 0.2;
				damage = 30;
			}
			else if (dist < 700)
			{
				prob = 0.15;
				damage = 25;
			}
			else
			{
				prob = 0.1;
				damage = 20;
			}
			break;

		case FIGHTER:
			if (dist < 200)
			{
				prob = 0.9;
				damage = 200;
			}
			else if (dist < 300)
			{
				prob = 0.5;
				damage = 100;
			}
			else if (dist < 400)
			{
				prob = 0.3;
				damage = 50;
			}
			else if (dist < 500)
			{
				prob = 0.25;
				damage = 40;
			}
			else if (dist < 600)
			{
				prob = 0.2;
				damage = 30;
			}
			else if (dist < 700)
			{
				prob = 0.15;
				damage = 25;
			}
			else
			{
				prob = 0.1;
				damage = 20;
			}
			break;

		case SHOOTER:
			if (dist < 200)
			{
				prob = 0.9;
				damage = 200;
			}
			else if (dist < 300)
			{
				prob = 0.7;
				damage = 150;
			}
			else if (dist < 400)
			{
				prob = 0.6;
				damage = 100;
			}
			else if (dist < 500)
			{
				prob = 0.4;
				damage = 75;
			}
			else if (dist < 600)
			{
				prob = 0.3;
				damage = 50;
			}
			else if (dist < 700)
			{
				prob = 0.25;
				damage = 40;
			}
			else
			{
				prob = 0.2;
				damage = 40;
			}
			break;

		case WORKER:
			if (dist < 200)
			{
				prob = 0.5;
				damage = 50;
			}
			else if (dist < 300)
			{
				prob = 0.4;
				damage = 45;
			}
			else if (dist < 400)
			{
				prob = 0.3;
				damage = 40;
			}
			else if (dist < 500)
			{
				prob = 0.25;
				damage = 35;
			}
			else if (dist < 600)
			{
				prob = 0.2;
				damage = 30;
			}
			else if (dist < 700)
			{
				prob = 0.15;
				damage = 25;
			}
			else
			{
				prob = 0.1;
				damage = 20;
			}
			break;
		}
	}

	double rn = (double)rand() / RAND_MAX;
	if (rn < prob)
		return damage;
	else
		return -1;
}

Ship::~Ship()
{
	//dtor
}
