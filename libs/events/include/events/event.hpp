#ifndef SDLTEMPLATE_LIB_EVENTS_EVENT_H_
#define SDLTEMPLATE_LIB_EVENTS_EVENT_H_
#include <variant>
#include "keys.hpp"

namespace sdltemplate::events {

struct KeyPressEvent {
  Key key{Key::UNKNOWN};
  bool is_repeated{false};
};

struct KeyReleaseEvent {
  Key key{Key::UNKNOWN};
  bool is_repeated{false};
};

struct QuitEvent {};

using Event = std::variant<std::monostate, KeyPressEvent, KeyReleaseEvent, QuitEvent>;

} // namespace sdltemplate::events

#endif
