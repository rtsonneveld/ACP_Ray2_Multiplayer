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