#ifndef VECTOR3_H
#define VECTOR3_H

#include <iostream>

template <typename T>
struct Vector3 {
public:
	T x;
	T y;
	T z;

public:
	Vector3(const std::uint16_t val = 0);
	Vector3(const std::uint16_t x, const std::uint16_t y, const std::uint16_t z);

	bool operator==(const Vector3<T>& other) const;

	void readFrom(std::istream& in = std::cin);
	void writeTo(std::ostream& out = std::cout) const;
};

#endif // !VECTOR3_H

template<typename T>
inline Vector3<T>::Vector3(const std::uint16_t val)
					: x(val), y(val), z(val) {
}

template<typename T>
inline Vector3<T>::Vector3(const std::uint16_t x, const std::uint16_t y, const std::uint16_t z)
					: x(x), y(y), z(z) {
}

template<typename T>
inline bool Vector3<T>::operator==(const Vector3<T>& other) const {
	return (x == other.x && y == other.y && z == other.z);
}

template<typename T>
inline void Vector3<T>::readFrom(std::istream& in) {
	in >> x >> y >> z;
}

template<typename T>
inline void Vector3<T>::writeTo(std::ostream& out) const {
	out << x << ' ' << y << ' ' << z;
}
