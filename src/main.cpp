#include <fmt/color.h>


struct A {
  int x;
  int y;
  int z;
};

int main(int argc, char** argv) {
  fmt::print(fg(fmt::color::green), "Hello, world!\n");

  A a{.x = 1, .z = 2};
  return 0;
}
