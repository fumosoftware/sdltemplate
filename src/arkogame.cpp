#include "arkogame.h"
#include <chrono>
#include "components/position.h"
#include "components/velocity.h"

using Duration = std::chrono::duration<float>;
using namespace std::literals;

ArkoGame::ArkoGame() noexcept : current_screen_{Title{&world_}} {}

void ArkoGame::process_event(SDL_Event const &event) noexcept {
  std::visit(
      [event, this](auto &&screen) { screen.process_event(event, *this); },
      current_screen_);
}

void ArkoGame::update([[maybe_unused]] float dt) noexcept {
  static auto previous_frame_time = std::chrono::steady_clock::now();
  static Duration accumulator{0s};
  static auto max_dt{.25s};
  static auto fixed_dt{1s / 100.f};

  std::visit(
      [&](auto &&screen) {
        auto const current_frame_time = std::chrono::steady_clock::now();
        auto const frame_dt =
            (current_frame_time - previous_frame_time) > max_dt
                ? max_dt
                : (current_frame_time - previous_frame_time);
        previous_frame_time = current_frame_time;
        accumulator += frame_dt;

        if (accumulator < fixed_dt)
          return;
        while (accumulator >= fixed_dt) {
          screen.update(fixed_dt.count());
          accumulator -= fixed_dt;
        }

        interpolate(accumulator.count());

        // interpolat to accomidate for leftover time in the accumulator
        // auto const alpha = accumulator / fixed_dt;
        // std::lerp(ball.x, old_ball.x, alpha);
        //          update(state, dt);
      },
      current_screen_);
}

void ArkoGame::draw(SDL_Renderer *renderer) const noexcept {
  std::visit([renderer](auto &&screen) { screen.draw(renderer); },
             current_screen_);
}

void ArkoGame::interpolate(float remainder) noexcept {
  static auto const fixed_dt{1s/ 100.f};
  auto const alpha = remainder / fixed_dt.count();

  auto view = world_.view<Position, Velocity>();

  for(auto&& [_, pos, vel] : view.each()) {
    auto old_x = pos.x - (vel.x * fixed_dt.count());
    pos.x = std::lerp(pos.x, old_x, alpha);
  }
}
