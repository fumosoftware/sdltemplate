#ifndef APP_SDLAPP_H_
#define APP_SDLAPP_H_

#include <SDL3/SDL.h>
#include <filesystem>
#include <memory>
#include <variant>

class SDLAppError;
class SDLApp final {
  using SDLWindowPtr = std::unique_ptr<SDL_Window, void (*)(SDL_Window *)>;
  using SDLRendererPtr =
      std::unique_ptr<SDL_Renderer, void (*)(SDL_Renderer *)>;

  static constexpr auto DEFAULT_WIDTH{380u};
  static constexpr auto DEFAULT_HEIGHT{120u};

public:
  enum struct Error {
    INITIALIZATION_FAILED,
    WINDOW_CREATION,
    RENDERER_CREATION
  };

  static std::variant<SDLApp, Error> create() noexcept;
  static std::variant<SDLApp, Error>
  create_from(std::filesystem::path const path) noexcept;

  int run() noexcept;

private:
  SDLApp() noexcept;
  SDLApp(unsigned int const width, unsigned int const height) noexcept;

  void process_events() noexcept;
  void draw() noexcept;

  SDLWindowPtr window_{nullptr, SDL_DestroyWindow};
  SDLRendererPtr renderer_{nullptr, SDL_DestroyRenderer};
  bool is_running_{true};
};

#endif
