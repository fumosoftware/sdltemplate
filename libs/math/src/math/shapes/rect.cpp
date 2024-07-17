#include <math/shapes/rect.hpp>

using namespace sdltemplate::math::shapes;

bool intersects(Rect const& rhs, Rect const& lhs) noexcept {
  if(rhs.x > lhs.x + lhs.w || rhs.x + rhs.w < lhs.x) return false;
  if(rhs.y > lhs.y + lhs.h || rhs.y + rhs.h < lhs.y) return false;
  return true;
}
