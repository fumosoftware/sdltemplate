#ifndef APP_SDLAPP_H_
#define APP_SDLAPP_H_

#include "config.h"
#include <SDL3/SDL.h>
#include <spdlog/fmt/fmt.h>
#include <toml++/toml.h>
#include "screens.h"

class SDLApp final {
public:
  SDLApp();

  ~SDLApp();

  SDLApp(SDLApp const &) = delete;
  SDLApp(SDLApp &&) noexcept = delete;
  SDLApp &operator=(SDLApp const &) = delete;
  SDLApp &operator=(SDLApp &&) noexcept = delete;
  int run() noexcept;

private:
  void process_events() noexcept;
  void update() noexcept;
  void draw() noexcept;

  toml::table config_{load_or_create_config()};
  bool is_running_{true};
  SDL_Window *window_{nullptr};
  SDL_Renderer *renderer_{nullptr};
  Screens screens_{};
};

class SDLException : public std::runtime_error {
public:
  explicit SDLException(std::string_view message,
                        std::string_view reason) noexcept
      : std::runtime_error(message.data()),
        message_{fmt::format("EXCEPTION: {}\nREASON: {}", message.data(),
                             reason.data())} {}
  char const *what() const noexcept override { return message_.c_str(); }

private:
  std::string message_{};
};

#endif
