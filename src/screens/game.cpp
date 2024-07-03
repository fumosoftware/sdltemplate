#include "game.h"
#include "../arkogame.h"
#include "../components/collider.h"
#include "../components/position.h"
#include "../components/velocity.h"
#include "../components/tags.h"
#include "../systems/movement.h"
#include "../systems/arenacollision.h"
#include "../systems/brickcollision.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <entt/entity/fwd.hpp>

Game::Game(entt::registry *world) noexcept : world_{world} {
  auto const ball = world_->create();
  world_->emplace<Position>(ball, 275.f, 50.f);
  world_->emplace<Collider>(ball, 0.f, 0.f, 20.f, 20.f);
  world_->emplace<Velocity>(ball, 360.f, 150.f);
  world_->emplace<BallTag>(ball);

  auto const brick = world_->create();
  world_->emplace<Position>(brick, 275.f, 350.f);
  world_->emplace<Collider>(brick, 0.f, 0.f, 100.f, 100.f);
  world_->emplace<BrickTag>(brick);
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
  movement(*world_, dt);
  check_arena_collision(*world_, arena_.width, arena_.height);
  check_brick_collisions(*world_);
}

void Game::draw(SDL_Renderer *renderer) const noexcept {
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 200);

  auto view = world_->view<Position, Velocity, Collider>();
  for (auto &&[_, position, velocity, hitbox] : view.each()) {
    SDL_FRect rect{
        .x = position.x, .y = position.y, .w = hitbox.w, .h = hitbox.h};
    SDL_RenderFillRect(renderer, &rect);
  }

  SDL_SetRenderDrawColor(renderer, 255, 255, 0, 200);
  auto oview = world_->view<Position, Collider>(entt::exclude<Velocity>);
  for (auto && [_, position, hitbox] : oview.each()) {
    SDL_FRect rect{
        .x = position.x, .y = position.y, .w = hitbox.w, .h = hitbox.h};
    SDL_RenderFillRect(renderer, &rect);
  }
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 200);

  SDL_FRect arena{.x = 0.f, .y = 0.f, .w = arena_.width, .h = arena_.height};
  SDL_RenderRect(renderer, &arena);

  SDL_SetRenderDrawColor(renderer, 0, 255, 255, 50);
}
