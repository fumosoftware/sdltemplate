#include <memory>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>

#include "app_main.h"

void setup_logging();
int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
  setup_logging();
  app_main();
  return 0;
}

void setup_logging() {
  auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(
      "logs/debug.log", true);

  spdlog::default_logger()->sinks().push_back(file_sink);
}
