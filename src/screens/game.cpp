#include "game.h"
#include "../arkogame.h"
#include "../components/hitbox.h"
#include "../components/position.h"
#include "../components/velocity.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <entt/entity/fwd.hpp>
#include <iostream>

Game::Game(entt::registry *world) noexcept : world_{world} {

  auto const ball = world_->create();
  world_->emplace<Position>(ball, 275.f, 50.f);
  world_->emplace<Hitbox>(ball, 0.f, 0.f, 20.f, 20.f);
  world_->emplace<Velocity>(ball, 360.f, 150.f);

  /*
  std::array<entt::entity, 10> bricks{};
  world_->create(bricks.begin(), bricks.end());

  for (auto i = 0u; i < bricks.size(); ++i) {
    if (!world_->valid(bricks[i]))
      continue;

    auto const x = (i * 50.f) + 10.f;
    auto const y = 100.f;
    world_->emplace<Position>(bricks[i], x, y);
    world_->emplace<Hitbox>(bricks[i], 0.f, 0.f, 10.f, 30.f);
  }
  */

  auto const brick = world_->create();
  world_->emplace<Position>(brick, arena_.width / 2.f, arena_.height / 2.f);
  world_->emplace<Hitbox>(brick, 0.f, 0.f, 100.f, 100.f);
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

  auto kinetic_bodies = world_->view<Position, Velocity, Hitbox>();

  auto other_bodies = world_->view<Position, Hitbox>();
  for (auto &&[ke, pos, vel, hb] : kinetic_bodies.each()) {
    auto new_x = pos.x + (vel.x * dt);
    auto new_y = pos.y + (vel.y * dt);

    std::cout << "attempted new_y: " << new_y << "\n";
    for (auto &&[oe, opos, ohb] : other_bodies.each()) {
      if (oe == ke)
        continue;

      if(pos.x < opos.x + ohb.w &&
         pos.x + hb.w > opos.x &&
         new_y < opos.y + ohb.h &&
         new_y + hb.h > opos.y) {
        std::cout << "Change Y\n";
        std::cout << "pos.x: " << pos.x << "\n";
        std::cout << "pos.x + w: " << pos.x + hb.w << "\n";
        std::cout << "new_y: " << new_y << "\n";
        std::cout << "new_y + h: " << new_y + hb.h << "\n";

        std::cout << "brick x: " << opos.x << "\n";
        std::cout << "brick x + w: " << opos.x + ohb.w << "\n";
        std::cout << "brick y: " << opos.y << "\n";
        std::cout << "brick y + h: " << opos.y + ohb.h << "\n";

        std::cout << "pos.x + hb.w > opos.x ? " << std::boolalpha
                  << ((pos.x + hb.w) > opos.x) << "\n";
        std::cout << "pos.x < opos.x + ohb.w ? " << std::boolalpha
                  << ((pos.x) < (opos.x + ohb.w)) << "\n";
        std::cout << "new_y + hb.h > opos.y ? " << std::boolalpha
                  << ((new_y + hb.h) > opos.y) << "\n";
        std::cout << "new_y < opos.y + ohb.h ? " << std::boolalpha
                  << ((new_y) < (opos.y + ohb.h)) << "\n";

        std::cout << "----\n";
        if (vel.y > 0) {
          new_y = opos.y - hb.h;
        } else {
          new_y = opos.y + ohb.h;
        }
        vel.y = -vel.y;
      }

      if (new_y < 0) {
        new_y = 0;
        vel.y = -vel.y;
      }

      if (new_y + hb.h > arena_.height) {
        new_y -= (new_y + hb.h - arena_.height);
        vel.y = -vel.y;
      }
      pos.y = new_y;

      if(new_x < opos.x + ohb.w &&
         new_x + hb.w > opos.x &&
         pos.y < opos.y + ohb.h &&
         pos.y + hb.h > opos.y) {
        std::cout << "Change X\n";
        std::cout << "new pos.x: " << new_x << "\n";
        std::cout << "new pos.x + w: " << new_x + hb.w << "\n";
        std::cout << "pos.y: " << pos.y << "\n";
        std::cout << "pos.y + h: " << pos.y + hb.h << "\n";

        std::cout << "brick x: " << opos.x << "\n";
        std::cout << "brick x + w: " << opos.x + ohb.w << "\n";
        std::cout << "brick y: " << opos.y << "\n";
        std::cout << "brick y + h: " << opos.y + ohb.h << "\n";

        std::cout << "new pos.x + hb.w > opos.x ? " << std::boolalpha
                  << ((new_x + hb.w) > opos.x) << "\n";
        std::cout << "new pos.x < opos.x + ohb.w ? " << std::boolalpha
                  << ((new_x) < (opos.x + ohb.w)) << "\n";
        std::cout << "pos.y + hb.h > opos.y ? " << std::boolalpha
                  << ((pos.y + hb.h) > opos.y) << "\n";
        std::cout << "pos.y < opos.y + ohb.h ? " << std::boolalpha
                  << ((pos.y) < (opos.y + ohb.h)) << "\n";

        std::cout << "----\n";

        if (vel.x > 0) {
          new_x = opos.x - hb.w;
        } else {
          new_x = opos.x + ohb.w;
        }
        vel.x = -vel.x;
      }
    }

    if (new_x < 0) {
      new_x = 0;
      vel.x = -vel.x;
    }

    if (new_x + hb.w > arena_.width) {
      new_x -= (new_x + hb.w - arena_.width);
      vel.x = -vel.x;
    }

    pos.x = new_x;
  }
}

void Game::draw(SDL_Renderer *renderer) const noexcept {
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 200);

  auto view = world_->view<Position, Velocity, Hitbox>();
  for (auto &&[_, position, velocity, hitbox] : view.each()) {
    SDL_FRect rect{
        .x = position.x, .y = position.y, .w = hitbox.w, .h = hitbox.h};
    SDL_RenderFillRect(renderer, &rect);
  }

  SDL_SetRenderDrawColor(renderer, 255, 255, 0, 200);
  auto oview = world_->view<Position, Hitbox>(entt::exclude<Velocity>);
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
