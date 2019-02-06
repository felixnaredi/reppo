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
#include <optional>

namespace reppo {

#define fileprivate reppo_Log_fileprivate
namespace fileprivate {

class TimeStamp {
  using Clock = std::chrono::system_clock;

  const Clock::time_point time;
  constexpr TimeStamp(const Clock::time_point& time) : time(time) {}

public:
  static TimeStamp now() { return TimeStamp(Clock::now()); }

  operator std::time_t() const { return Clock::to_time_t(time); }

  constexpr auto milliDelta() const {
    using namespace std::chrono;
    return duration_cast<milliseconds>(time - (floor<seconds>(time)));
  }
};

template <class Char>
std::basic_ostream<Char>& operator<<(std::basic_ostream<Char>& stream,
                                     const TimeStamp& timeStamp) {
  std::time_t time(timeStamp);
  std::array<char, 64> buffer;

  std::strftime(
      buffer.data(), buffer.size(), "%F %T. %z", std::localtime(&time));

  // Range      String
  // ----------------------------------------------------------
  // [0, 25]  : "2019-02-05 20:20:28. +0100"
  // [0, 19]  : "2019-02-05 20:20:28."
  // [20, 25] : " +0100"
  write(stream,
        std::string_view(buffer.data(), 20),
        // The milliseconds are inserted in the middle of the date string to
        // prevent an extra call to 'strftime' and also to keep the localtime as
        // a one call rvalue.
        fill(timeStamp.milliDelta().count(), 3, '0'),
        std::string_view(buffer.data()).substr(20));
  return stream;
}

template <class Stream>
void log(Stream& stream,
         const std::optional<std::string_view>& prefix,
         const std::string_view& message) {
  write(stream, '[', TimeStamp::now(), ']', ' ');
  if (prefix)
    write(stream, *prefix, " - ");
  write(stream, message, '\n');
}

} // namespace fileprivate

void log(const std::string_view& message) {
  fileprivate::log(std::cout, {}, message);
}

void logError(const std::string_view& message) {
  fileprivate::log(std::cout, "Error", message);
}

void logWarning(const std::string_view& message) {
  fileprivate::log(std::cout, "Warning", message);
}

} // namespace reppo

#undef fileprivate
#endif // REPPO_LOG_HPP