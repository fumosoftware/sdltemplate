#ifndef SDLTEMPLATE_APP_APP_H_
#define SDLTEMPLATE_APP_APP_H_

#include <SDL3/SDL.h>
#include <stdexcept>
#include <variant>
#include <math/time.h>

namespace sdltemplate {
/** Container for running an SDL Application */
class SDLApp {
  /** Represents logic for the Title Screen state of the application */
  class TitleState {
  public:
    /** Prcesses SDL_Event and potentially modifies the state of the SDLApp.
     *
     * \param &event A const reference to the current SDL_Event being processed.
     * \param &app A reference to the containing SDLApp itself.
     */
    void process_event(SDL_Event const &event, SDLApp &app) noexcept;

    /** Update logic for the Title State. */
    void update() noexcept;

    /** Draws the Title State to the screen.
     *
     * \param *renderer A pointer to the SDLApp's renderer.
     */
    void draw(SDL_Renderer *renderer) noexcept;
  };

  /** Represents logic for the Game Screen state of the application */
  class GameState {
  public:
    /** Processes SDL_Event and potentially modifies the state of the SDLApp.
     *
     * \param &event A const reference to the current SDL_Event being processed.
     * \param &app A reference to the containing SDLApp itself.
     */
    void process_event(SDL_Event const &event, SDLApp &app) noexcept;

    /** Update logic for the Game State. */
    void update() noexcept;

    /** Draws the Game State to the screen.
     *
     * \param *renderer A pointer to the SDLApp's renderer.
     */
    void draw(SDL_Renderer *renderer) noexcept;
  };

  /** Represents logic for the Game Over Screen state of the application */
  class GameOverState {
  public:
    /** Processes SDL_Event and potentially modifies the state of the SDLApp.
     *
     * \param &event A const reference to the current SDL_Event being processed.
     * \param &app A reference to the containing SDLApp itself.
     */
    void process_event(SDL_Event const &event, SDLApp &app) noexcept;

    /** Update logic for the Game Over State. */
    void update() noexcept;

    /** Draws the Game Over State to the screen.
     *
     * \param *renderer A pointer to the SDLApp's renderer.
     */
    void draw(SDL_Renderer *renderer) noexcept;
  };

  /** Safe union type of all valid states of the SDLApp. */
  using State = std::variant<TitleState, GameState, GameOverState>;

public:
  /** Default Constructor
   *
   *  Attempts to initialize SDL3, create an SDL_Window and SDL_Renderer.
   *  If initialization of SDL3 fails, throws an SDLInitializeError.
   *  If creating an SDL_Window fails, throws an SDLWindowCreationError.
   *  If creating an SDL_Renderer fails, throws an SDLRendererCreationError.
   *
   *  If the constructor throws, SDL_DestroyRenderer, SDL_DestroyWindow, and
   * SDL_Quit will be called.
   */
  SDLApp();

  /** Destructor
   *  Calls SDL_DestroyRenderer, SDL_DestroyWindow, and SDL_Quit.
   */
  ~SDLApp() noexcept;

  /** Copy Constructor (deleted)
   *  SDLApp should not be able to be copied, assigned or moved.
   */
  SDLApp(SDLApp const &) = delete;

  /** Move Constructor (deleted)
   *  SDLApp should not be able to be copied, assigned or moved.
   */
  SDLApp(SDLApp &&) noexcept = delete;

  /** Copy Assignment (deleted)
   *  SDLApp should not be able to be copied, assigned or moved.
   */
  SDLApp &operator=(SDLApp const &) = delete;

  /** Move Assignment (deleted)
   *  SDLApp should not be able to be copied, assigned or moved.
   */
  SDLApp &operator=(SDLApp &&) noexcept = delete;

  /** Runs the application loop
   *
   *  Indefinately runs the application loop until a quit signal is received.
   */
  void run() noexcept;

private:
  /** Polls all queued SDL_Events. */
  void poll_events() noexcept;
  /** Runs the current states update logic. */
  void update() noexcept;
  /** Draws the current state. */
  void draw() noexcept;

  math::TimeAccumulator m_time_accumulator{};
  State m_current_state{TitleState{}};
  SDL_Renderer *m_renderer{nullptr};
  SDL_Window *m_window{nullptr};
  bool m_is_running{true};
};

/** Exception class for when SDL fails to initialize. */
class SDLInitializeError : public std::runtime_error {
public:
  SDLInitializeError() : std::runtime_error("Could not initialize SDL") {}
};

/** Exception class for when an SDL_Window cannot be created. */
class SDLWindowCreationError : public std::runtime_error {
public:
  SDLWindowCreationError() : std::runtime_error(SDL_GetError()) {}
};

/** Exception class for when an SDL_Renderer cannot be created. */
class SDLRendererCreationError : public std::runtime_error {
public:
  SDLRendererCreationError() : std::runtime_error(SDL_GetError()) {}
};

} // namespace sdltemplate

#endif
