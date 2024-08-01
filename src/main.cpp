#include <core/sdlapp/sdlapp.h>

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) try {
  fumo::core::SDLApp{}.run();
} catch (fumo::core::SDLInitializeError const &error) {
  return 1;
} catch (fumo::core::SDLWindowCreationError const &error) {
  return 2;
} catch (fumo::core::SDLRendererCreationError const &error) {
  return 3;
}
