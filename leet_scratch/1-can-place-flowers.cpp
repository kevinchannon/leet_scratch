// leet_scratch.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <iostream>

#include <vector>
#include <algorithm>
#include <iterator>
#include <string>
#include <numeric>
#include <unordered_set>
#include <format>
#include <unordered_map>
#include <string_view>
#include <deque>
#include <vector>

namespace leet {
  template<typename Range_T>
  [[nodiscard]] bool any(const Range_T& r, const typename Range_T::value_type& val) noexcept {
    return std::any_of(r.begin(), r.end(), [&val](auto&& x) { return x == val;  });
  }
}

class Solution {
public:

  using flowerbed_t = std::vector<int>;

  bool canPlaceFlowers(const flowerbed_t& flowerbed, int n) {
    return can_place_flowers(flowerbed.begin(), flowerbed.end(), n);
  }

private:
  static constexpr auto UNOCCUPIED = 0;
  static constexpr auto OCCUPIED = 1;

  template<int STATE>
  [[nodiscard]] constexpr static bool is(int val) noexcept { return val == STATE; }

  [[nodiscard]] static bool can_place_flowers(flowerbed_t::const_iterator start, flowerbed_t::const_iterator end, int n) {
    if (n == 0) {
      return true;
    }

    if (not std::any_of(start, end, is<OCCUPIED>)) {
      switch (n) {
      case 1: return std::distance(start, end) > 0;
      default: return static_cast<unsigned long long>(std::distance(start, end)) >= 2 * static_cast<unsigned long long>(n) - 1;
      }
    }

    switch (std::distance(start, end)) {
    case 0:
    case 1:
    case 2: return false;
    case 3: return (*start == OCCUPIED) ^ (*std::prev(end) == OCCUPIED);
    default:;
    }

    auto available_positions = 0;

    if (std::all_of(start, std::next(start, 2), is<UNOCCUPIED>)) {
      ++available_positions;
      ++start;
    }

    while (available_positions < n && start <= std::prev(end)) {
      const auto next_available = find_next_position(start, end);
      if (next_available == end) {
        break;
      }

      ++available_positions;
      std::advance(start, 2);
    }

    if (is<UNOCCUPIED>(*std::reverse_iterator{ end }) and is<UNOCCUPIED>(*std::next(std::reverse_iterator{ end }))) {
      ++available_positions;
    }

    return available_positions >= n;
  }

  [[nodiscard]] static flowerbed_t::const_iterator find_next_position(flowerbed_t::const_iterator start, const flowerbed_t::const_iterator end) {
    for (auto pos = start; pos != end; ++pos) {
      const auto next_possible_begin = std::find(pos, end, UNOCCUPIED);
      if (next_possible_begin == end) {
        break;
      }

      const auto next_possible_end = std::find(next_possible_begin, end, OCCUPIED);
      if (std::distance(next_possible_begin, next_possible_end) >= 3) {
        return std::next(next_possible_begin);
      }
    }

    return end;
  }
};

// ZERO FLOWER PLACEMENT
TEST_CASE("Can place ZERO new flower in size 1, empty") { REQUIRE(Solution{}.canPlaceFlowers({ 0 }, 0)); }
TEST_CASE("Can place ZERO new flower in size 1, full") { REQUIRE(Solution{}.canPlaceFlowers({ 1 }, 0)); }
TEST_CASE("Can place ZERO new flower in size 2, full") { REQUIRE(Solution{}.canPlaceFlowers({ 1, 1 }, 0)); }
TEST_CASE("Can place ZERO new flower in size 3, full") { REQUIRE(Solution{}.canPlaceFlowers({ 1, 1, 1 }, 0)); }

