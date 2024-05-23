#include <fmt/color.h>


int main([[maybe_unused]]int argc, [[maybe_unused]]char** argv) {
  fmt::print(fg(fmt::color::green), "Hello, world!\n");

  return 0;
}
