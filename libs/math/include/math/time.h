#ifndef SDLTEMPLATE_MATH_TIME_H_
#define SDLTEMPLATE_MATH_TIME_H_
#include <chrono>
#include <ratio>

namespace math {
using Duration = std::chrono::duration<float, std::milli>;
using TimePoint = std::chrono::time_point<std::chrono::high_resolution_clock>;

class TimeAccumulator {
public:
  Duration accumulate() noexcept;
  Duration consume(Duration const &ms) noexcept;
  Duration get_total_time() const noexcept { return m_total_accumulated_time; }
  void reset() noexcept { m_total_accumulated_time = std::chrono::milliseconds{0}; }

private:
  TimePoint m_last_tick{std::chrono::high_resolution_clock::now()};
  Duration m_accumulated_time{std::chrono::seconds{0}};
  Duration m_total_accumulated_time{std::chrono::seconds{0}};
};
} // namespace math
#endif
