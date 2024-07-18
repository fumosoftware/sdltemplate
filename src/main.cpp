 #include "sdlapp.h"

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) noexcept {
  try {
     SDLApp app{};
     return app.run();
//    return SDLApp{}.run();
  } catch (SDLException const &error) {
//    spdlog::error(error.what());
  }

  return 1;
}
