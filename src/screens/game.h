#ifndef APP_SCREENS_GAME_H_
#define APP_SCREENS_GAME_H_
#include <SDL3/SDL.h>
#include <entt/entt.hpp>

class ArkoGame;

class Game final {
public:
  explicit Game(entt::registry* world) noexcept;
  void process_event(SDL_Event const &event, ArkoGame &screen) noexcept;
  void update(float dt) noexcept;
  void draw(SDL_Renderer *renderer) const noexcept;

private:
  entt::registry* world_{};
};

#endif
