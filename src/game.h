#ifndef APP_GAME_H_
#define APP_GAME_H_

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_render.h>
#include <variant>

class Game final {
  struct Title final {};
  struct Gameplay final {};

  using GameState = std::variant<std::monostate, Title, Gameplay>;

public:
  void process_event(SDL_Event const &event) noexcept;
  void update() noexcept;
  void draw(SDL_Renderer *renderer) const noexcept;

private:
  void update([[maybe_unused]] Title &state,
              [[maybe_unused]] float const dt) noexcept;
  void update([[maybe_unused]] Gameplay &state,
              [[maybe_unused]] float const dt) noexcept;

  void process_event([[maybe_unused]] Title &state,
                     [[maybe_unused]] SDL_Event const &event) noexcept;
  void process_event([[maybe_unused]] Gameplay &state,
                     [[maybe_unused]] SDL_Event const &event) noexcept;

  void draw([[maybe_unused]] Title const &state,
            [[maybe_unused]] SDL_Renderer *renderer) const noexcept;
  void draw([[maybe_unused]] Gameplay const &state,
            [[maybe_unused]] SDL_Renderer *renderer) const noexcept;

  GameState next_state_{};
  GameState current_state_{Title{}};
};
#endif
