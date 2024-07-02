#include "title.h"
#include "../arkogame.h"
#include <iostream>

Title::Title(entt::registry* world) noexcept : world_{world} {}
void Title::process_event(SDL_Event const &event, ArkoGame &screen) noexcept {

  if (event.type == SDL_EVENT_KEY_DOWN) {
    switch (event.key.keysym.scancode) {
    case SDL_SCANCODE_G:
      screen.change_screen(Game{world_});
      break;
    case SDL_SCANCODE_S:
      screen.change_screen(Settings{world_});
      break;
    default:
      break;
    }
  }
}

void Title::update([[maybe_unused]] float dt) noexcept {
  std::cout << "Title Screen Update\n";
}

void Title::draw(SDL_Renderer *renderer) const noexcept {
  SDL_SetRenderDrawColor(renderer, 0, 0, 255, 200);
}
