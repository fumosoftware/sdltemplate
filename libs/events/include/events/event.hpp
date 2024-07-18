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

} // namespace sdltemplate::events

namespace sdltemplate {
  using Event = std::variant<std::monostate, events::KeyPressEvent, events::KeyReleaseEvent, events::QuitEvent>;
}

#endif
