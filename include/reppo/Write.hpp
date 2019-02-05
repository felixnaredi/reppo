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

#define fileprivate reppo_Write_hpp
namespace fileprivate {

template <class Stream, class Tuple, std::size_t... Is>
void write(Stream& stream, const Tuple& tuple, std::index_sequence<Is...>) {
  ((stream << std::get<Is>(tuple)), ...);
}

template <class Stream, class... Types>
void write(Stream& stream, const std::tuple<const Types&...>& tuple) {
  using Tuple = std::tuple<Types...>;
  write(
      stream, tuple, std::make_index_sequence<std::tuple_size<Tuple>::value>());
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
void write(Stream& stream, const Types&... args) {
  fileprivate::write(stream, std::forward_as_tuple(args...));
}

template <class T, class Char> auto fill(T value, std::size_t length, Char c) {
  return fileprivate::Fill(value, length, c);
}

#undef fileprivate
} // namespace reppo

#endif // REPPO_WRITE_HPP
