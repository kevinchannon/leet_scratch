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
  static constexpr auto UNOCCUPIED = 0;
  static constexpr auto OCCUPIED = 1;

  [[nodiscard]] static bool is_occupied(int val) noexcept { return val == OCCUPIED; }
public:

  using flowerbed_t = std::vector<int>;

  bool canPlaceFlowers(const flowerbed_t& flowerbed, int n) {
    if (n == 0) {
      return true;
    }

    if (not leet::any(flowerbed, OCCUPIED)) {
      switch (n) {
      case 1: return not flowerbed.empty();
      default: return flowerbed.size() >= 2 * static_cast<unsigned long long>(n) - 1;
      }
    }

    switch (flowerbed.size()) {
    case 0:
    case 1:
    case 2:
      return false;
    case 3:
      return flowerbed == flowerbed_t{ 0, 0, 1 } or flowerbed == flowerbed_t{ 1, 0, 0 };
    default:;
    }

    return true;
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

TEST_CASE("Cannot place ONE new flower in size 0, flowers in 0th") { REQUIRE_FALSE(Solution{}.canPlaceFlowers({}, 1)); }
TEST_CASE("Cannot place ONE new flower in size 1, full") { REQUIRE_FALSE(Solution{}.canPlaceFlowers({ 1 }, 1)); }
TEST_CASE("Cannot place ONE new flower in size 2, flowers in 0th") { REQUIRE_FALSE(Solution{}.canPlaceFlowers({ 1, 0 }, 1)); }
TEST_CASE("Cannot place ONE new flower in size 2, flowers in 1st") { REQUIRE_FALSE(Solution{}.canPlaceFlowers({ 0, 1 }, 1)); }
TEST_CASE("Cannot place ONE new flower in size 3, flowers in 1st") { REQUIRE_FALSE(Solution{}.canPlaceFlowers({ 0, 1, 0 }, 1)); }

// TWO FLOWERS PLACED
TEST_CASE("Can place TWO new flower in size 3, empty") { REQUIRE(Solution{}.canPlaceFlowers({ 0, 0, 0 }, 2)); }

TEST_CASE("Cannot place TWO new flower in size 1, empty") { REQUIRE_FALSE(Solution{}.canPlaceFlowers({ 0, 0 }, 2)); }
TEST_CASE("Cannot place TWO new flower in size 2, empty") { REQUIRE_FALSE(Solution{}.canPlaceFlowers({ 0, 0 }, 2)); }
