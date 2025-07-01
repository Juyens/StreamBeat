#pragma once

#include <iostream>
#include <cmath>

namespace sb
{
	template <typename T>
	class Vector2 
	{
		static_assert(std::is_arithmetic<T>::value, "Vector2 only supports arithmetic types");

	private:
		T x_;
		T y_;

	public:
		constexpr Vector2() : x_{}, y_{} {}
		constexpr Vector2(T x, T y) : x_{ x }, y_{ y } {}

		constexpr T x() const { return x_; }
		constexpr T y() const { return y_; }

		void setX(T x) { x_ = x; }
		void setY(T y) { y_ = y; }
		void set(T x, T y) { x_ = x; y_ = y; }

		constexpr Vector2 operator+(const Vector2& other) const { return Vector2(x_ + other.x_, y_ + other.y_); }
		constexpr Vector2 operator-(const Vector2& other) const { return Vector2(x_ - other.x_, y_ - other.y_); }
		constexpr Vector2 operator*(T scalar) const { return Vector2(x_ * scalar, y_ * scalar); }
		constexpr Vector2 operator/(T scalar) const { return Vector2(x_ / scalar, y_ / scalar); }

		constexpr bool operator==(const Vector2& other) const { return x_ == other.x_ && y_ == other.y_; }
		constexpr bool operator!=(const Vector2& other) const { return !(*this == other); }

		double length() const { return std::sqrt(static_cast<double>(x_ * x_ + y_ * y_)); }

		T manhattanDistance(const Vector2& other) const 
		{
			return static_cast<T>(std::abs(x_ - other.x_) + std::abs(y_ - other.y_));
		}

		friend std::ostream& operator<<(std::ostream& os, const Vector2& vec) 
		{
			os << "(" << vec.x_ << ", " << vec.y_ << ")";
			return os;
		}
	};

	using Vector2i = Vector2<int>;
	using Vector2u = Vector2<unsigned int>;
	using Vector2f = Vector2<float>;
	using Vector2d = Vector2<double>;
}