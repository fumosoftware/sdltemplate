#ifndef FUMOSOFT_LIB_MATH_SHAPE_RECTANGLE_H_
#define FUMOSOFT_LIB_MATH_SHAPE_RECTANGLE_H_

#include <optional>

namespace fumo::math::shapes {

struct Rectangle {
  float x{0.f};
  float y{0.f};
  float w{0.f};
  float h{0.f};
};

} // namespace fumo::math::shapes

namespace fumo::math {

std::optional<shapes::Rectangle>
intersects(shapes::Rectangle const &rhs, shapes::Rectangle const &lhs) noexcept;

}
#endif
