#include <core/time/time.h>

using namespace fumo::core::time;

Duration TimeAccumulator::accumulate() noexcept {
  auto const now = std::chrono::high_resolution_clock::now();
  auto const diff = std::chrono::duration_cast<Duration>(now - m_last_tick);
  m_last_tick = now;
  m_accumulated_time += diff;
  m_total_accumulated_time += diff;

  return m_accumulated_time;
}

Duration
TimeAccumulator::consume(Duration const& ms) noexcept {

  m_accumulated_time -= ms;
  return m_accumulated_time;
}
