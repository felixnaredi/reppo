//===- Write.hpp --------------------------------------------------* C++ *-===//
//
//
//===----------------------------------------------------------------------===//

#ifndef REPPO_WRITE_HPP
#define REPPO_WRITE_HPP

#include <iomanip>
#include <iostream>
#include <tuple>
#include <utility>

namespace reppo {

#define fileprivate reppo_Write_fileprivate
namespace fileprivate {

template <class Stream> constexpr void write(Stream& stream) {}

template <class Stream, class T, class... Types>
constexpr void write(Stream& stream, const T& head, const Types&... tail) {
  stream << head;
  write(stream, tail...);
}

template <class T, class Char> struct Fill {
  const T value;
  const std::size_t length;
  const Char filler;

  constexpr Fill(T value, std::size_t length, Char filler)
      : value(value), length(length), filler(filler) {}
};

template <class Char, class T>
std::basic_ostream<Char>& operator<<(std::basic_ostream<Char>& stream,
                                     const Fill<T, Char>& fill) {
  return stream << std::setw(fill.length) << std::setfill(fill.filler)
                << fill.value;
}

} // namespace fileprivate

template <class Stream, class... Types>
constexpr void write(Stream& stream, const Types&... args) {
  fileprivate::write(stream, args...);
}

template <class T, class Char>
constexpr auto fill(T value, std::size_t length, Char c) {
  return fileprivate::Fill(value, length, c);
}

#undef fileprivate
} // namespace reppo

#endif // REPPO_WRITE_HPP
