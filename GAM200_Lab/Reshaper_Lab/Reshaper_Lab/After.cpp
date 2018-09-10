// file After.cpp
// author Team Name: Team_Boleh
// par Digipen login: 
// par GAM200 Engine
// date 9/10/2018
// 
// brief: Test for resharper
// 
// All content © 2018, DigiPen (USA) Corporation, all rights reserved. 

#include <iostream>

enum PointsNumber
{
	a = 0,
	b = 1,
	c = 2,
	d = 3,
	e = 4,
	f = 5,
	g = 6,
	h = 7
};

class Point
{
public:
	Point() : x_(a), y_(a)
	{
	}

	Point(int x, int y) : x_(x), y_(y)
	{
	}

	void add(int x, int y)
	{
		x_ += x;
		y_ += y;
	}

	void print()
	{
		std::cout << "X :" << x_ << ", " << "Y :" << y_ << std::endl;
	}

private:
	int x_;
	int y_;
};

int main(void)
{
	Point a;
	Point b(c, c);

	a.add(f, f);
	b.add(d, c);

	a.print();
	b.print();

	return 0;
}
