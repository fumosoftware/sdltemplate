// #include "sdlapp.h"
// #include <spdlog/spdlog.h>

#include "events/keys.hpp"
#include <SDL3/SDL.h>
#include <events/event.hpp>

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
int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) noexcept {

  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
  auto window = SDL_CreateWindow("", 300, 100, 0);
  auto renderer = SDL_CreateRenderer(window, nullptr);

  bool is_running{true};
  SDL_Event event{};
  while (is_running) {
    while (SDL_PollEvent(&event) == SDL_TRUE) {
      std::visit(
          [&is_running](auto &&event) {
            using T = std::decay_t<decltype(event)>;
            if constexpr (std::is_same_v<T,
                                         sdltemplate::events::KeyPressEvent>) {
              if (event.key == sdltemplate::events::Key::Q)
                is_running = false;
            } else if constexpr (std::is_same_v<
                                     T, sdltemplate::events::KeyReleaseEvent>) {
              //is_running = false;
            } else if constexpr (std::is_same_v<
                                     T, sdltemplate::events::QuitEvent>) {
              is_running = false;
            } else if constexpr (std::is_same_v<T, std::monostate>) {
              // ERROR Should never reach this block!
            }
          },
          translate_sdl_event(event));
    }

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 200);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
  }
  /*
  try {
    return SDLApp{}.run();
  } catch (SDLException const &error) {
    spdlog::error(error.what());
  }
*/

  return 1;
}
