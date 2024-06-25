#include "config.h"
#include <filesystem>
#include <spdlog/spdlog.h>
#include <toml++/toml.h>

using namespace std::literals;
namespace {
auto const CONFIG_PATH{"./data/config.toml"sv};
auto const DEFAULT_CONFIG_CONTENTS{
    R"(
[window]
width  = 1000
height = 680
)"sv};
} // namespace

toml::table load_or_create_config() {
  if (std::filesystem::exists(CONFIG_PATH) == false) {
    return toml::parse(DEFAULT_CONFIG_CONTENTS);
  }

  try {
    return toml::parse_file(CONFIG_PATH);
  } catch (toml::parse_error const &error) {
    spdlog::error("Could not parse the config at ./data/config.toml\n%s",
                  error.what());
    return toml::parse(DEFAULT_CONFIG_CONTENTS);
  }
}

toml::table default_config() noexcept {
  return toml::parse(DEFAULT_CONFIG_CONTENTS);
}
