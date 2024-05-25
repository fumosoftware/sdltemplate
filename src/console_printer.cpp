#include "console_printer.h"
#include <functional>

void print(Level level, std::string_view error_message) {
  auto const fg_color = std::invoke([level]() {
    switch (level) {
    case Level::none:
      return fmt::color::green;
    case Level::warning:
      return fmt::color::gold;
    case Level::error:
      return fmt::color::red;

      return fmt::color::green;
    }
  });
  std::string _message(error_message);
  fmt::print(fg(fg_color) | fmt::emphasis::bold, "{}", _message.c_str());
}
