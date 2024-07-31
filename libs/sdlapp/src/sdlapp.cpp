#include <sdlapp/sdlapp.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <iostream>

sdltemplate::SDLApp::SDLApp() try {
  auto const did_init = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
  if (did_init != 0)
    throw sdltemplate::SDLInitializeError{};

  m_window = SDL_CreateWindow("Title", 400, 200, 0);
  if (!m_window)
    throw sdltemplate::SDLWindowCreationError{};

  m_renderer = SDL_CreateRenderer(m_window, nullptr);
  if (!m_renderer) {
    SDL_DestroyWindow(m_window);
    throw sdltemplate::SDLRendererCreationError{};
  }

} catch (...) {
  SDL_Quit();
}

sdltemplate::SDLApp::~SDLApp() noexcept {
  SDL_DestroyRenderer(m_renderer);
  SDL_DestroyWindow(m_window);
  SDL_Quit();
}

int sdltemplate::SDLApp::run() noexcept {

  SDL_Event event;

  while (m_is_running) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_KEY_DOWN) {
        m_is_running = false;
      }
    }

    SDL_RenderClear(m_renderer);
    SDL_RenderPresent(m_renderer);
  }

  return 0;
}

void sdltemplate::SDLApp::poll_events() noexcept {}

void sdltemplate::SDLApp::draw() noexcept {}
