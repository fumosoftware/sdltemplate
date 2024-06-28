#ifndef APP_GAMESCREENS_H_
#define APP_GAMESCREENS_H_

#include <SDL3/SDL.h>
#include <variant>

class TitleScreen;
class GameScreen;
class SettingsScreen;
class GameOverScreen;
class GameScreens;

class TitleScreen final {
public:
  void process_event(SDL_Event const &event, GameScreens &screen) noexcept;
  void update(float dt) noexcept;
  void draw(SDL_Renderer *renderer) const noexcept;

private:
};

class GameScreen final {
public:
  void process_event(SDL_Event const &event, GameScreens &screen) noexcept;
  void update(float dt) noexcept;
  void draw(SDL_Renderer *renderer) const noexcept;

private:
private:
};

class SettingsScreen final {
public:
  void process_event(SDL_Event const &event, GameScreens &screen) noexcept;
  void update(float dt) noexcept;
  void draw(SDL_Renderer *renderer) const noexcept;

private:
};

class GameOverScreen final {
public:
  void process_event(SDL_Event const &event, GameScreens &screen) noexcept;
  void update(float dt) noexcept;
  void draw(SDL_Renderer *renderer) const noexcept;

private:
};

using Screen =
    std::variant<TitleScreen, GameScreen, SettingsScreen, GameOverScreen>;
class GameScreens final {
public:
  void change_screen(auto screen) noexcept
    requires std::is_same_v<decltype(screen), TitleScreen> ||
             std::is_same_v<decltype(screen), GameScreen> ||
             std::is_same_v<decltype(screen), SettingsScreen> ||
             std::is_same_v<decltype(screen), GameOverScreen>
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
