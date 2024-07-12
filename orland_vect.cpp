#include <cmath>

#include "orland_vect.h"


namespace orland {
	Vector2D::Vector2D(double x, double y) : x(x), y(y) {}

	Vector2D::Vector2D(const PolarVector& polar_vec) {
		double length = polar_vec.GetLength();
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


	void Vector2D::Scale(double scalar) {
		x *= scalar;
		y *= scalar;
	}

	Vector2D Vector2D::Scale(double scalar) const {
		return Vector2D(x * scalar, y * scalar);
	}

	void Vector2D::Move(const Vector2D& right) {
		x += right.GetX();
		y += right.GetY();
	}

	void Vector2D::Subtract(const Vector2D& right) {
		Vector2D tmp(right.x, right.y);
		tmp.Reverse();
		Move(tmp);
	}

	void Vector2D::Reverse() {
		x *= -1.;
		y *= -1.;
	}

	Vector2D Vector2D::Reverse() const {
		return Vector2D(-1. * x, -1. * y);
	}	

	void Vector2D::Rotate(double angle) {
		PolarVector polar(*this);
		polar.Rotate(angle);
		Vector2D new_dec_vec(polar);
		x = new_dec_vec.x;
		y = new_dec_vec.y;
	}

	void Vector2D::RadRotate(double rad_angle) {
		double grad_angle = rad_angle * (360. / twoPi);
		Rotate(grad_angle);
	}

	double Vector2D::GetX() const {
		return x;
	}
	double Vector2D::GetY() const {
		return y;
	}

	double Vector2D::Scalar(const Vector2D& other) const {
		return x * other.GetX() + y * other.GetY();
	}

	Vector2D::COMMON_DIR Vector2D::DirStatuc(const Vector2D& other) const {
		double scalar = Scalar(other);
		double total_length = Length() * other.Length();
		if (std::abs(scalar - 0.) <= Dopusk) {
			return COMMON_DIR::PERPENDICULAR;
		}
		else if (std::abs(std::abs(scalar) - total_length) <= Dopusk) {
			return scalar > 0. ? COMMON_DIR::POSITIVE_ON_LINE : COMMON_DIR::NEGATIVE_ON_LINE;
		}
		return scalar > 0. ? COMMON_DIR::POSITIVE : COMMON_DIR::NEGATIVE;
	}

	double Vector2D::GetBetweenAngle(const Vector2D& other) const {
		double scalar = Scalar(other);
		double total_length = Length() * other.Length();
		if (std::abs(total_length - 0.) <= Dopusk) return 1.;
		double rad_angle = std::acos(scalar / total_length);
		return RadToGrad(rad_angle);
	}

	PolarVector::PolarVector(double length, double angle) : length_(length), angle_(angle){}

	PolarVector::PolarVector(const Vector2D& dec_vector) {
		angle_ = std::atan2(dec_vector.GetY(), dec_vector.GetX());
		angle_ = RadToGrad(angle_);
		length_ = dec_vector.Length();
	}
	
	double PolarVector::GetCommonAngle() const {
		return angle_;
	}

	double PolarVector::GetRadianAngle() const {
		return angle_ * (Pi / 180.);
	}

	void PolarVector::Rotate(double angle) {
		angle_ += angle;
	}

	double PolarVector::GetLength() const {
		return length_;
	}

	double PolarVector::GetAngle() const {
		return angle_;
	}

	

	Vector2D GetReverse(const Vector2D& other) {
		return Vector2D(-other.GetX(), -other.GetY());
	}	

	bool operator==(const Vector2D& left, const Vector2D& right) {
		return std::abs(left.GetX() - right.GetX()) < Dopusk && std::abs(left.GetY() - right.GetY()) < Dopusk;
	}

	bool operator!=(const Vector2D& left, const Vector2D& right) {
		return !(left == right);
	}

	Vector2D operator+(const Vector2D& left, const Vector2D& right) {
		return Vector2D(left.GetX() + right.GetX(), left.GetY() + right.GetY());
	}

	Vector2D operator-(const Vector2D& left, const Vector2D& right) {
		Vector2D tmp(right.GetX(), right.GetY());
		tmp.Reverse();
		return left + tmp;
	}

	double Distance(const Vector2D& start, const Vector2D& finish) {
		return (start - finish).Length();
	}

	bool operator==(const PolarVector& left, const PolarVector& right) {
		return std::abs(left.GetLength() - right.GetLength()) < Dopusk && std::abs(left.GetCommonAngle() - right.GetCommonAngle()) < Dopusk;
	}

	bool operator!=(const PolarVector& left, const PolarVector& right) {
		return !(left == right);
	}

	double RadToGrad(double rad_angle) {
		return rad_angle * (180. / Pi);
	}

}//namespace orland