#include <SDL3/SDL_events.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <chrono>
#include <core/sdlapp/sdlapp.h>

#include <iostream>

/********************************
 * Title State implementation
 ********************************/

void fumo::core::SDLApp::TitleState::process_event(SDL_Event const &event,
                                                    SDLApp &app) noexcept {
  switch (event.type) {
  case SDL_EVENT_KEY_DOWN: {
    if (event.key.keysym.scancode == SDL_SCANCODE_G)
      app.m_current_state = GameState{};
    else if (event.key.keysym.scancode == SDL_SCANCODE_Q)
      app.m_is_running = false;
  } break;
  default:
    break;
  }
}

void fumo::core::SDLApp::TitleState::update() noexcept {
  //std::cout << "Title State\n";
}

void fumo::core::SDLApp::TitleState::draw(SDL_Renderer *renderer) noexcept {
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 200);
}

/********************************
 * Game State implementation
 ********************************/

void fumo::core::SDLApp::GameState::process_event(SDL_Event const &event,
                                                   SDLApp &app) noexcept {
  switch (event.type) {
  case SDL_EVENT_KEY_DOWN: {
    if (event.key.keysym.scancode == SDL_SCANCODE_O)
      app.m_current_state = GameOverState{};
    else if (event.key.keysym.scancode == SDL_SCANCODE_T)
      app.m_current_state = TitleState{};
    else if (event.key.keysym.scancode == SDL_SCANCODE_Q)
      app.m_is_running = false;
  } break;
  default:
    break;
  }
}

void fumo::core::SDLApp::GameState::update() noexcept {
  //std::cout << "Game State\n";
}

void fumo::core::SDLApp::GameState::draw(SDL_Renderer *renderer) noexcept {
  SDL_SetRenderDrawColor(renderer, 0, 0, 255, 200);
}

/********************************
 * Game Over State implementation
 ********************************/

void fumo::core::SDLApp::GameOverState::process_event(SDL_Event const &event,
                                                       SDLApp &app) noexcept {
  switch (event.type) {
  case SDL_EVENT_KEY_DOWN: {
    if (event.key.keysym.scancode == SDL_SCANCODE_T)
      app.m_current_state = TitleState{};
    else if (event.key.keysym.scancode == SDL_SCANCODE_Q)
      app.m_is_running = false;
  } break;
  default:
    break;
  }
}

void fumo::core::SDLApp::GameOverState::update() noexcept {
  //std::cout << "Game Over State\n";
}

void fumo::core::SDLApp::GameOverState::draw(SDL_Renderer *renderer) noexcept {
  SDL_SetRenderDrawColor(renderer, 255, 255, 0, 200);
}

/********************************
 * SDLApp Implementation
 ********************************/
fumo::core::SDLApp::SDLApp() {
  try {
    auto const did_init = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
    if (did_init != 0)
      throw fumo::core::SDLInitializeError{};

    m_window = SDL_CreateWindow("Title", 400, 200, 0);
    if (!m_window)
      throw fumo::core::SDLWindowCreationError{};

    m_renderer = SDL_CreateRenderer(m_window, nullptr);
    if (!m_renderer) {
      throw fumo::core::SDLRendererCreationError{};
    }

    SDL_SetRenderVSync(m_renderer, 1);
  } catch (...) {
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
  }
}

fumo::core::SDLApp::~SDLApp() noexcept {
  SDL_DestroyRenderer(m_renderer);
  SDL_DestroyWindow(m_window);
  SDL_Quit();
}

void fumo::core::SDLApp::run() noexcept {
  while (m_is_running) {
    poll_events();
    update();
    draw();
  }
}

void fumo::core::SDLApp::poll_events() noexcept {
  SDL_Event event{};
  while (SDL_PollEvent(&event)) {
    std::visit(
        [&event, this](auto &&state) { state.process_event(event, *this); },
        m_current_state);
  }
}

using namespace std::chrono_literals;
void fumo::core::SDLApp::update() noexcept {
  static int frame_count = 0;
  frame_count++;
  std::visit([this](auto &&state) { 
    auto accumulated  = m_time_accumulator.accumulate();
    while(accumulated >= fumo::core::time::Duration{0.10}) {
      state.update();
      accumulated = m_time_accumulator.consume(fumo::core::time::Duration{0.10});
    }
  }, m_current_state);

  if(m_time_accumulator.get_total_time() >= 1s) {
    std::cout << "Frames: " << frame_count << "\n";
    frame_count = 0;
    m_time_accumulator.reset();
  }
}

void fumo::core::SDLApp::draw() noexcept {
  SDL_RenderClear(m_renderer);
  std::visit([this](auto &&state) { state.draw(m_renderer); }, m_current_state);
  SDL_RenderPresent(m_renderer);
}
