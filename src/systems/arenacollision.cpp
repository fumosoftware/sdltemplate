#include "arenacollision.h"

#include "../components/position.h"
#include "../components/velocity.h"
#include "../components/collider.h"

void check_arena_collision(entt::registry& world, float width, float height) {
  auto view = world.view<Position, Velocity, Collider>();
  for(auto&& [_, pos, vel, hb] : view.each()) {

    if(pos.x < 0 || pos.x + hb.w > width) {
      vel.x = -vel.x;
    }

    if(pos.x + hb.w > width) {
      pos.x = width - hb.w;
    } else if(pos.x < 0) {
      pos.x = 0;
    }

    if(pos.y < 0 || pos.y + hb.h > height) {
      vel.y = -vel.y;
    }

    if(pos.y + hb.h > height) {
      pos.y = height - hb.h;
    } else if(pos.y < 0) {
      pos.y = 0;
    }
  }
}

