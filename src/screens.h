#ifndef APP_GAMESCREENS_H_
#define APP_GAMESCREENS_H_

#include "screens/game.h"
#include "screens/gameover.h"
#include "screens/settings.h"
#include "screens/title.h"
#include <SDL3/SDL.h>
#include <variant>

class Screens final {
using Screen =
    std::variant<Title, Game, Settings, GameOver>;
public:
  void change_screen(auto screen) noexcept
    requires std::is_same_v<decltype(screen), Title> ||
             std::is_same_v<decltype(screen), Game> ||
             std::is_same_v<decltype(screen), Settings> ||
             std::is_same_v<decltype(screen), GameOver>
  {
    current_screen_ = screen;
  }

  void process_event(SDL_Event const &event) noexcept;
  void update(float dt) noexcept;
  void draw(SDL_Renderer *renderer) const noexcept;

private:
  Screen current_screen_{};
};

#endif
