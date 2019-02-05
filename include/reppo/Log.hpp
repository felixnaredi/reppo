//===- Log.hpp ----------------------------------------------------* C++ *-===//
//
//
//===----------------------------------------------------------------------===//

#ifndef REPPO_LOG_HPP
#define REPPO_LOG_HPP

#include "reppo/Write.hpp"
#include <array>
#include <chrono>
#include <ctime>

namespace reppo {

#define fileprivate Log_hpp_fileprivate
namespace fileprivate {

class Now {
  using Clock = std::chrono::system_clock;

  const Clock::time_point time;

public:
  Now() : time(Clock::now()) {}

  operator std::time_t() const { return Clock::to_time_t(time); }

  auto milliDelta() const {
    using namespace std::chrono;
    return duration_cast<milliseconds>(time - (floor<seconds>(time)));
  }
};

template <class Char>
std::basic_ostream<Char>& operator<<(std::basic_ostream<Char>& stream,
                                     const Now& now) {
  using namespace std::chrono;
  std::time_t time(now);
  std::array<char, 64> buffer;

  std::strftime(
      buffer.data(), buffer.size(), "%F %T. %z", std::localtime(&time));

  // [0, 25]  : "2019-02-05 20:20:28. +0100"
  // [0, 19]  : "2019-02-05 20:20:28."
  // [20, 25] : " +0100"
  write(stream,
        std::string_view(buffer.data(), 20),
        fill(now.milliDelta().count(), 3, '0'),
        std::string_view(buffer.data()).substr(20));
  return stream;
}

} // namespace fileprivate

void logError(const std::string_view& message) {
  write(std::cout, '[', fileprivate::Now(), ']', " Error - ", message, '\n');
}

} // namespace reppo

#undef fileprivate
#endif // REPPO_LOG_HPP