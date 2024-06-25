#ifndef APP_GAME_H_
#define APP_GAME_H_

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_render.h>
#include <variant>

namespace gamestate {
struct Title final {};

struct Gameplay final {};

} // namespace gamestate
class Game final {
  using GameState =
      std::variant<std::monostate, gamestate::Title, gamestate::Gameplay>;

public:
  void process_event(SDL_Event const &event) noexcept;
  void update(float const dt) noexcept;
  void draw(SDL_Renderer const *renderer) const noexcept;

private:
  void update([[maybe_unused]] gamestate::Title& state, [[maybe_unused]] float const dt) noexcept;
  void update([[maybe_unused]] gamestate::Gameplay& state, [[maybe_unused]] float const dt) noexcept;

  void process_event([[maybe_unused]] gamestate::Title& state,
                     [[maybe_unused]] SDL_Event const &event) noexcept;
  void process_event([[maybe_unused]] gamestate::Gameplay& state,
                     [[maybe_unused]] SDL_Event const &event) noexcept;

  void handle_state_change([[maybe_unused]] gamestate::Title const& state, [[maybe_unused]] SDL_Event const& event) noexcept;
  void handle_state_change([[maybe_unused]] gamestate::Gameplay const& state, [[maybe_unused]] SDL_Event const& event) noexcept;

  void draw([[maybe_unused]] gamestate::Title const& state,
            [[maybe_unused]] SDL_Renderer const *renderer) const noexcept;
  void draw([[maybe_unused]] gamestate::Gameplay const& state,
            [[maybe_unused]] SDL_Renderer const *renderer) const noexcept;

  GameState next_state_{};
  GameState current_state_{gamestate::Title{}};
};
#endif
