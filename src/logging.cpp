#include "logging.h"
#include <spdlog/spdlog.h>

void logging::log(std::string_view msg) {
  spdlog::info(msg);
}

