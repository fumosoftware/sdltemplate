#include <SDL3/SDL_events.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <sdlapp/sdlapp.h>

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

void sdltemplate::SDLApp::run() noexcept {
  while (m_is_running) {
    poll_events();
    update_state();
    draw();
  }
}

void sdltemplate::SDLApp::poll_events() noexcept {
  SDL_Event event{};
  while (SDL_PollEvent(&event)) {
    std::visit(
        [&event, this](auto &&state) { state.process_event(event, *this); },
        m_current_state);
  }
}

void sdltemplate::SDLApp::update_state() noexcept {
  std::visit([](auto &&state) { state.update(); }, m_current_state);
}

void sdltemplate::SDLApp::draw() noexcept {
  SDL_RenderClear(m_renderer);
  SDL_RenderPresent(m_renderer);
}
