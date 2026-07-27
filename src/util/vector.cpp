#include "vector.h"
#include <algorithm>
#include <cstdint>

static inline int8_t FloatToByte(float coord, float scale) {
	if (scale <= 0.0f) {
		return 0;
	}
	float normalized = std::clamp(coord / scale, -1.0f, 1.0f);
	return static_cast<int8_t>(normalized * 127.0f);
}

static inline float ByteToFloat(int8_t coord, float scale) {
	int8_t clampedCoord = std::max<int8_t>(coord, -127);
	return (static_cast<float>(clampedCoord) / 127.0f) * scale;
}

ByteVec3 Vec3ToByteVec3(Vec3 coord, float scale) {

	return ByteVec3{
		.x = FloatToByte(coord.x, scale),
		.y = FloatToByte(coord.y, scale),
		.z = FloatToByte(coord.z, scale),
	};
}

Vec3 ByteVec3ToVec3(ByteVec3 coord, float scale) {

	return Vec3(ByteToFloat(coord.x, scale), ByteToFloat(coord.y, scale), ByteToFloat(coord.z, scale));
}
