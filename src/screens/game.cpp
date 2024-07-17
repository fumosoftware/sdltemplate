#include "game.h"
#include "../arkogame.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <entt/entity/fwd.hpp>

Game::Game(entt::registry *world) noexcept : world_{world} {
}

void Game::process_event(SDL_Event const &event, ArkoGame &screen) noexcept {

  if (event.type == SDL_EVENT_KEY_DOWN) {
    switch (event.key.keysym.scancode) {
    case SDL_SCANCODE_T:
      screen.change_screen(Title{world_});
      break;
    case SDL_SCANCODE_D:
      screen.change_screen(GameOver{world_});
      break;
    default:
      break;
    }
  }
}

void Game::update([[maybe_unused]] float dt) noexcept {
}

void Game::draw(SDL_Renderer *renderer) const noexcept {
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 200);

  SDL_SetRenderDrawColor(renderer, 0, 255, 255, 50);
}
