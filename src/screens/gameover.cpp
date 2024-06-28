#include "gameover.h"
#include "../screens.h"
#include <iostream>

void GameOver::process_event(SDL_Event const &event,
                                   Screens &screen) noexcept {

  if (event.type == SDL_EVENT_KEY_DOWN) {
    switch (event.key.keysym.scancode) {
    case SDL_SCANCODE_T:
      screen.change_screen(Title{});
      break;
    default:
      break;
    }
  }
}

void GameOver::update([[maybe_unused]] float dt) noexcept {
  std::cout << "GameOver Screen Update\n";
}

void GameOver::draw(SDL_Renderer *renderer) const noexcept {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200);
}
