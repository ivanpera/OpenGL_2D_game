#ifndef COMMON
#define COMMON

#include <string>

namespace myCommon {

	constexpr float PI = 3.14159265358979323846f;

	enum class DrawMode { points, lines, lines_strip, lines_loop, triangles, triangles_fan, triangles_strip };

	struct vec3 {
		float x, y, z;

		bool operator <= (float const& factor) const {
			return !(*this >= factor);
		}

		bool operator >= (float const& factor) const {
			return this->x >= factor && this->y >= factor && this->z >= factor;
		}

		bool operator == (vec3 const& other) const {
			return this->x == other.x && this->y == other.y && this->z == other.z;
		}

		vec3 operator / (vec3 const& other) const {
			return { this->x / other.x, this->y / other.y, this->z / other.z };
		}

		vec3 operator + (vec3 const& other) const {
			return { this->x + other.x, this->y + other.y, this->z + other.z };
		}

		vec3 operator * (vec3 const& other) const {
			return { this->x * other.x, this->y * other.y, this->z * other.z };
		}

		vec3 operator * (float const& other) const {
			return { this->x * other, this->y * other, this->z * other };
		}

		vec3 operator + (float const& other) const {
			return { this->x + other, this->y + other, this->z + other };
		}

		vec3 operator - (float const& other) const {
			return { this->x - other, this->y - other, this->z - other };
		}

		vec3 operator / (float const& other) const {
			return { this->x / other, this->y / other, this->z / other };
		}

		vec3 operator - (vec3 const& other) const {
			return { this->x - other.x, this->y - other.y, this->z - other.z };
		}

		vec3& operator = (vec3 const& other) {
			this->x = other.x;
			this->y = other.y;
			this->z = other.z;
			return *this;
		}

		vec3& operator += (vec3 const& other) {
			this->x += other.x;
			this->y += other.y;
			this->z += other.z;
			return *this;
		}

		vec3& operator *= (vec3 const& other) {
			this->x *= other.x;
			this->y *= other.y;
			this->z *= other.z;
			return *this;
		}
	};

	struct vec4 {
		float x, y, z, w;
	};

	struct Point {
		vec3 coords;
		vec4 color;
	};

	float const signAngleCos(float grad);

	float const signAngleSin(float grad);

	float degToRad(float const& grad);

	std::string const vecToString(vec3 vec, std::string name);

}
#endif