// SINGLE FLOWER PLACEMENT
TEST_CASE("Can place ONE new flower in size 1, empty") { REQUIRE(Solution{}.canPlaceFlowers({ 0 }, 1)); }
TEST_CASE("Can place ONE new flower in size 2, empty") { REQUIRE(Solution{}.canPlaceFlowers({ 0, 0 }, 1)); }
TEST_CASE("Can place ONE new flower in size 3, empty") { REQUIRE(Solution{}.canPlaceFlowers({ 0, 0, 0 }, 1)); }
TEST_CASE("Can place ONE new flower 3, flowers in 0th") { REQUIRE(Solution{}.canPlaceFlowers({ 1, 0, 0 }, 1)); }
TEST_CASE("Can place ONE new flower in size 3, flowers in 2nd") { REQUIRE(Solution{}.canPlaceFlowers({ 0, 0, 1 }, 1)); }
TEST_CASE("Can place ONE new flower gap of three empty slots") { REQUIRE(Solution{}.canPlaceFlowers({ 1, 1, 0, 0, 0, 1 }, 1)); }
TEST_CASE("Can place ONE new flower gap of 2 at front") { REQUIRE(Solution{}.canPlaceFlowers({ 0, 0, 1, 1, 1, 1 }, 1)); }
TEST_CASE("Can place ONE new flower gap of 2 at end") { REQUIRE(Solution{}.canPlaceFlowers({ 1, 1, 1, 1, 0, 0 }, 1)); }

TEST_CASE("Cannot place ONE new flower in size 0, flowers in 0th") { REQUIRE_FALSE(Solution{}.canPlaceFlowers({}, 1)); }
TEST_CASE("Cannot place ONE new flower in size 1, full") { REQUIRE_FALSE(Solution{}.canPlaceFlowers({ 1 }, 1)); }
TEST_CASE("Cannot place ONE new flower in size 2, flowers in 0th") { REQUIRE_FALSE(Solution{}.canPlaceFlowers({ 1, 0 }, 1)); }
TEST_CASE("Cannot place ONE new flower in size 2, flowers in 1st") { REQUIRE_FALSE(Solution{}.canPlaceFlowers({ 0, 1 }, 1)); }
TEST_CASE("Cannot place ONE new flower in size 3, flowers in 1st") { REQUIRE_FALSE(Solution{}.canPlaceFlowers({ 0, 1, 0 }, 1)); }
TEST_CASE("Cannot place ONE new flower gap of two empty slots") { REQUIRE_FALSE(Solution{}.canPlaceFlowers({ 1, 1, 0, 0, 1, 1 }, 1)); }

// TWO FLOWERS PLACED
TEST_CASE("Can place TWO new flowers in size 3, empty") { REQUIRE(Solution{}.canPlaceFlowers({ 0, 0, 0 }, 2)); }
TEST_CASE("Can place TWO new flowers in with 2 gaps (not at ends)") { REQUIRE(Solution{}.canPlaceFlowers({ 1, 0, 0, 0, 1, 0, 0, 0, 1 }, 2)); }
TEST_CASE("Can place TWO new flowers in with gap at each end") { REQUIRE(Solution{}.canPlaceFlowers({ 0, 0, 1, 0, 0 }, 2)); }
TEST_CASE("Can place TWO new flowers in flowerbed with alternating unoccupied slots") { REQUIRE(Solution{}.canPlaceFlowers({ 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1 }, 2)); }

TEST_CASE("Cannot place TWO new flower in size 1, empty") { REQUIRE_FALSE(Solution{}.canPlaceFlowers({ 0, 0 }, 2)); }
TEST_CASE("Cannot place TWO new flower in size 2, empty") { REQUIRE_FALSE(Solution{}.canPlaceFlowers({ 0, 0 }, 2)); }
TEST_CASE("Cannot place TWO new flower in with 1 insufficient gap (not at ends)") { REQUIRE_FALSE(Solution{}.canPlaceFlowers({ 1, 0, 0, 0, 1, 0, 0, 1 }, 2)); }
TEST_CASE("Cannot place TWO new flower in one large gap") { REQUIRE_FALSE(Solution{}.canPlaceFlowers({ 1, 0, 0, 0, 0, 1 }, 2)); }

// >2 FLOWERS PLACED
