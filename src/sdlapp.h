#ifndef APP_SDLAPP_H_
#define APP_SDLAPP_H_

#include <SDL3/SDL.h>
#include <spdlog/fmt/fmt.h>
#include <toml++/toml.h>

class SDLApp final {
public:
  SDLApp();
  SDLApp(SDLApp const&) = delete;
  SDLApp(SDLApp&&) noexcept = delete;
  SDLApp& operator=(SDLApp const&) = delete;
  SDLApp& operator=(SDLApp&&) noexcept = delete;
  ~SDLApp();

  int run() noexcept;
private:
  void process_events() noexcept;
  void draw() noexcept;

  bool is_running{true};
  SDL_Window* window_{nullptr};
  SDL_Renderer* renderer_{nullptr};
  toml::table config_{};
};

class SDLException : public std::runtime_error {
public:
  explicit SDLException(std::string_view message, std::string_view reason) noexcept
      : std::runtime_error(message.data()),
        message_{fmt::format("EXCEPTION: {}\nREASON: {}", message.data(),
                             reason.data())} {}

  char const *what() const noexcept override { return message_.c_str(); }

private:
  std::string message_{};
};

#endif
