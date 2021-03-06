#include <algorithm>
#include <vector>
#include "Solution.hpp"
#include "io.hpp"

#define COMPARE_BY(X) [] (const auto & d1, const auto & d2) { return d1 . X < d2 . X; }

struct Reindeer {
  int speed { 0 }, go { 0 }, rest { 0 }, dist { 0 }, points { 0 };
  explicit Reindeer() {}
  Reindeer (int _s, int _g, int _r) : speed { _s }, go { _g }, rest { _r } { }
  void tick (int t) {
    if (t % (go + rest) < go) dist += speed;
  }
};

template <> void solve <Day14> (bool part2, std::istream & is, std::ostream & os) {
  const static std::regex PARSE { R"(\w+ can fly (\d+) km/s for (\d+) seconds, but then must rest for (\d+) seconds.)" };
  const int TIME { 2503 };
  std::vector <Reindeer> deer;
  for (auto && line : io::by <io::line> (is)) {
    std::smatch m { io::regex_parse (line, PARSE) };
    deer.emplace_back (std::stoi (m.str (1)), std::stoi (m.str (2)), std::stoi (m.str (3)));
  }
  for (int t { 0 }; t < TIME; ++t) {
    for (auto && d : deer)
      d.tick (t);
    if (part2) {
      std::vector <int> leaders;
      int lead { 0 };
      for (auto && d : deer) {
        if (d.dist > lead)
          leaders.clear(), lead = d.dist;
        if (d.dist == lead)
          leaders.push_back (&d - &deer[0]);
      }
      for (auto && name : leaders)
        ++deer[name].points;
    }
  }
  int winner { part2
      ? std::max_element (std::cbegin (deer), std::cend (deer), COMPARE_BY (points))->points
      : std::max_element (std::cbegin (deer), std::cend (deer), COMPARE_BY (dist))->dist
      };
  os << winner << std::endl;
}
