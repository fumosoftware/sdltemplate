#ifndef FUMOSOFT_LIB_CORE_ARKOGAME_COMPONENTS_PHYSICSBODY_H_
#define FUMOSOFT_LIB_CORE_ARKOGAME_COMPONENTS_PHYSICSBODY_H_

#include <math/physics/collider.h>

namespace fumo::core::components {

struct PhysicsBody {
  //fumo::math::physics::Collider collider;
  float x{0.f};
  float y{0.f};
  float dir{1.f};
};
}

#endif

