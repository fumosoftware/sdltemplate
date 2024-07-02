#ifndef APP_GAMESCREENS_H_
#define APP_GAMESCREENS_H_

#include "screens/game.h"
#include "screens/gameover.h"
#include "screens/settings.h"
#include "screens/title.h"
#include <SDL3/SDL.h>
#include <entt/entt.hpp>
#include <variant>

/**
 * \class Screens
 * \brief Manages the current state of the application.
 *
 * A finite-state machine implementation to help
 * manage the state of the application itself.
 *
 * A "Screen" can be thought of as a seperate, distinct
 * state of the application that is not a substate of the application.
 *
 * For example, the "Title Screen" and "Level Select" screens are
 * completely different states of an application, but a "Menu Screen"
 * can be a sub-state of the main gameplay screen.
 */
class ArkoGame final {
  using Screen = std::variant<Title, Game, Settings, GameOver>;

public:
  explicit ArkoGame() noexcept;
  /**< Changes from the current screen to another screen */
  /**
   * Replaces the current screen with an instance of another screen.
   * Because of this, changing screens must only happen
   * from handling an event, and must not happen from inside the update loop.
   *
   */
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
  entt::registry world_{};
  Screen current_screen_;
};

#endif
