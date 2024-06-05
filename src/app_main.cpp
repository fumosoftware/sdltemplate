#include "logging.h"
#include <SDL.h>
#include <SDL_render.h>
#include <chrono>
#include <cmath>
#include "ball.h"

using namespace std::chrono_literals;

constexpr auto fixed_dt = 1s / 100.;
constexpr auto max_dt = .25s;
using duration = std::chrono::duration<double>;

int app_main() {
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
    return 1;
  }

  SDL_Window *const window = SDL_CreateWindow("sdlapp", 320, 180, 0);
  SDL_Renderer *const renderer =
      SDL_CreateRenderer(window, "window_renderer", -1);

  auto previous_frame_time = std::chrono::steady_clock::now();
  duration accumulator{0s};

  SDL_Event event{};
  bool is_running = true;

  Ball old_ball{.x = 5, .y = 10};
  Ball ball{.x = 5, .y = 10};

  float x_vel = 50.f;

  while (is_running) {
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_EVENT_KEY_DOWN: {
        if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
          is_running = false;
          break;
        }
      }
      }
    }

    if (!is_running)
      break;

    auto const current_frame_time = std::chrono::steady_clock::now();
    auto const frame_dt = (current_frame_time - previous_frame_time) > max_dt
                              ? max_dt
                              : (current_frame_time - previous_frame_time);
    previous_frame_time = current_frame_time;
    accumulator += frame_dt;

    while (accumulator >= fixed_dt) {
      old_ball = ball;
      ball.x = ball.x + (x_vel * fixed_dt).count(); 
      if(ball.x + 10 > 330 || ball.x - 10 < -20) x_vel *= -1.f;
      accumulator -= fixed_dt;
    }

    // integrate
     auto const alpha = accumulator / fixed_dt;
     std::lerp(ball.x, old_ball.x, alpha);

    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 100, 200, 255);

    SDL_FRect ball_rect{.x = ball.x, .y = ball.y, .w = 10, .h = 10};
    SDL_RenderFillRect(renderer, &ball_rect);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderPresent(renderer);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
