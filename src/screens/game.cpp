#include "game.h"
#include "../arkogame.h"
#include "../components/position.h"
#include "../components/hitbox.h"
#include "../components/velocity.h"
#include <SDL3/SDL_render.h>
#include <iostream>

Game::Game(entt::registry* world) noexcept : world_{world} {

  auto const ball = world_->create();
  world_->emplace<Position>(ball, 10.f, 10.f);
  world_->emplace<Hitbox>(ball, 0.f, 0.f, 20.f, 20.f);
  world_->emplace<Velocity>(ball, 100.f, 0.f);
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
  std::cout << "Game Screen Update\n";

  auto view = world_->view<Position, Velocity>();
  for(auto&& [_, pos, vel] : view.each()) {
    pos.x += vel.x * dt;
    if(pos.x > 180.f)  {
      pos.x = 180.f;
      vel.x = -vel.x;
    } else if(pos.x < 0) {
      pos.x = 0;
      vel.x = -vel.x;
    }
  }
}

void Game::draw(SDL_Renderer *renderer) const noexcept {
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 200);

  auto view = world_->view<Position, Hitbox>();
  for(auto&& [_, position, hitbox] : view.each()) {
    SDL_FRect rect {.x = position.x - (hitbox.w / 2), .y = position.y - (hitbox.h / 2), .w = hitbox.w, .h = hitbox.h };
    SDL_RenderFillRect(renderer, &rect);
  }

  SDL_SetRenderDrawColor(renderer, 0, 255, 255, 50);
}
