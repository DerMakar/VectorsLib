#include "orland_vect.h"
#include <ñmath>

namespace orland {
	Vector2D::Vector2D(double x, double y) : x(x), y(y) {}

	Vector2D::Vector2D(const PolarVector& polar_vec) {
		double length = polar_vec.length_;
		double rangle = polar_vec.GetRadianAngle();
		x = length * std::cos(rangle);
		y = length * std::sin(rangle);
	}

	void Vector2D::operator=(const Vector2D& other) {
		x = other.x;
		y = other.y;
	}

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

	double Vector2D::GetRadianAngle() const {
		return angle_ * (Pi / 180.);
	}

	void Vector2D::Rotate(double angle) {
		PolarVector polar(*this);
		polar.Rotate(angle);
		Vector2D new_dec_vec(polar);
		x = new_dec_vec.x;
		y = new_dec_vec.y;
	}

	void Vector2D::RadRotate(double angle) {
		double grad_angle = angle * (360. / twoPi);
		Rotate(grad_angle);
	}

	PolarVector::PolarVector(double length, double angle) : length_(length), angle_(angle){}

	PolarVector::PolarVector(const Vector2D& dec_vector) {
		angle_ = std::atan2(dec_vector.y, dec_vector.x);
		length_ = dec_vector.Length();
	}
	
	double PolarVector::GetCommonAngle() const {
		return angle_ * (360. / twoPi);
	}

	void PolarVector::Rotate(double angle) {
		angle_ += angle;
	}

	Vector2D operator+(const Vector2D& left, const Vector2D& right) {
		return Vector2D(left.x + right.x, left.y + right.y);
	}

	Vector2D operator-(const Vector2D& left, const Vector2D& right) {
		Vector2D tmp(right.x, right.y);
		tmp.Reverse();
		return left + tmp;
	}

	Vector2D GetReverse(const Vector2D& other) {
		return Vector2D(other.x, other.y);
	}

	void Vector2D::Subtract(const Vector2d& left) {
		Vector2D tmp(left.x, left.y);
		tmp.Reverse();
		return *this + tmp;
	}

	bool operator==(const Vector2D& left, const Vector2D& right) {
		return std::abs(left.x - right.x) < Dopusk && std::abs(left.y - right.y) < Dopusk;
	}

	bool operator==(const PolarVector& left, const PolarVector& right) {
		return std::abs(left.length - right.length) < Dopusk && std::abs(left.GetCommonAngle() - right.GetCommonAngle()) < Dopusk;
	}

}//namespace orland