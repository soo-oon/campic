#include <iostream>

class vector {
private:
  int x;
  int y;

public:
  vector() : x(0), y(0) {}
  vector(int x_, int y_) : x(x_), y(y_) {}

  void print_vector() {
    std::cout << "x pos: " << x << ", "
              << "y pos: " << y << std::endl;
  }
};

int main(void) {
  vector a(5, 3);
  vector b;

  a.print_vector();
  b.print_vector();

  return 0;
}