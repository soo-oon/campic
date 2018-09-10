// file After.cpp
// author Team Name: Team_Boleh
// par Digipen login: 
// par GAM200 Engine
// date 9/10/2018
// 
// brief: Test for resharper second version
// 
// All content © 2018, DigiPen (USA) Corporation, all rights reserved. 

#include <iostream>

#define a 1
#define b 2

class VECTOR
{
public:
	VECTOR() : X_(0), Y_(0)
	{
	}

	VECTOR(int x_, int y_) : X_(x_), Y_(y_)
	{
	}

	void Add(int x_, int y_)
	{
		X_ += x_;
		Y_ += y_;
	}

	void print()
	{
		std::cout << "x pos: " << X_ << ", " << "y pos: " << Y_ << std::endl;
	}

private:
	int X_;
	int Y_;
};

int main(void)
{
	VECTOR v1;
	VECTOR v2(5, 5);

	v1.Add(a, a);
	v2.Add(a, b);

	v1.print();
	v2.print();

	return 0;
}
