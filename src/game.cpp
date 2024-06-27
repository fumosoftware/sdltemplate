#include "game.h"
#include <SDL3/SDL_render.h>
#include <chrono>

using Duration = std::chrono::duration<float>;
using namespace std::literals;

void Game::update() noexcept {

  static auto previous_frame_time = std::chrono::steady_clock::now();
  static Duration accumulator{0s};
  static auto max_dt{.25s};
  static auto fixed_dt{1s / 100.f};

  auto const current_frame_time = std::chrono::steady_clock::now();
  auto const frame_dt = (current_frame_time - previous_frame_time) > max_dt
                            ? max_dt
                            : (current_frame_time - previous_frame_time);
  previous_frame_time = current_frame_time;
  accumulator += frame_dt;

  if (accumulator < fixed_dt)
    return;
  while (accumulator >= fixed_dt) {
    // This may be a performance killer?
    // We did not put the timing logic within std::visit because
    // then we would not be able to change state from within std::visit
    //(changing state and then accessing while inside std::visit is UB)
    // If this is too much, put the timing logic within the std::visit and
    // add substates to the current state
    //( Game::GamePlay::Menu, Game::GamePlay::GameOver,... instead of
    //  Game::Menu, Game::GameOver, ...)
    auto maybe_state = std::visit(
        [&](auto &&state) {
          using T = std::decay_t<decltype(state)>;
          if constexpr (std::is_same_v<T, std::monostate> == false) {
            return this->update(state, fixed_dt.count());
          } else {

          return std::nullopt;
        }
        },
        current_state_);

    if(maybe_state) {
      current_state_ = maybe_state.value();
    }

    accumulator -= fixed_dt;
  }

  // integrate to accomidate for leftover time in the accumulator
  // auto const alpha = accumulator / fixed_dt;
  // std::lerp(ball.x, old_ball.x, alpha);
  //          update(state, dt);
}

void Game::process_event(SDL_Event const &event) noexcept {

  auto maybe_state = std::visit(
      [&](auto &&state) {
        using T = std::decay_t<decltype(state)>;
        if constexpr (std::is_same_v<T, std::monostate> == false) {
          return process_event(state, event);
        } else {
          return std::nullopt;
        }
      },
      current_state_);

  if(maybe_state) {
    current_state_ = *maybe_state;
  }
}

void Game::draw(SDL_Renderer *renderer) const noexcept {

  std::visit(
      [&](auto &&state) {
        using T = std::decay_t<decltype(state)>;
        if constexpr (std::is_same_v<T, std::monostate> == false) {
          draw(state, renderer);
        }
      },
      current_state_);
}

std::optional<Game::GameState>
Game::update([[maybe_unused]] TitleScreen &state,
             [[maybe_unused]] float const dt) noexcept {
  // std::cout << "In title state\n";
  return std::nullopt;
}
std::optional<Game::GameState>
Game::update([[maybe_unused]] GameScreen &state,
             [[maybe_unused]] float const dt) noexcept {
  // std::cout << "In gameplay state\n";
  return std::nullopt;
}

std::optional<Game::GameState>
Game::process_event([[maybe_unused]] TitleScreen &state,
                    [[maybe_unused]] SDL_Event const &event) noexcept {
  switch (event.type) {
  case SDL_EVENT_KEY_DOWN: {
    if (event.key.keysym.scancode == SDL_SCANCODE_A) {
      return GameScreen{};
    }
  } break;
  default:
    break;
  }
  return std::nullopt;
}
std::optional<Game::GameState>
Game::process_event([[maybe_unused]] GameScreen &state,
                    [[maybe_unused]] SDL_Event const &event) noexcept {
  switch (event.type) {
  case SDL_EVENT_KEY_DOWN: {
    if (event.key.keysym.scancode == SDL_SCANCODE_S) {
      return TitleScreen{};
    }
  } break;
  default:
    break;
  }

  return std::nullopt;
}

void Game::draw([[maybe_unused]] TitleScreen const &,
                [[maybe_unused]] SDL_Renderer *renderer) const noexcept {
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 200);
}
void Game::draw([[maybe_unused]] GameScreen const &,
                [[maybe_unused]] SDL_Renderer *renderer) const noexcept {
  SDL_SetRenderDrawColor(renderer, 255, 255, 0, 200);
}
