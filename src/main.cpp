#include "sdlapp.h"
#include <spdlog/spdlog.h>

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) noexcept {


  try {
    return SDLApp{}.run();
  }
  catch(SDLException const& error) {
    spdlog::error(error.what());
  }

  return 1;
}

