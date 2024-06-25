#include "game.h"
#include <spdlog/fmt/fmt.h>
#include <iostream>

namespace {} // namespace

void Game::update(float const dt) noexcept {

  std::visit(
      [&](auto &&state) {
        using T = std::decay_t<decltype(state)>;
        if constexpr (std::is_same_v<T, std::monostate> == false) {
          update(state, dt);
        }
      },
      current_state_);
}

void Game::process_event(SDL_Event const &event) noexcept {

  std::visit(
      [&](auto &&state) {
        using T = std::decay_t<decltype(state)>;
        if constexpr (std::is_same_v<T, std::monostate> == false) {
          process_event(state, event);
        }
      },
      current_state_);
}

void Game::draw(SDL_Renderer const *renderer) const noexcept {

  std::visit(
      [&](auto &&state) {
        using T = std::decay_t<decltype(state)>;
        if constexpr (std::is_same_v<T, std::monostate> == false) {
          draw(state, renderer);
        }
      },
      current_state_);
}

void Game::update([[maybe_unused]] gamestate::Title& state,
                  [[maybe_unused]] float const dt) noexcept {
  std::cout << "In title state\n";
}
void Game::update([[maybe_unused]] gamestate::Gameplay& state,
                  [[maybe_unused]] float const dt) noexcept {
  std::cout << "In gameplay state\n";
}

void Game::process_event([[maybe_unused]] gamestate::Title &state,
                         [[maybe_unused]] SDL_Event const &event) noexcept {
  switch (event.type) {
  case SDL_EVENT_KEY_DOWN: {
    handle_state_change(state, event);
  } break;
  default:
    break;
  }
}
void Game::process_event([[maybe_unused]] gamestate::Gameplay &state,
                         [[maybe_unused]] SDL_Event const &event) noexcept {}

void Game::handle_state_change(
    [[maybe_unused]] gamestate::Title const&,
    [[maybe_unused]] SDL_Event const &event) noexcept {
  if (event.key.keysym.scancode == SDL_SCANCODE_A) {
    current_state_ = gamestate::Gameplay{};
  }
}
void Game::handle_state_change(
    [[maybe_unused]] gamestate::Gameplay const&,
    [[maybe_unused]] SDL_Event const &event) noexcept {}

void Game::draw([[maybe_unused]] gamestate::Title const&,
                [[maybe_unused]] SDL_Renderer const *renderer) const noexcept {}
void Game::draw([[maybe_unused]] gamestate::Gameplay const&,
                [[maybe_unused]] SDL_Renderer const *renderer) const noexcept {}
