#ifndef SDLTEMPLATE_LIB_MATH_SHAPES_RECT_H_
#define SDLTEMPLATE_LIB_MATH_SHAPES_RECT_H_

namespace sdltemplate::math::shapes {
struct Rect {
  float x{0.f};
  float y{0.f};
  float w{0.f};
  float h{0.f};
};

// Separating Axis Theorem to test intersections
bool intersects(Rect const &rhs, Rect const &lhs) noexcept;
} // namespace sdltemplate::math::shapes

#endif
