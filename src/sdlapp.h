#ifndef APP_SDLAPP_H_
#define APP_SDLAPP_H_

#include <SDL3/SDL.h>
#include <filesystem>
#include <variant>

/**
 * Represents the main logic of the application.
 *
 * Cannot be created implicitly, must first be created by a helper function.
 * \sa create
 * \sa create_from
 *
 * Upon initialization, an SDLApp instance will attempt to do the following:
 *  1) Initialize SDL3
 *  2) Create an SDL_Window
 *  3) Create an SDL_Renderer(from the previously created SDL_Window)
 *
 * If any of the above steps fail, the failure will be logged.
 */
class SDLApp final {
  static constexpr auto DEFAULT_WIDTH{380u};
  static constexpr auto DEFAULT_HEIGHT{120u};

public:
  enum struct Error {
    INITIALIZATION_FAILED,
    WINDOW_CREATION,
    RENDERER_CREATION
  };

  /**
   * Attempts to create an SDLApp object.
   * If the initialization of the SDLApp object fails, then an
   * SDLApp::Error value is created instead.
   * The SDLApp object is constructed with the following defaults:
   *  * window_width: 380u
   *  * window_height: 120u
   *
   * This method does not throw.
   *
   * \return An SDLApp object, or an SDLApp::Error value on initialization
   * error.
   *
   * \sa create_from
   */
  static std::variant<SDLApp, Error> create() noexcept;

  /**
   * Attempts to create an SDLApp object.
   * If the config toml file exists, then the object will be initialized
   *  with values read from the config.
   *
   * If the config is not found, or values are missing from the config,
   * then the appropriate default values will be used instead.
   * These config values are:
   *  * [window][width] -> the width of the window
   *  * [window][height] -> the height of the window
   *
   * If the initialization of the SDLApp object fails, then an
   * SDLApp::Error value is created instead.
   *
   * This method does not throw.
   *
   * \param path The relative path to the config toml file.
   *
   * \return An SDLApp object, or an SDLApp::Error value on initialization
   * error.
   *
   * \sa create
   */
  static std::variant<SDLApp, Error>
  create_from(std::filesystem::path const path) noexcept;

  /**
   * Destructor.
   * Runs SDL_Quit, and not much else.
   *
   */
  ~SDLApp() noexcept;

  /**
   * Deleted copy constructor.
   */
  SDLApp(SDLApp const&) = delete;

  /**
   * Move constructor.
   */
  SDLApp(SDLApp&& other) noexcept;

  /**
   * Deleted copy-assignment operator.
   */
  SDLApp& operator=(SDLApp const&) = delete;

  /**
   * Deleted move-assignment operator.
   */
  SDLApp& operator=(SDLApp&&) noexcept = delete;
  
  /**
   * Runs the application loop.
   * The loop runs the following (while is_running_ is true):
   *  1) Processes all queued SDL_Events
   *  2) Attempts to run game logic at a set fps. 
   *    (this may run multiple times in a single iteration)
   *  3) Draws to the screen
   *
   * This method does not throw.
   *
   * \return 0 after a successful run.
   */
  int run() noexcept;

private:
  /**
   * Default constructor.
   * Creates an SDLApp with the following values:
   *  * width: 380u
   *  * height: 120u
   *
   * This method does not throw.
   * \sa SDLApp(unsigned int width, unsigned int height)
   */
  SDLApp() noexcept;

  /**
   * Creates an SDLApp object with the provided width and height.
   * This method does not throw.
   *
   * \param width The desired width of the window.
   * \param height The desired height of the window.
   * \sa SDLApp
   */
  SDLApp(unsigned int const width, unsigned int const height) noexcept;

  /**
   * Processes incoming SDL_Events.
   * SDLApp first attempts to handle the incoming event.
   * If it does not handle the event, the event is then forwarded
   *  to the games logic.
   *
   *  This method does not throw.
   */
  void process_events() noexcept;

  /**
   * Draws to the window.
   * 
   * This method does not throw.
   */
  void draw() noexcept;

  // Do not use smart pointers for SDL_Window or SDL_Renderer.
  // This is because we call SDL_Quit in our destructor, which ends up 
  // causing some issues if it is called before we destroy SDL_Window or SDL_Renderer.
  SDL_Window* window_{};
  SDL_Renderer* renderer_{};
  bool is_running_{true};
};

#endif
