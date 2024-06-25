#ifndef APP_GAME_H_
#define APP_GAME_H_

#include <variant>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_render.h>

namespace gamestate {
struct Title final {};

struct Gameplay final {};

}
class Game final {
  using GameState = std::variant<std::monostate, gamestate::Title, gamestate::Gameplay>;
public:
  void process_event(SDL_Event const& event) noexcept;
  void update(float dt) noexcept;
  void draw(SDL_Renderer const* renderer) noexcept;
private:
  GameState current_state_{};
};
#endif

