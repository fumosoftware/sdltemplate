#include "sdlapp.h"
#include <cstdint>

#include <chrono>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_render.h>
#include <spdlog/spdlog.h>

using Duration = std::chrono::duration<float>;
using namespace std::literals;
namespace {
constexpr std::uint32_t INIT_FLAGS{SDL_INIT_VIDEO | SDL_INIT_EVENTS};
} // namespace

SDLApp::SDLApp() {
  if (SDL_Init(INIT_FLAGS) != 0) {
    throw SDLException{"Can not continue execution of application.",
                       SDL_GetError()};
  }

  auto const width = config_["window"]["width"].value_or(1000);
  auto const height = config_["window"]["width"].value_or(680);
  if (SDL_CreateWindowAndRenderer("Title", width, height, 0, &window_,
                                  &renderer_) != 0) {
    throw SDLException("Can not continue execution of application.",
                       SDL_GetError());
  }
}

SDLApp::~SDLApp() {
  SDL_DestroyRenderer(renderer_);
  SDL_DestroyWindow(window_);
  SDL_Quit();
}

int SDLApp::run() noexcept {

  while (is_running_) {
    process_events();
    update();
    draw();
  }
  return 0;
}

void SDLApp::process_events() noexcept {
  SDL_Event event{};

  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_EVENT_KEY_DOWN:
      if (event.key.keysym.scancode == SDL_SCANCODE_Q) {
        is_running_ = false;
        break;
      }
      screens_.process_event(event);
      break;
    default:
        screens_.process_event(event);
      break;
    }
  }
}

void SDLApp::update() noexcept {
  screens_.update(10.f);
}

void SDLApp::draw() noexcept {
  SDL_RenderClear(renderer_);
  SDL_SetRenderDrawColor(renderer_, 100, 229, 255, 200);
  screens_.draw(renderer_);
  SDL_RenderPresent(renderer_);
}
