#include "orland_vect.h"
#include <math.h>

namespace orland {
	Vector2D::Vector2D(double x, double y) : x(x), y(y) {}

	double Vector2D::Length() const {
		return std::sqrt(std::pow(x, 2) + std::pow(y, 2));
	}

	void Vector2D::Sclar(double scalar) {
		x *= scalar;
		y *= scalar;
	}

	Vector2D Vector2D::Sclar(double scalar) const {
		return Vector2D(x * scalar; y * scalar);
	}

	void Vector2D::Reverse() {
		x *= -1.;
		y *= -1.;
	}

	Vector2D Vector2D::Reverse() const {
		return Vector2D(-1. * x, -1. * y);
	}

	Vector2D operator+(const Vector2D& left, const Vector2D& right) {
		return Vector2D(left.x + right.x, left.y + right.y);
	}

	Vector2D operator-(const Vector2D& left, const Vector2D& right) {
		Vector2D tmp(right.x, right.y);
		tmp.Reverse();
		return left + tmp;
	}

	void Vector2D::Subtract(const Vector2d& left) {
		Vector2D tmp(left.x, left.y);
		tmp.Reverse();
		return *this + tmp;
	}

	bool operator==(const Vector2D& left, const Vector2D& right) {
		return left.x == right.x && left.y == right.y;
	}

}//namespace orland