#ifndef FUMOSOFT_LIB_CORE_ARKOGAME_COMPONENTS_CONTROLLERBODY_H_
#define FUMOSOFT_LIB_CORE_ARKOGAME_COMPONENTS_CONTROLLERBODY_H_

#include <math/physics/collider.h>

namespace fumo::core::components {

struct ControllerBody {
//  fumo::math::physics::Collider collider;
  float x{0.f};
  float y{0.f};
  float dir{1.f};
};
}

#endif

