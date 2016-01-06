#include <map>
#include <tuple>
#include "Solution.hpp"
#include "io.hpp"

using Pos = std::tuple <int, int>;

Pos& apply (Pos& p, char c) {
  switch (c) {
    case '<': --std::get<1> (p); break;
    case '>': ++std::get<1> (p); break;
    case 'v': --std::get<0> (p); break;
    case '^': ++std::get<0> (p); break;
  }
  return p;
}

template <> void solve <Day03> (bool part2, std::istream & ifs) {
  std::map <Pos, int> p;
  Pos p1 { 0, 0 }, p2 { 0, 0 };
  bool santa { true };
  for (char c : io::as_string (ifs))
    ++p [apply (((santa ^= part2) ? p1 : p2), c)];
  std::cout << p.size() << std::endl;
}
