#include "sdlapp.h"
#include <cstdint>
#include <optional>

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_render.h>
#include <spdlog/spdlog.h>
#include <toml++/toml.h>

namespace {
constexpr std::uint32_t INIT_FLAGS{SDL_INIT_VIDEO | SDL_INIT_EVENTS};
std::optional<std::pair<SDL_Window *, SDL_Renderer *>>
create_window_and_renderer(toml::table const &config) noexcept {

  SDL_Window *window{nullptr};
  SDL_Renderer *renderer{nullptr};

  auto const window_width = config["window"]["width"].value_or(380);
  auto const window_height = config["window"]["width"].value_or(160);
  if (SDL_CreateWindowAndRenderer("Title", window_width, window_height, 0,
                                  &window, &renderer) != 0) {
    spdlog::error("Error creating window context: %s", SDL_GetError());
    return std::nullopt;
  }
  return std::pair{window, renderer};
}
} // namespace

int SDLApp::exec() noexcept {

  if (SDL_Init(::INIT_FLAGS) != 0) {
    return 1;
  }

  if (auto maybeApp = create(); maybeApp != std::nullopt) {
    maybeApp->run();
  }

  SDL_Quit();
  return 0;
}

std::optional<SDLApp> SDLApp::create() noexcept {
  if (SDL_WasInit(INIT_FLAGS) != INIT_FLAGS) {
    spdlog::error("Error during initialization: %s", SDL_GetError());
    return std::nullopt;
  }

  auto parse_result = toml::parse_file("./data/config.toml");
  if (!parse_result) {
    spdlog::error("Error reading config.toml from data/ folder");
    return std::nullopt;
  }

  auto maybe_window_and_renderer =
      create_window_and_renderer(parse_result.table());
  if (!maybe_window_and_renderer) {
    return std::nullopt;
  }

  auto [window, renderer] = *maybe_window_and_renderer;
  return SDLApp{window, renderer};
}

SDLApp::SDLApp(SDL_Window *window, SDL_Renderer *renderer) noexcept
    : window_{window, SDL_DestroyWindow},
      renderer{renderer, SDL_DestroyRenderer} {}

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
  SDL_RenderClear(renderer.get());
  SDL_SetRenderDrawColor(renderer.get(), 100, 229, 255, 200);
  SDL_RenderPresent(renderer.get());
}
