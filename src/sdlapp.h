#ifndef APP_SDLAPP_H_
#define APP_SDLAPP_H_

#include "config.h"
#include "arkogame.h"
#include <SDL3/SDL.h>
#include <entt/entity/fwd.hpp>
#include <spdlog/fmt/fmt.h>
#include <toml++/toml.h>

/**
 * \class SDLApp SDLApp.h "SDLApp.h"
 * \brief Encapsulates the main entry point for the application.
 *
 * Encapsulates the main entry point for the application, and is
 * responsible for managing the lifetime of SDL.
 *
 * Due to the inner working of SDL, SDLApp cannot be copied or moved.
 */
class SDLApp final {
public:
  /**< Default constructor */
  /**
   * Attempts to initialze SDL, as well as
   * create an SDL_Window and SDL_Renderer.
   *
   * If initialization fails, or either an SDL_Window or
   * an SDL_Renderer cannot be created,
   * then the constructor will throw an SDLException.
   *
   * Reads in config data from ./data/config.toml (or creates it if that file
   * does not exist). The properties of the SDL_Window are set by the
   * values of the config.
   */
  SDLApp();

  /**< Destructor */
  /**
   * Destroys both the SDL_Renderer and SDL_Window(in that order),
   * then de-initializes SDL.
   */
  ~SDLApp();

  /**< Copy constructor */
  /**
   * Deleted due to the fact that the destructor de-initializes SDL,
   * which would otherwise cause issues with the surviving instance.
   */
  SDLApp(SDLApp const &) = delete;

  /**< Move constructor */
  /**
   * Deleted due to the fact that the destructor de-initializes SDL,
   * which would otherwise cause issues with the surviving instance.
   */
  SDLApp(SDLApp &&) noexcept = delete;

  /**< Copy assignment */
  /**
   * Deleted due to the fact that the destructor de-initializes SDL,
   * which would otherwise cause issues with the surviving instance.
   */
  SDLApp &operator=(SDLApp const &) = delete;

  /**< Move assignment */
  /**
   * Deleted due to the fact that the destructor de-initializes SDL,
   * which would otherwise cause issues with the surviving instance.
   */
  SDLApp &operator=(SDLApp &&) noexcept = delete;

  /**< Runs the main application loop */
  /**
   * \return 0 on success, or 1 upon encountering an unrecoverable error.
   */
  int run() noexcept;

private:
  /**< Processes queued SDL_Events*/
  /**
   * Attempts to handle all SDL_Events that have been queued up.
   * If SDLApp cannot handle the SDL_Event, then it is
   * handed to the current Screen for processing.
   */
  void process_events() noexcept;

  /**< Updates the current state of the application. */
  void update() noexcept;

  /**< Draws the current state of the application. */
  void draw() noexcept;

  toml::table config_{load_or_create_config()};
  bool is_running_{true};
  SDL_Window *window_{nullptr};
  SDL_Renderer *renderer_{nullptr};

  ArkoGame game_{};
};

/**
 * \class SDLException SDLApp.h "SDLApp.h"
 * \brief An exception thrown if an unrecoverable error is encountered with SDL
 *
 * Thrown when SDLApp cannot intialize SDL, or either an SDL_Window or an
 * SDL_Renderer cannot be created.
 */
class SDLException : public std::runtime_error {
public:
  /**< Constructor */
  /**
   * Formats the error message and reason message into a descriptive message
   * to be displayed.
   *
   * \parama message An error message to display
   * \param reason A detailed reason why the exception had to be thrown
   */
  explicit SDLException(std::string_view message,
                        std::string_view reason) noexcept
      : std::runtime_error(message.data()),
        message_{fmt::format("EXCEPTION: {}\nREASON: {}", message.data(),
                             reason.data())} {}

  /**< Gets the descriptive error message */
  char const *what() const noexcept override { return message_.c_str(); }

private:
  std::string message_{};
};

#endif
