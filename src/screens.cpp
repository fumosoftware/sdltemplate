#include "screens.h"

void Screens::process_event(SDL_Event const &event) noexcept {
  std::visit(
      [event, this](auto &&screen) { screen.process_event(event, *this); },
      current_screen_);
}

void Screens::update([[maybe_unused]] float dt) noexcept {
  std::visit([dt](auto &&screen) { screen.update(dt); }, current_screen_);
}

void Screens::draw(SDL_Renderer *renderer) const noexcept {
  std::visit([renderer](auto &&screen) { screen.draw(renderer); },
             current_screen_);
}
