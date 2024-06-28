#ifndef APP_SCREEN_SETTINGS_H_
#define APP_SCREEN_SETTINGS_H_
#include <SDL3/SDL.h>

class Screens;
class Settings final {
public:
  void process_event(SDL_Event const &event, Screens &screen) noexcept;
  void update(float dt) noexcept;
  void draw(SDL_Renderer *renderer) const noexcept;

private:
};

#endif
