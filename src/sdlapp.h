#ifndef APP_SDLAPP_H_
#define APP_SDLAPP_H_

#include <memory>
#include <optional>
#include <SDL3/SDL.h>

class SDLApp {
public:
  static int exec() noexcept;
private:
  static std::optional<SDLApp> create() noexcept;

  explicit SDLApp(SDL_Window* window, SDL_Renderer* renderer) noexcept;
  int run() noexcept;
  void process_events() noexcept;
  void draw() noexcept;

  std::unique_ptr<SDL_Window, void(*)(SDL_Window*)> window_{nullptr, SDL_DestroyWindow};
  std::unique_ptr<SDL_Renderer, void(*)(SDL_Renderer*)> renderer{nullptr, SDL_DestroyRenderer};
  bool is_running{true};
};

#endif
