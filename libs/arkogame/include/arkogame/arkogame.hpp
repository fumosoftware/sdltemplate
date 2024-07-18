#ifndef SDLTEMPLATE_LIB_ARKOGAME_ARKOGAME_H_
#define SDLTEMPLATE_LIB_ARKOGAME_ARKOGAME_H_

#include <iostream>
#include <variant>

#include <events/event.hpp>

namespace sdltemplate::arkogame {
class ArkoGame {

  class TitleScreen {
  public:
    inline void process_event(sdltemplate::Event &&event,
                              ArkoGame *game) noexcept {
      std::visit(
          [&](auto &&event) {
            using T = std::decay_t<decltype(event)>;
            if constexpr (std::is_same_v<T,
                                         sdltemplate::events::KeyPressEvent>) {
              game->current_screen_ = SettingsScreen{};
            }
          },
          event);
    };
    inline void update() noexcept { std::cout << "Title Screen\n"; };
    inline void draw() const noexcept {};
  };

  class SettingsScreen {
  public:
    inline void process_event(sdltemplate::Event &&event,
                              ArkoGame *game) noexcept {
      using T = std::decay_t<decltype(event)>;
      if constexpr (std::is_same_v<T, sdltemplate::events::KeyPressEvent>) {
        game->current_screen_ = GameScreen{};
      }
    };
    inline void update() noexcept { std::cout << "Settings Screen\n"; };
    inline void draw() const noexcept {};
  };

  class GameScreen {
  public:
    inline void process_event(sdltemplate::Event &&event,
                              ArkoGame *game) noexcept {
      using T = std::decay_t<decltype(event)>;
      if constexpr (std::is_same_v<T, sdltemplate::events::KeyPressEvent>) {
        game->current_screen_ = GameOverScreen{};
      }
    };
    inline void update() noexcept { std::cout << "Game Screen\n"; };
    inline void draw() const noexcept {};
  };

  class GameOverScreen {
  public:
    inline void process_event(sdltemplate::Event &&event,
                              ArkoGame *game) noexcept {
      using T = std::decay_t<decltype(event)>;
      if constexpr (std::is_same_v<T, sdltemplate::events::KeyPressEvent>) {
        game->current_screen_ = TitleScreen{};
      }
    };
    inline void update() noexcept { std::cout << "Game Over Screen\n"; };
    inline void draw() const noexcept {};
  };

  using Screen =
      std::variant<TitleScreen, SettingsScreen, GameScreen, GameOverScreen>;

public:
  void process_event(sdltemplate::Event &&event) noexcept;
  void update() noexcept;
  void draw() const noexcept;

private:
  Screen current_screen_{};
};
} // namespace sdltemplate::arkogame
#endif
