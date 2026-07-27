#pragma once
#include <cstdint>

#include <MTH.h>

/** A serializable 3-dimensional position vector. */
struct Vec3 {
    float x;
    float y;
    float z;

    Vec3(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {}

    // Conversion operators to convert between CPA struct and this struct
    Vec3(const MTH3D_tdstVector& v)
        : x(v.x), y(v.y), z(v.z) {
    }

    operator MTH3D_tdstVector() const {
        return MTH3D_tdstVector{ x, y, z };
    }
};

template<typename S>
void serialize(S& s, Vec3& v) {
    s.value4b(v.x);
    s.value4b(v.y);
    s.value4b(v.z);
}

/** Tiny variant of a Vec3 with one byte of precision per coordinate */
struct ByteVec3 {
    int8_t x;
    int8_t y;
    int8_t z;
};

template<typename S>
void serialize(S& s, ByteVec3& v) {
    s.value1b(v.x);
    s.value1b(v.y);
    s.value1b(v.z);
}

// Helper functions to convert between Vec3 and ByteVec3
ByteVec3 Vec3ToByteVec3(Vec3 coord, float scale);
Vec3 ByteVec3ToVec3(ByteVec3 coord, float scale);