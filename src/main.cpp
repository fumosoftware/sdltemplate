#include <iostream>
#include <type_traits>
#include <variant>

#include "sdlapp.h"

int app_main(std::filesystem::path const path) noexcept;
int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
  return app_main("./data/config.toml");
}

int app_main(std::filesystem::path const path) noexcept {
  SDL_Init(SDLApp::SDL_SUBSYSTEMS);
  auto const returnVal = std::visit(
      [](auto &&val) {
        using T = std::decay_t<decltype(val)>;
        if constexpr (std::is_same_v<T, SDLApp> == true) {
          return val.run();
        } else {
          switch (val) {
          case SDLApp::Error::INITIALIZATION_FAILED:
            std::cout << "Failed to initialize SDL.\n";
            return 1;
          case SDLApp::Error::WINDOW_CREATION:
            std::cout << "Failed to create a window.\n";
            return 2;
          case SDLApp::Error::RENDERER_CREATION:
            std::cout << "Failed to create a renderer.\n";
            return 3;
          }
        }
      },
      SDLApp::create_from(path));

  SDL_Quit();
  return returnVal;
}
