//===- main.cc ----------------------------------------------------* C++ *-===//
//
//
//===----------------------------------------------------------------------===//

#include "reppo/Log.hpp"
#include <fstream>

namespace reppo {
// Fileprivate functions.

} // namespace reppo

using namespace reppo;

int main(int argc, char** argv) {
  write(std::cout, "Int: ", 11, 'd', 1.2, '\n');

  logWarning("IO operation that might fail");
  if (auto stream = std::ofstream("nope/temp.txt"))
    write(stream, "Hello World! - ", 1337, '\n');
  else
    logError("Failed to open file");

  log("Program finished");
  return 0;
}