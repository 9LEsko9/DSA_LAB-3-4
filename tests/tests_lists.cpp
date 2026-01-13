#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_all.hpp>
#include "DoubleList.h"
#include "OneList.h"
#include <sstream>

template<typename ListType>
std::string listToString(const ListType& list) {
    std::string result;
    for (int i = 0; i < list.size(); i++) {
        result += list[i];
    }
    return result;
}

TEST_CASE("OneList: Basic operations", "[OneList]") {
    OneList<int> list;

    SECTION("Empty list") {
        REQUIRE(list.empty());
        REQUIRE(list.size() == 0);
    }

    SECTION("push_front and front") {
        list.push_front(10);
        REQUIRE_FALSE(list.empty());
        REQUIRE(list.size() == 1);
        REQUIRE(list.front() == 10);
        REQUIRE(list.back() == 10);

        list.push_front(20);
        REQUIRE(list.size() == 2);
        REQUIRE(list.front() == 20);
        REQUIRE(list.back() == 10);
    }

    SECTION("push_back and back") {
        list.push_back(10);
        REQUIRE_FALSE(list.empty());
        REQUIRE(list.size() == 1);
        REQUIRE(list.front() == 10);
        REQUIRE(list.back() == 10);

        list.push_back(20);
        REQUIRE(list.size() == 2);
        REQUIRE(list.front() == 10);
        REQUIRE(list.back() == 20);
    }
}

TEST_CASE("DoubleList: Basic operations", "[DoubleList]") {
    DoubleList<int> list;

    SECTION("Empty list") {
        REQUIRE(list.empty());
        REQUIRE(list.size() == 0);
    }

    SECTION("push_front and front") {
        list.push_front(10);
        REQUIRE_FALSE(list.empty());
        REQUIRE(list.size() == 1);
        REQUIRE(list.front() == 10);
        REQUIRE(list.back() == 10);

        list.push_front(20);
        REQUIRE(list.size() == 2);
        REQUIRE(list.front() == 20);
        REQUIRE(list.back() == 10);
    }

    SECTION("push_back and back") {
        list.push_back(10);
        REQUIRE_FALSE(list.empty());
        REQUIRE(list.size() == 1);
        REQUIRE(list.front() == 10);
        REQUIRE(list.back() == 10);

        list.push_back(20);
        REQUIRE(list.size() == 2);
        REQUIRE(list.front() == 10);
        REQUIRE(list.back() == 20);
    }
}

TEST_CASE("DoubleList: Shell sort", "[DoubleList][sort]") {
    SECTION("Sort ascending numbers") {
        DoubleList<int> list;
        list.push_back(5);
        list.push_back(3);
        list.push_back(8);
        list.push_back(1);
        list.push_back(9);
        list.push_back(2);
        list.push_back(7);
        list.push_back(4);
        list.push_back(6);

        list.shell_sort();

        REQUIRE(list.size() == 9);
        for (int i = 0; i < 9; i++) {
            REQUIRE(list[i] == i + 1);
        }
    }

    SECTION("Sort already sorted list") {
        DoubleList<int> list;
        for (int i = 1; i <= 5; i++) {
            list.push_back(i);
        }

        list.shell_sort();

        REQUIRE(list.size() == 5);
        for (int i = 0; i < 5; i++) {
            REQUIRE(list[i] == i + 1);
        }
    }

    SECTION("Sort reverse order") {
        DoubleList<int> list;
        for (int i = 10; i >= 1; i--) {
            list.push_back(i);
        }

        list.shell_sort();

        REQUIRE(list.size() == 10);
        for (int i = 0; i < 10; i++) {
            REQUIRE(list[i] == i + 1);
        }
    }

    SECTION("Sort with duplicates") {
        DoubleList<int> list;
        list.push_back(3);
        list.push_back(1);
        list.push_back(2);
        list.push_back(1);
        list.push_back(3);
        list.push_back(2);

        list.shell_sort();

        REQUIRE(list.size() == 6);
        REQUIRE(list[0] == 1);
        REQUIRE(list[1] == 1);
        REQUIRE(list[2] == 2);
        REQUIRE(list[3] == 2);
        REQUIRE(list[4] == 3);
        REQUIRE(list[5] == 3);
    }
}
