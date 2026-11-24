// -*- mode:C++; c-basic-offset:4; indent-tabs-mode:nil -*-;
// Copyright 2026 Glen S. Dayton. Rights reserved according to terms of included license.
//
// Created by Glen Dayton on 11/14/26.
//

#ifndef BIGNUMBER_ARRAY_HPP
#define BIGNUMBER_ARRAY_HPP

#include <cstddef>
#include <expected>
#include <new>

namespace big_number {
    enum class Error {
        bad_allocation
    };

    template <typename ElementType>
    class Array
    {
        std::size_t mCapacity;
        std::size_t mSize;
        ElementType *data;

        Array(std::size_t requestedCapacity, ElementType *space);

    public:
        static auto create(std::size_t requestedCapacity) -> std::expected<Array, Error>;
        ~Array() {delete[] data;}

        Array(const Array&) = delete;
        auto operator=(const Array&) -> Array& = delete;

        Array(Array&& other) noexcept
            : mCapacity(other.mCapacity),
              mSize(other.mSize),
              data(other.data)
        {
            other.mCapacity = 0;
            other.mSize = 0;
            other.data = nullptr;
        }

        auto operator=(Array&& other) noexcept -> Array&
        {
            if (this != &other) {
                delete[] data;
                mCapacity = other.mCapacity;
                mSize = other.mSize;
                data = other.data;
                other.mCapacity = 0;
                other.mSize = 0;
                other.data = nullptr;
            }
            return *this;
        }

        [[nodiscard]] auto capacity() const -> std::size_t {return mCapacity;}
        [[nodiscard]] auto size() const -> std::size_t {return mSize;}
    };


    template<typename ElementType>
    Array<ElementType>::Array(const std::size_t requestedCapacity, ElementType* space)
        : mCapacity(requestedCapacity),
          mSize{0},
          data(space)
    {}



    template <typename ElementType>
    auto Array<ElementType>::create(std::size_t requestedCapacity) -> std::expected<Array, Error>
    {
        ElementType *space = new(std::nothrow) ElementType[requestedCapacity];
        if (space == nullptr) return std::unexpected(Error::bad_allocation);

        return Array {requestedCapacity, space};
    }


}


#endif //BIGNUMBER_ARRAY_HPP
