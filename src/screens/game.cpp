#include "game.h"
#include "../screens.h"
#include <iostream>

void Game::process_event(SDL_Event const &event, Screens &screen) noexcept {

  if (event.type == SDL_EVENT_KEY_DOWN) {
    switch (event.key.keysym.scancode) {
    case SDL_SCANCODE_T:
      screen.change_screen(Title{});
      break;
    case SDL_SCANCODE_D:
      screen.change_screen(GameOver{});
      break;
    default:
      break;
    }
  }
}

void Game::update([[maybe_unused]] float dt) noexcept {
  std::cout << "Game Screen Update\n";
}

void Game::draw(SDL_Renderer *renderer) const noexcept {
  SDL_SetRenderDrawColor(renderer, 0, 255, 255, 50);
}
