#ifndef SDLTEMPLATE_APP_APP_H_
#define SDLTEMPLATE_APP_APP_H_

#include <SDL3/SDL.h>
#include <stdexcept>
#include <variant>

namespace sdltemplate {
class SDLApp {
  class TitleState {
  public:
    void process_event(SDL_Event const &event, SDLApp &app) noexcept;
    void update() noexcept;
    void draw(SDL_Renderer *renderer) noexcept;
  };

  class GameState {
  public:
    void process_event(SDL_Event const &event, SDLApp &app) noexcept;
    void update() noexcept;
    void draw(SDL_Renderer *renderer) noexcept;
  };

  class GameOverState {
  public:
    void process_event(SDL_Event const &event, SDLApp &app) noexcept;
    void update() noexcept;
    void draw(SDL_Renderer *renderer) noexcept;
  };

  using State = std::variant<TitleState, GameState, GameOverState>;

public:
  SDLApp();
  ~SDLApp() noexcept;

  SDLApp(SDLApp const &) = delete;
  SDLApp(SDLApp &&) noexcept = delete;
  SDLApp &operator=(SDLApp const &) = delete;
  SDLApp &operator=(SDLApp &&) noexcept = delete;

  void run() noexcept;

private:
  void poll_events() noexcept;
  void update_state() noexcept;
  void draw() noexcept;

  State m_current_state{TitleState{}};
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
