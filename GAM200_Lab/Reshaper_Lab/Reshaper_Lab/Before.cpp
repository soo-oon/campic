#include <iostream>

enum Points_Numbers
{
	A=0,
	B=1, 
	C=2, 
	D=3,
	E=4,
	F=5,
	G=6,
	H=7
};

class point
{
public:
	point() : x(A), y(A)
	{
	}

	point(int x_, int y_) : x(x_), y(y_)
	{
	}

	void add(int x_, int y_)
	{
		x += x_;
		y += y_;
	}

	void print()
	{
		std::cout << "X :" << x << ", " << "Y :" << y << std::endl;
	}

private:
	int x;
	int y;
};

int main(void)
{
	point A;
	point B(C, C);

	A.add(F, F);
	B.add(D, C);

	A.print();
	B.print();

	return 0;
}
