#include <math/shapes/rectangle.h>


bool aabb_sat(fumo::math::shapes::Rectangle const& rhs, fumo::math::shapes::Rectangle const& lhs) {

  if(rhs.x + rhs.w < lhs.x || rhs.x > lhs.x + lhs.w) return false;
  if(rhs.y + rhs.h < lhs.y || rhs.y > lhs.y + lhs.h) return false;
  return true;
}

std::optional<fumo::math::shapes::Rectangle> fumo::math::intersects(fumo::math::shapes::Rectangle const& rhs, fumo::math::shapes::Rectangle const& lhs) noexcept {
  if(!aabb_sat(rhs, lhs)) return {};

  return fumo::math::shapes::Rectangle{rhs.x - lhs.x, rhs.y - lhs.y, (lhs.x + lhs.w) - rhs.x, (lhs.y + lhs.h) - rhs.y};
}
