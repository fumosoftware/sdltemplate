#include <SDL3/SDL_events.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <chrono>
#include <core/arkogame/components/physicsbody.h>
#include <core/sdlapp/sdlapp.h>
#include <math/shapes/rectangle.h>

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

void fumo::core::SDLApp::TitleState::update(
    [[maybe_unused]] time::Duration dt,
    [[maybe_unused]] entt::registry &registry) noexcept {
  auto physicsbodies = registry.view<fumo::core::components::PhysicsBody>();

  // Move
  for (auto &&[_, body] : physicsbodies.each()) {
    body.x += 0.1f * dt.count() * body.dir;
  }

  // Collision Check
  for (auto &&[e1, body] : physicsbodies.each()) {
    for (auto &&[e2, body2] : physicsbodies.each()) {
      if (e1 == e2)
        continue;

      math::shapes::Rectangle f1{body.x, body.y, 10.f, 10.f};
      math::shapes::Rectangle f2{body2.x, body2.y, 10.f, 10.f};

      if (auto const maybe = fumo::math::intersects(f1, f2);
          maybe.has_value()) {
        std::cout << "Collision!\n"
                  << body.x << ", " << body.x + 10.f << "\n"
                  << body2.x << ", " << body2.x + 10.f << "\n";
        body.x += maybe->w;
        body2.x -= maybe->w;
        body.dir = -body.dir;
        body2.dir = -body2.dir;
      }
    }
  }

  // Bounds check
  for (auto &&[_, body] : physicsbodies.each()) {
    if (body.x < 0.f) {
      body.x = 0.f;
      body.dir = -body.dir;
    }
    if ((body.x + 10.f) > 400.f) {
      body.x = 300.f;
      body.dir = -body.dir;
    }
  }
}

void fumo::core::SDLApp::TitleState::draw(
    SDL_Renderer *renderer, entt::registry const &registry) noexcept {
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 200);
  auto const bodies = registry.view<fumo::core::components::PhysicsBody>();
  for (auto &&[_, body] : bodies.each()) {
    SDL_FRect frect{body.x, body.y, 10.f, 10.f};
    SDL_RenderFillRect(renderer, &frect);
    SDL_SetRenderDrawColor(renderer, 0, 200, 0, 200);
  }
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200);
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

void fumo::core::SDLApp::GameState::update(
    [[maybe_unused]] time::Duration dt,
    [[maybe_unused]] entt::registry &registry) noexcept {
  // std::cout << "Game State\n";
}

void fumo::core::SDLApp::GameState::draw(
    SDL_Renderer *renderer,
    [[maybe_unused]] entt::registry const &registry) noexcept {
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

void fumo::core::SDLApp::GameOverState::update(
    [[maybe_unused]] time::Duration dt,
    [[maybe_unused]] entt::registry &registry) noexcept {
  // std::cout << "Game Over State\n";
}

void fumo::core::SDLApp::GameOverState::draw(
    SDL_Renderer *renderer,
    [[maybe_unused]] entt::registry const &registry) noexcept {
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

  auto e1 = m_registry.create();
  m_registry.emplace<fumo::core::components::PhysicsBody>(e1, 30.f, 30.f, 1.f);
  auto e2 = m_registry.create();
  m_registry.emplace<fumo::core::components::PhysicsBody>(e2, 300.f, 30.f,
                                                          -1.f);
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
  std::visit(
      [this](auto &&state) {
        auto accumulated = m_time_accumulator.accumulate();
        while (accumulated >= fumo::core::time::Duration{0.10}) {
          state.update(fumo::core::time::Duration{0.10}, m_registry);
          accumulated =
              m_time_accumulator.consume(fumo::core::time::Duration{0.10});
        }
      },
      m_current_state);
}

void fumo::core::SDLApp::draw() noexcept {
  SDL_RenderClear(m_renderer);
  std::visit([this](auto &&state) { state.draw(m_renderer, m_registry); },
             m_current_state);
  SDL_RenderPresent(m_renderer);
}
