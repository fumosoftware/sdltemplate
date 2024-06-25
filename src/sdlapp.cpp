#include "sdlapp.h"
#include <cstdint>

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_render.h>
#include <spdlog/spdlog.h>
#include <toml++/toml.h>

using namespace std::literals;
namespace {
constexpr std::uint32_t INIT_FLAGS{SDL_INIT_VIDEO | SDL_INIT_EVENTS};
constexpr std::string_view DEFAULT_CONFIG{
    R"(
[window]
width  = 1000
height = 680
  )"sv};

} // namespace

SDLApp::SDLApp() : config_{toml::parse(DEFAULT_CONFIG)} {
  if (SDL_Init(INIT_FLAGS) != 0) {
    throw SDLException{"Can not continue execution of application.",
                       SDL_GetError()};
  }

  auto const width = config_["window"]["width"].value_or(380);
  auto const height = config_["window"]["width"].value_or(160);
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

  while (is_running) {
    process_events();
    draw();
  }
  return 0;
}

void SDLApp::process_events() noexcept {
  SDL_Event event{};

  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_EVENT_KEY_DOWN:
      is_running = false;
      break;
    default:
      break;
    }
  }
}

void SDLApp::draw() noexcept {
  SDL_RenderClear(renderer_);
  SDL_SetRenderDrawColor(renderer_, 100, 229, 255, 200);
  SDL_RenderPresent(renderer_);
}
