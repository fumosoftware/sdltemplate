#include "sdlapp.h"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <chrono>
#include <cstdint>

#include <events/event.hpp>
using Duration = std::chrono::duration<float>;
using namespace std::literals;
namespace {
constexpr std::uint32_t INIT_FLAGS{SDL_INIT_VIDEO | SDL_INIT_EVENTS};


sdltemplate::events::Key translate_scancode(SDL_Scancode scancode) {
  switch (scancode) {
  case SDL_SCANCODE_A:
    return sdltemplate::events::Key::A;
  case SDL_SCANCODE_B:
    return sdltemplate::events::Key::B;
  case SDL_SCANCODE_C:
    return sdltemplate::events::Key::C;
  case SDL_SCANCODE_D:
    return sdltemplate::events::Key::D;
  case SDL_SCANCODE_E:
    return sdltemplate::events::Key::E;
  case SDL_SCANCODE_F:
    return sdltemplate::events::Key::F;
  case SDL_SCANCODE_G:
    return sdltemplate::events::Key::G;
  case SDL_SCANCODE_H:
    return sdltemplate::events::Key::H;
  case SDL_SCANCODE_I:
    return sdltemplate::events::Key::I;
  case SDL_SCANCODE_J:
    return sdltemplate::events::Key::J;
  case SDL_SCANCODE_K:
    return sdltemplate::events::Key::K;
  case SDL_SCANCODE_L:
    return sdltemplate::events::Key::L;
  case SDL_SCANCODE_M:
    return sdltemplate::events::Key::M;
  case SDL_SCANCODE_N:
    return sdltemplate::events::Key::N;
  case SDL_SCANCODE_O:
    return sdltemplate::events::Key::O;
  case SDL_SCANCODE_P:
    return sdltemplate::events::Key::P;
  case SDL_SCANCODE_Q:
    return sdltemplate::events::Key::Q;
  case SDL_SCANCODE_R:
    return sdltemplate::events::Key::R;
  case SDL_SCANCODE_S:
    return sdltemplate::events::Key::S;
  case SDL_SCANCODE_T:
    return sdltemplate::events::Key::T;
  case SDL_SCANCODE_U:
    return sdltemplate::events::Key::U;
  case SDL_SCANCODE_V:
    return sdltemplate::events::Key::V;
  case SDL_SCANCODE_W:
    return sdltemplate::events::Key::W;
  case SDL_SCANCODE_X:
    return sdltemplate::events::Key::X;
  case SDL_SCANCODE_Y:
    return sdltemplate::events::Key::Y;
  case SDL_SCANCODE_Z:
    return sdltemplate::events::Key::Z;
  default:
    return sdltemplate::events::Key::UNKNOWN;
  }
}

sdltemplate::Event translate_sdl_event(SDL_Event const &event) {
  switch (event.type) {
  case SDL_EVENT_KEY_DOWN:
    return sdltemplate::events::KeyPressEvent{
        .key = translate_scancode(event.key.keysym.scancode)};
  case SDL_EVENT_KEY_UP:
    return sdltemplate::events::KeyReleaseEvent{
        .key = translate_scancode(event.key.keysym.scancode)};
  case SDL_EVENT_QUIT:
    return sdltemplate::events::QuitEvent{};
  default:
    return {};
  }
}

} // namespace

SDLApp::SDLApp() {
  if (SDL_Init(INIT_FLAGS) != 0) {
    throw SDLException{"Can not continue execution of application.",
                       SDL_GetError()};
  }

  auto const width = 1000;
  auto const height = 800;
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
      game_.process_event(translate_sdl_event(event));
      break;
    default:
      game_.process_event(translate_sdl_event(event));
      break;
    }
  }
}

void SDLApp::update() noexcept { 
  game_.update(); 
}

void SDLApp::draw() noexcept {
  SDL_RenderClear(renderer_);
  SDL_SetRenderDrawColor(renderer_, 100, 229, 255, 200);
  game_.draw();
  //game_.draw(renderer_);
  SDL_RenderPresent(renderer_);
}

