#include <fmt/color.h>
#include <string_view>

enum struct Level { none, warning, error };

void print(Level level, std::string_view error_message);
