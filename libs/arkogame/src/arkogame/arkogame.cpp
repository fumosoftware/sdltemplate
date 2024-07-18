#include <utility>

#include <arkogame/arkogame.hpp>
#include <events/event.hpp>

using namespace sdltemplate::arkogame;

void ArkoGame::process_event(sdltemplate::Event &&event) noexcept {
  std::visit(
      [&](auto &&screen) {
        screen.process_event(std::forward<sdltemplate::Event>(event), this);
      },
      current_screen_);
}

void ArkoGame::update() noexcept {
  std::visit([&](auto &&screen) { screen.update(); }, current_screen_);
}

void ArkoGame::draw() const noexcept {
  std::visit([&](auto &&screen) { screen.draw(); }, current_screen_);
}
