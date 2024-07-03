#include "brickcollision.h"

#include "../components/collider.h"
#include "../components/position.h"
#include "../components/tags.h"
#include "../components/velocity.h"
#include <entt/entity/entity.hpp>

void check_brick_collisions(entt::registry &world) {
  auto balls = world.view<Position, Collider, Velocity, BallTag>();
  auto bricks = world.view<Position, Collider, BrickTag>();

  std::unordered_set<entt::entity> bricks_to_destroy{};
  for (auto &&[_, ball_pos, ball_collider, ball_vel] : balls.each()) {
    for (auto &&[brick, brick_pos, brick_collider] : bricks.each()) {

      if (ball_pos.x < brick_pos.x + brick_collider.w &&
          ball_pos.x + ball_collider.w > brick_pos.x &&
          ball_pos.y < brick_pos.y + brick_collider.h &&
          ball_pos.y + ball_collider.h > brick_pos.y) {
        ball_vel.x = -ball_vel.x;
        ball_vel.y = -ball_vel.y;

        bricks_to_destroy.insert(brick);
      }
    }
  }

  world.destroy(bricks_to_destroy.begin(), bricks_to_destroy.end());
}
