#ifndef SDLTEMPLATE_APP_APP_H_
#define SDLTEMPLATE_APP_APP_H_

#include <SDL3/SDL.h>
#include <stdexcept>
#include <variant>

#include <iostream>

namespace sdltemplate {
class SDLApp {

  class TitleState {
  public:
    void process_event(SDL_Event const &event, SDLApp &app) noexcept {
      switch (event.type) {
      case SDL_EVENT_KEY_DOWN: {
        if (event.key.keysym.scancode == SDL_SCANCODE_G)
          app.m_current_state = GameState{};
        else if (event.key.keysym.scancode == SDL_SCANCODE_Q)
          app.m_is_running = false;
      }
      default:
        break;
      }
    };
    void update() noexcept {
      std::cout << "Title State\n";
    };

  private:
  };
  class GameState {
  public:
    void process_event(SDL_Event const &event, SDLApp &app) noexcept {
      switch (event.type) {
      case SDL_EVENT_KEY_DOWN: {
        if (event.key.keysym.scancode == SDL_SCANCODE_O)
          app.m_current_state = GameOverState{};
        else if (event.key.keysym.scancode == SDL_SCANCODE_T)
              app.m_current_state = TitleState{};
        else if (event.key.keysym.scancode == SDL_SCANCODE_Q)
          app.m_is_running = false;
      }
      default:
        break;
      }
    };
    void update() noexcept {
      std::cout << "Game State \n";
    };

  private:
  };
  class GameOverState {
  public:
    void process_event(SDL_Event const &event, SDLApp &app) noexcept {
      switch (event.type) {
      case SDL_EVENT_KEY_DOWN: {
        if (event.key.keysym.scancode == SDL_SCANCODE_T)
          app.m_current_state = TitleState{};
        else if (event.key.keysym.scancode == SDL_SCANCODE_Q)
          app.m_is_running = false;
      }
      default:
        break;
      }
    };
    void update() noexcept {
      std::cout << "Game Over State \n";
    };

  private:
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
