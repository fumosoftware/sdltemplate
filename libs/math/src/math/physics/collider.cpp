#include <math/physics/collider.h>

using namespace fumo::math::physics;
using namespace fumo::math::shapes;

Collider::Collider(float pos_x, float pos_y, float w, float h) noexcept
    : m_collision_box{0.f, 0.f, w, h}, m_pos_x{pos_x}, m_pos_y{pos_y} {}

Collider::Collider(float pos_x, float pos_y, float offset_x, float offset_y,
                   float w, float h) noexcept
    : m_collision_box{offset_x, offset_y, w, h}, m_pos_x{pos_x},
      m_pos_y{pos_y} {}

Collider::Collider(Rectangle const &collision_box) noexcept
    : m_collision_box{collision_box} {}

std::optional<Collider::CollisionInfo>
Collider::does_collide(Collider const &other) noexcept {

  Rectangle this_rect{.x = m_collision_box.x + m_pos_x,
                      .y = m_collision_box.y + m_pos_y,
                      .w = m_collision_box.w,
                      .h = m_collision_box.h};

  Rectangle other_rect{.x = other.m_collision_box.x + other.m_pos_x,
                       .y = other.m_collision_box.y + other.m_pos_y,
                       .w = other.m_collision_box.w,
                       .h = other.m_collision_box.h};

  if(auto const maybe_collision_rect = intersects(this_rect, other_rect); maybe_collision_rect.has_value()) {
    return CollisionInfo{*maybe_collision_rect};
  }

  return {};
}
