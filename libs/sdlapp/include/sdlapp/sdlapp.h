#ifndef SDLTEMPLATE_APP_APP_H_
#define SDLTEMPLATE_APP_APP_H_

#include <SDL3/SDL.h>
#include <memory>
#include <stdexcept>

namespace sdltemplate {
class SDLApp {
  using SDLWindow = std::unique_ptr<SDL_Window, void (*)(SDL_Window *)>;
  using SDLRenderer = std::unique_ptr<SDL_Renderer, void (*)(SDL_Renderer *)>;

public:
  SDLApp();
  ~SDLApp() noexcept;

  SDLApp(SDLApp const &) = delete;
  SDLApp(SDLApp &&) noexcept = delete;
  SDLApp &operator=(SDLApp const &) = delete;
  SDLApp &operator=(SDLApp &&) noexcept = delete;

  int run() noexcept;

private:
  void poll_events() noexcept;
  void draw() noexcept;

  SDL_Renderer *m_renderer{nullptr};
  SDL_Window *m_window{nullptr};
  bool m_is_running{true};
};

class SDLInitializeError : public std::runtime_error {
public:
  SDLInitializeError() : std::runtime_error("Could not initialize SDL") {}
};

class SDLWindowCreationError : public std::runtime_error {
public:
  SDLWindowCreationError() : std::runtime_error(SDL_GetError()) {}
};

class SDLRendererCreationError : public std::runtime_error {
public:
  SDLRendererCreationError() : std::runtime_error(SDL_GetError()) {}
};

} // namespace sdltemplate

#endif
