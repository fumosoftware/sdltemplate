#include "sdlapp.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_render.h>
#include <iostream>

#include <toml++/toml.h>

/*
 *

using namespace std::chrono_literals;
using Duration = std::chrono::duration<double>;

//Represents the entire gamestate
namespace {
constexpr auto fixed_dt = 1s / 100.;
constexpr auto max_dt = .25s;
constexpr auto window_width = 320;
constexpr auto window_height = 180;
SDL_Window *window{};
SDL_Renderer *renderer{};
std::chrono::time_point<std::chrono::steady_clock> previous_frame_time{};
Duration accumulator{0s};
Ball old_ball{.x = 5, .y = 10, .w = 10, .h = 10};
Ball ball{.x = 5, .y = 10, .w = 10, .h = 10};
float x_vel = 50.f;
bool is_running = true;
} // namespace
 */

std::variant<SDLApp, SDLApp::Error> SDLApp::create() noexcept {

  SDLApp app{};
  if (SDL_WasInit(0) != (SDL_INIT_VIDEO | SDL_INIT_EVENTS)) {
    return Error::INITIALIZATION_FAILED;
  }

  if (!app.window_) {
    return Error::WINDOW_CREATION;
  }

  if (!app.renderer_) {
    return Error::RENDERER_CREATION;
  }

  return app;
}

std::variant<SDLApp, SDLApp::Error>
SDLApp::create_from(std::filesystem::path const path) noexcept {

  if (!std::filesystem::exists(path)) {
    std::cout << "Config not found\n";
    return SDLApp::create();
  }

  auto config = toml::parse_file(path.c_str());
  auto window_height = config["window"]["height"].value_or(120u);
  auto window_width = config["window"]["width"].value_or(380u);

  SDLApp maybeApp{window_width, window_height};
  return maybeApp;
}

SDLApp::SDLApp() noexcept : SDLApp(DEFAULT_WIDTH, DEFAULT_HEIGHT) {}

SDLApp::SDLApp(unsigned int const width, unsigned int const height) noexcept {
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
    // Log Error
    std::cout << "Nothing initialized\n";
    is_running_ = false;
  }

  window_ = SDL_CreateWindow("Title", width, height, 0);
  if (!window_) {
    // Log Error
    std::cout << "No window\n";
    is_running_ = false;
  }
  renderer_ = SDL_CreateRenderer(window_, nullptr);
  if (!renderer_) {
    // Log Error
    std::cout << "No renderer\n";
    is_running_ = false;
  }
}

SDLApp::SDLApp(SDLApp &&other) noexcept {
  //Increment the internal counter for SDL_Video and SDL_Event
  // in order to prevent them from being destroyed by our destructor.
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

  this->renderer_ = std::move(other.renderer_);
  this->window_ = std::move(other.window_);
}

SDLApp::~SDLApp() noexcept {
  // SDL_Quit destroys objects as well as attempting to de-initialize everything
  // So we first call SDL_QuitSubsystem(...) to attempt to de-initialize, then
  // if everything was successfully de-initialized, we can call SDL_Quit
  SDL_QuitSubSystem(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
  if (SDL_WasInit(SDL_INIT_VIDEO | SDL_INIT_EVENTS) == 0) {
    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);
    SDL_Quit();
  }
}

int SDLApp::run() noexcept {

  while (is_running_) {
    process_events();

    /*
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
    */
    draw();
  }

  return 0;
}

void SDLApp::process_events() noexcept {
  SDL_Event event{};
  while (SDL_PollEvent(&event) != SDL_FALSE) {
    if (event.type == SDL_EVENT_QUIT) {
      is_running_ = false;
    } else if (event.type == SDL_EVENT_KEY_DOWN) {
      if (event.key.keysym.scancode == SDL_SCANCODE_Q) {
        is_running_ = false;
      }
    }
  }
}

void SDLApp::draw() noexcept {

  SDL_SetRenderDrawColor(renderer_, 255, 100, 200, 200);
  SDL_RenderClear(renderer_);
  SDL_RenderPresent(renderer_);
}
