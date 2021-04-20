//
// Created by david on 4/19/21.
//
/**
 * Test for Board.cpp
 *
 * AUTHORS: david
 *
 * Date: 4/19/21
 */

#include "NumberWithUnits.hpp"
#include "doctest.h"
using namespace doctest;
#include <string>

using namespace ariel;

using namespace std;
//

TEST_CASE ("g") {


/* Add more checks here */
}
//1 km = 1000 m
//1 m = 100 cm
//1 kg = 1000 g
//1 ton = 1000 kg
//1 hour = 60 min
//1 min = 60 sec
//1 USD = 3.33 ILS

TEST_CASE ("throws checks") {
    NumberWithUnits km2{2, "km"};
    NumberWithUnits m2000{2000, "m"};
    NumberWithUnits m500{500, "m"};
    NumberWithUnits cm100{100, "cm"};

    NumberWithUnits hour1{2, "km"};
    NumberWithUnits min30{2000, "m"};
    NumberWithUnits USD500{500, "USD"};
    NumberWithUnits ILS100{1000, "ILS"};
    NumberWithUnits ropy100{10000, "ropy"};
////km
CHECK_THROWS(km2+hour1);
CHECK_THROWS(km2+min30);
CHECK_THROWS(km2+USD500);
CHECK_THROWS(km2+ILS100);
CHECK_THROWS(km2+ropy100);

CHECK_NOTHROW(km2-m2000);
CHECK_NOTHROW(km2-m500);
CHECK_NOTHROW(km2-cm100);

CHECK_NOTHROW(km2+m2000);
CHECK_NOTHROW(km2+m500);
CHECK_NOTHROW(km2+cm100);

CHECK_NOTHROW(km2++);
CHECK_NOTHROW(++km2);

CHECK_NOTHROW(km2--);
CHECK_NOTHROW(--km2);

////time

CHECK_NOTHROW(min30-hour1);
CHECK_NOTHROW(min30+hour1);
CHECK_NOTHROW(min30-min30);
CHECK_NOTHROW(min30+min30);
CHECK_NOTHROW(min30--);
CHECK_NOTHROW(--min30);

CHECK_THROWS(min30-USD500);
CHECK_THROWS(min30-ILS100);
CHECK_THROWS(min30-ropy100);
CHECK_THROWS(USD500+min30);
CHECK_THROWS(USD500-min30);
CHECK_THROWS(cm100+min30);
CHECK_THROWS(km2+hour1);

CHECK_THROWS(ropy100++);
CHECK_THROWS(ropy100--);
CHECK_THROWS(--ropy100);
CHECK_THROWS(++ropy100);

CHECK_NOTHROW(ILS100++);
CHECK_NOTHROW(ILS100--);
CHECK_NOTHROW(ILS100++);
CHECK_NOTHROW(ILS100--);

CHECK_FALSE(ILS100==USD500);
CHECK_FALSE(ILS100>USD500);

    CHECK(cm100==NumberWithUnits{1,"m"});
    CHECK(cm100<NumberWithUnits{10,"m"});
    CHECK_FALSE(cm100==NumberWithUnits{10,"m"});




}

/* Add more test cases here */
//add test for each body part
