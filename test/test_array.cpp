// -*- mode:C++; c-basic-offset:4; indent-tabs-mode:nil -*-;
// Copyright 2026 Glen S. Dayton. Rights reserved according to terms of included license.//
#include <boost/test/unit_test.hpp>
#include <bignumber/array.hpp>
#include <utility>

BOOST_AUTO_TEST_SUITE(TestBigNumber)

BOOST_AUTO_TEST_CASE(test_create)
{
    using SampleType = unsigned int;
    constexpr size_t sampleSize = 10;
    auto result = big_number::Array<SampleType>::create(sampleSize);

    BOOST_REQUIRE(result.has_value());
    const auto array = std::move(result.value());
    BOOST_CHECK_EQUAL(array.capacity(), sampleSize);
    BOOST_CHECK_EQUAL(array.size(), 0u);
}
BOOST_AUTO_TEST_SUITE_END()
