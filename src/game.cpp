#include "game.h"

namespace {
void update([[maybe_unused]] gamestate::Title, [[maybe_unused]] float dt) {}
void update([[maybe_unused]] gamestate::Gameplay, [[maybe_unused]] float dt) {}

void process_event([[maybe_unused]] gamestate::Title, [[maybe_unused]] SDL_Event const& event) {}
void process_event([[maybe_unused]] gamestate::Gameplay, [[maybe_unused]] SDL_Event const& event) {}

void draw([[maybe_unused]] gamestate::Title, [[maybe_unused]] SDL_Renderer const* renderer) {}
void draw([[maybe_unused]] gamestate::Gameplay, [[maybe_unused]] SDL_Renderer const* renderer) {}
} // namespace

void Game::update(float dt) noexcept {

  std::visit(
      [dt](auto &&state) {
        using T = std::decay_t<decltype(state)>;
        if constexpr (std::is_same_v<T, std::monostate> == false) {
          ::update(state, dt);
        }
      },
      current_state_);
}

void Game::process_event(SDL_Event const& event) noexcept {

  std::visit(
      [&event](auto &&state) {
        using T = std::decay_t<decltype(state)>;
        if constexpr (std::is_same_v<T, std::monostate> == false) {
          ::process_event(state, event);
        }
      },
      current_state_);
}

void Game::draw(SDL_Renderer const* renderer) noexcept {

  std::visit(
      [renderer](auto &&state) {
        using T = std::decay_t<decltype(state)>;
        if constexpr (std::is_same_v<T, std::monostate> == false) {
          ::draw(state, renderer);
        }
      },
      current_state_);
}
