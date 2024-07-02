#ifndef APP_SCREEN_SETTINGS_H_
#define APP_SCREEN_SETTINGS_H_
#include <SDL3/SDL.h>
#include <entt/entt.hpp>

class ArkoGame;
class Settings final {
public:
  explicit Settings(entt::registry* world) noexcept;
  void process_event(SDL_Event const &event, ArkoGame &screen) noexcept;
  void update(float dt) noexcept;
  void draw(SDL_Renderer *renderer) const noexcept;

private:
  entt::registry* world_{};
};

#endif
