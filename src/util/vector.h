#pragma once

/** A serializable 3-dimensional position vector. */
struct Vec3 {
    float x;
    float y;
    float z;
};

template<typename S>
void serialize(S& s, Vec3& v) {
    s.value4b(v.x);
    s.value4b(v.y);
    s.value4b(v.z);
}

/** Tiny variant of a Vec3 with one byte of precision per coordinate */
struct ByteVec3 {
    signed char x;
    signed char y;
    signed char z;
};

template<typename S>
void serialize(S& s, ByteVec3& v) {
    s.value1b(v.x);
    s.value1b(v.y);
    s.value1b(v.z);
}