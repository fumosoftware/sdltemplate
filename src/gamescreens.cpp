#include "gamescreens.h"
#include <iostream>

void TitleScreen::process_event(SDL_Event const &event,
                                GameScreens &screen) noexcept {

  if (event.type == SDL_EVENT_KEY_DOWN) {
    switch (event.key.keysym.scancode) {
    case SDL_SCANCODE_G:
      screen.change_screen(GameScreen{});
      break;
    case SDL_SCANCODE_S:
      screen.change_screen(SettingsScreen{});
      break;
    default:
      break;
    }
  }
}

void TitleScreen::update([[maybe_unused]] float dt) noexcept {
  std::cout << "Title Screen Update\n";
}

void TitleScreen::draw(SDL_Renderer *renderer) const noexcept {
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 200);
}

void GameScreen::process_event(SDL_Event const &event,
                               GameScreens &screen) noexcept {

  if (event.type == SDL_EVENT_KEY_DOWN) {
    switch (event.key.keysym.scancode) {
    case SDL_SCANCODE_T:
      screen.change_screen(TitleScreen{});
      break;
    case SDL_SCANCODE_D:
      screen.change_screen(GameOverScreen{});
      break;
    default:
      break;
    }
  }
}

void GameScreen::update([[maybe_unused]] float dt) noexcept {
  std::cout << "Game Screen Update\n";
}

void GameScreen::draw(SDL_Renderer *renderer) const noexcept {
  SDL_SetRenderDrawColor(renderer, 255, 0, 255, 50);
}

void SettingsScreen::process_event(SDL_Event const &event,
                                   GameScreens &screen) noexcept {

  if (event.type == SDL_EVENT_KEY_DOWN) {
    switch (event.key.keysym.scancode) {
    case SDL_SCANCODE_T:
      screen.change_screen(TitleScreen{});
      break;
    default:
      break;
    }
  }
}

void SettingsScreen::update([[maybe_unused]] float dt) noexcept {
  std::cout << "Settings Screen Update\n";
}

void SettingsScreen::draw(SDL_Renderer *renderer) const noexcept {
  SDL_SetRenderDrawColor(renderer, 100, 255, 0, 100);
}

void GameOverScreen::process_event(SDL_Event const &event,
                                   GameScreens &screen) noexcept {

  if (event.type == SDL_EVENT_KEY_DOWN) {
    switch (event.key.keysym.scancode) {
    case SDL_SCANCODE_T:
      screen.change_screen(TitleScreen{});
      break;
    default:
      break;
    }
  }
}

void GameOverScreen::update([[maybe_unused]] float dt) noexcept {
  std::cout << "GameOver Screen Update\n";
}

void GameOverScreen::draw(SDL_Renderer *renderer) const noexcept {
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 200);
}

void GameScreens::process_event(SDL_Event const &event) noexcept {
  std::visit(
      [event, this](auto &&screen) { screen.process_event(event, *this); },
      current_screen_);
}

void GameScreens::update([[maybe_unused]] float dt) noexcept {
  std::visit([dt](auto &&screen) { screen.update(dt); }, current_screen_);
}

void GameScreens::draw(SDL_Renderer *renderer) const noexcept {
  std::visit([renderer](auto &&screen) { screen.draw(renderer); },
             current_screen_);
}
