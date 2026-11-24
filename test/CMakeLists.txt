

set (Boost_USE_STATIC_LIBS OFF)
find_package (Boost REQUIRED CONFIG COMPONENTS unit_test_framework)

add_executable(test_bignumber test.cpp
        test_array.cpp)

target_link_libraries (test_bignumber PRIVATE bignumber Boost::unit_test_framework)
add_test(NAME test_bignumber COMMAND test_bignumber)

