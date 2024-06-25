#include "sdlapp.h"
#include <iostream>

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) noexcept {


  try {
    return SDLApp{}.run();
  }
  catch(SDLException const& error) {
    std::cout << error.what() << "\n";
  }

  return 1;
}

    
    /*
    auto const current_frame_time = std::chrono::steady_clock::now();
    auto const frame_dt = (current_frame_time - previous_frame_time) > max_dt
                              ? max_dt
                              : (current_frame_time - previous_frame_time);
    previous_frame_time = current_frame_time;
    accumulator += frame_dt;

    while (accumulator >= fixed_dt) {
      old_ball = ball;
      ball.x = ball.x + (x_vel * fixed_dt).count();

      //Check collision against window borders
      if (ball.x + ball.w > window_width || ball.x - ball.w < -ball.w)
        x_vel *= -1.f;


      accumulator -= fixed_dt;
    }

    // integrate to accomidate for leftover time in the accumulator
    auto const alpha = accumulator / fixed_dt;
    std::lerp(ball.x, old_ball.x, alpha);
  return 0;
}
    */
