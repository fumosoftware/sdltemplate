#include <math/time.h>

math::Duration math::TimeAccumulator::accumulate() noexcept {
  auto const now = std::chrono::high_resolution_clock::now();
  auto const diff = std::chrono::duration_cast<Duration>(now - m_last_tick);
  m_last_tick = now;
  m_accumulated_time += diff;
  m_total_accumulated_time += diff;

  return m_accumulated_time;
}

math::Duration
math::TimeAccumulator::consume(math::Duration const& ms) noexcept {

  m_accumulated_time -= ms;
  return m_accumulated_time;
}
