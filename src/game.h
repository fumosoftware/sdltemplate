#ifndef APP_GAME_H_
#define APP_GAME_H_

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_render.h>
#include <optional>
#include <variant>

class Game final {
  struct TitleScreen final {};
  struct GameScreen final {};

  using GameState = std::variant<TitleScreen, GameScreen>;

public:
  void process_event(SDL_Event const &event) noexcept;
  void update() noexcept;
  void draw(SDL_Renderer *renderer) const noexcept;

private:
  std::optional<GameState> update([[maybe_unused]] TitleScreen &state,
              [[maybe_unused]] float const dt) noexcept;
  std::optional<GameState> update([[maybe_unused]] GameScreen &state,
              [[maybe_unused]] float const dt) noexcept;

  std::optional<GameState> process_event([[maybe_unused]] TitleScreen &state,
                     [[maybe_unused]] SDL_Event const &event) noexcept;
  std::optional<GameState> process_event([[maybe_unused]] GameScreen &state,
                     [[maybe_unused]] SDL_Event const &event) noexcept;

  void draw([[maybe_unused]] TitleScreen const &state,
            [[maybe_unused]] SDL_Renderer *renderer) const noexcept;
  void draw([[maybe_unused]] GameScreen const &state,
            [[maybe_unused]] SDL_Renderer *renderer) const noexcept;

  GameState next_state_{};
  GameState current_state_{TitleScreen{}};
};
#endif
