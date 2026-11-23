// -*- mode:C++; c-basic-offset:2; indent-tabs-mode:nil -*-;
// Copyright 2026 Glen S. Dayton. Rights reserved according to terms of included license.
//
// Created by Glen Dayton on 11/14/26.
//

#include <cstddef>
#include <stdexcept>
#include <expected>

#ifndef BIGNUMBER_ARRAY_HPP
#define BIGNUMBER_ARRAY_HPP

namespace big_number {
    template <typename ElementType>
    class Array
    {
        std::size_t capacity;
        ElementType *data;

        Array(std::size_t requestedCapacity);

    public:
        auto create(size_t requestedCapacity) -> std::expected<Array, std::exception>;
    };


    template<typename ElementType>
    Array<ElementType>::Array(std::size_t requestedCapacity)
        : capacity(requestedCapacity),
          data(new ElementType)
    {

    }
}


#endif //BIGNUMBER_ARRAY_HPP
