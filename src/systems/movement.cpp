#include "movement.h"

#include "../components/position.h"
#include "../components/velocity.h"

void movement(entt::registry& world, float dt) {

  auto view = world.view<Position, Velocity>();
  for(auto&& [_, pos, vel] : view.each()) {
    pos.x += vel.x * dt;
    pos.y += vel.y * dt;
  }
}
