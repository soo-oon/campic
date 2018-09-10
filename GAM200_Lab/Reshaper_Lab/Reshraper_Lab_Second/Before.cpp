#include <iostream>

#define A 1
#define B 2

class vector
{
public:
	vector() : x(0), y(0)
	{}

	vector(int x_, int y_) : x(x_), y(y_)
	{}

	void Add(int x_, int y_)
	{
		x += x_;
		y += y_;
	}

	void print()
	{
		std::cout << "x pos: " << x << ", " << "y pos: "<< y << std::endl;
	}

private:
	int x;
	int y;
};

int main(void)
{
	vector v1;
	vector v2(5, 5);

	v1.Add(A, A);
	v2.Add(A, B);

	v1.print();
	v2.print();

	return 0;
}