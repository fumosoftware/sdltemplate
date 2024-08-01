#ifndef FUMOSOFT_LIB_MATH_PHYSICS_COLLIDER_H_
#define FUMOSOFT_LIB_MATH_PHYSICS_COLLIDER_H_

#include <optional>
#include <math/shapes/rectangle.h>

namespace fumo::math::physics {

class Collider {
public:
  struct CollisionInfo {
    shapes::Rectangle collision_rect{};
  };

  Collider(float pos_x, float pos_y, float w, float h) noexcept;
  Collider(float pos_x, float pos_y, float offset_x, float offset_y, float w, float h) noexcept;
  explicit Collider(shapes::Rectangle const& collision_box) noexcept;

  std::optional<CollisionInfo> does_collide(Collider const& other) noexcept;

private:
  shapes::Rectangle m_collision_box{};
  float m_pos_x{0.f};
  float m_pos_y{0.f};
};
} // namespace fumo::math::physics
#endif
