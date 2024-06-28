#ifndef APP_SDLAPP_H_
#define APP_SDLAPP_H_

#include "config.h"
#include <SDL3/SDL.h>
#include <spdlog/fmt/fmt.h>
#include <toml++/toml.h>
#include "screens.h"

/**
 * Encapsulates the application loop and logic.
 * Cannot be inherited from.
 * Cannot be copied or moved, due to how the SDL library work.
 *
 * The constructor will attempt to load a config file from ./data/config.toml.
 * If the file does not exist, a default config will be written out and loaded.
 * If the config does not contain some field, default values will be used.
 *
 * The constructor will throw an SDL_Exception if it cannot initialze SDL,
 * or it cannot create an SDL_Window or SDL_Renderer.
 *
 * SDL_Window will be created using fields from the config.
 *
 * The destructor will destroy the renderer and window, and de-initialize SDL.
 */
class SDLApp final {
public:
  /**
   * Throws an SDLException if initialization fails.
   *  (SDL_Init fails, or SDL_Window/SDL_Renderer cannot be created.)
   *
   * Does the following in order:
   * 1) Load a config file, or create a default one if no config is found.
   * 2) Attempt to initialize SDL.
   * 3) Attempt to create an SDL_Window, using values from the config.
   * 4) Attempt to create an SDL_Renderer.
   */
  SDLApp();

  /**
   * Ensures that SDL is properly cleaned up.
   * Calls SDL_DestroyRenderer, SDL_DestroyWindow, and SDL_Quit (in that order)
   */
  ~SDLApp();

  /**
   * Because the destructor calls SDL_Quit,
   * the copy- and move-constructors/assignments
   * must be deleted, otherwise we can get into a weird state.
   * (Also why are you trying to copy/move this object around?)
   */
  SDLApp(SDLApp const &) = delete;
  SDLApp(SDLApp &&) noexcept = delete;
  SDLApp &operator=(SDLApp const &) = delete;
  SDLApp &operator=(SDLApp &&) noexcept = delete;

  /**
   * Runs the main application loop, in the following order:
   * 1) Accumulate time since last frame
   * 2) Process all queued events
   * 3) If enough time has accumulated:
   *    1) Loop main app code, subtracting a fixed delta time each iteration.
   *    2) After looping, interpolate the app state with the leftover time.
   * 4) Draw to the screen
   * \returns 0 on success, non-zero when a fatal error had occurred.
   */
  int run() noexcept;

private:
  /**
   * Attempts to handle all events queued since the last frame.
   * Forwards any unhandled events to the main app code.
   */
  void process_events() noexcept;

  /**
   *
   *
   */
  void update() noexcept;

  /**
   * Draws the current app state to the screen.
   */
  void draw() noexcept;

  toml::table config_{load_or_create_config()};
  bool is_running_{true};
  SDL_Window *window_{nullptr};
  SDL_Renderer *renderer_{nullptr};
  Screens screens_{};
  //Game game_{};
};

/**
 * Thrown when there is an issue with SDL, such as initialization issues.
 * Should only be used when there is no possible recovery, which is rare.
 */
class SDLException : public std::runtime_error {
public:
  /**
   * Constructor
   *
   * Creates a formatted message using the `message` and `reason` parameters.
   *
   * \param message An error message for the failure.
   * \param reason An error message on why the failure happened.
   */
  explicit SDLException(std::string_view message,
                        std::string_view reason) noexcept
      : std::runtime_error(message.data()),
        message_{fmt::format("EXCEPTION: {}\nREASON: {}", message.data(),
                             reason.data())} {}

  /**
   * Overrides std::runtime_error::what().
   *
   * \returns A formatted error message detailing why the exception occurred.
   */
  char const *what() const noexcept override { return message_.c_str(); }

private:
  std::string message_{};
};

#endif
