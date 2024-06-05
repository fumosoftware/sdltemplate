#include "ball.h"
#include <SDL.h>
#include <SDL_render.h>
#include <chrono>
#include <cmath>

using namespace std::chrono_literals;
using duration = std::chrono::duration<double>;

//Represents the entire gamestate
namespace {
constexpr auto fixed_dt = 1s / 100.;
constexpr auto max_dt = .25s;
constexpr auto window_width = 320;
constexpr auto window_height = 180;
SDL_Window *window{};
SDL_Renderer *renderer{};
std::chrono::time_point<std::chrono::steady_clock> previous_frame_time{};
duration accumulator{0s};
Ball old_ball{.x = 5, .y = 10, .w = 10, .h = 10};
Ball ball{.x = 5, .y = 10, .w = 10, .h = 10};
float x_vel = 50.f;
bool is_running = true;
} // namespace

void handle_events();
void run_game_logic();
void render();
int app_main() {
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
    return 1;
  }

  window = SDL_CreateWindow("sdlapp", window_width, window_height, 0);
  renderer = SDL_CreateRenderer(window, "window_renderer", -1);

  previous_frame_time = std::chrono::steady_clock::now();

  while (is_running) {
    handle_events();
    if (!is_running)
      break;

    run_game_logic();

    render();
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}

void handle_events() {
  SDL_Event event{};
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_EVENT_KEY_DOWN: {
      if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
        is_running = false;
      }
      break;
    }
    }
  }
}

void run_game_logic() {
  auto const current_frame_time = std::chrono::steady_clock::now();
  auto const frame_dt = (current_frame_time - previous_frame_time) > max_dt
                            ? max_dt
                            : (current_frame_time - previous_frame_time);
  previous_frame_time = current_frame_time;
  accumulator += frame_dt;

  while (accumulator >= fixed_dt) {
    old_ball = ball;
    ball.x = ball.x + (x_vel * fixed_dt).count();
    
    //Check collision against window borders
    if (ball.x + ball.w > window_width || ball.x - ball.w < -ball.w)
      x_vel *= -1.f;

    accumulator -= fixed_dt;
  }

  // integrate to accomidate for leftover time in the accumulator
  auto const alpha = accumulator / fixed_dt;
  std::lerp(ball.x, old_ball.x, alpha);
}

void render() {
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, 255, 100, 200, 255);

  SDL_FRect ball_rect{.x = ball.x, .y = ball.y, .w = ball.w, .h = ball.h};
  SDL_RenderFillRect(renderer, &ball_rect);

  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderPresent(renderer);
}
