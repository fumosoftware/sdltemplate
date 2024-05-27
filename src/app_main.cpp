#include <SDL.h>
#include "logging.h"

int app_main() {
  logging::log("This is a test.");
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
    return 1;
  }

  SDL_Window *const window = SDL_CreateWindow("sdlapp", 320, 180, 0);
  SDL_Renderer *const renderer =
      SDL_CreateRenderer(window, "window_renderer", -1);

  SDL_Event event{};
  bool is_running = true;

  while (is_running) {
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_EVENT_KEY_DOWN: {
        if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
          is_running = false;
          break;
        }
      }
      }
    }

    if (!is_running)
      break;

    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 100, 200, 255);
    SDL_RenderPresent(renderer);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
