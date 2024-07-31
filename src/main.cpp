#include <sdlapp/sdlapp.h>

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) try {
  return sdltemplate::SDLApp{}.run();
} catch (sdltemplate::SDLInitializeError const &error) {
  return 1;
} catch (sdltemplate::SDLWindowCreationError const &error) {
  return 2;
} catch (sdltemplate::SDLRendererCreationError const &error) {
  return 3;
}
