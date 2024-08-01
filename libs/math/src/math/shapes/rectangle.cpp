#include <math/shapes/rectangle.h>

using namespace fumo::math;
using namespace fumo::math::shapes;

bool aabb_sat(Rectangle const& rhs, Rectangle const& lhs) {

  if(rhs.x + rhs.w < lhs.x || rhs.x > lhs.x + lhs.w) return false;
  if(rhs.y + rhs.h < lhs.y || rhs.y > lhs.y + lhs.h) return false;
  return true;
}

std::optional<Rectangle> intersects(Rectangle const& rhs, Rectangle const& lhs) noexcept {
  if(!aabb_sat(rhs, lhs)) return {};

  return Rectangle{rhs.x - lhs.x, rhs.y - lhs.y, rhs.w - lhs.w, rhs.h - lhs.h};
}
