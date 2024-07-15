#include <cmath>
#include <cassert>

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

	Vector3D::Vector3D(double x, double y, double z)
		: x(x), y(y), z(z) {

	}

	void Vector3D::operator=(const Vector3D& other) {
		x = other.GetX(); y = other.GetY(); z = other.GetZ();
	}

	double Vector3D::Length() const {
		auto pow_ = [](double x) {return std::pow(x, 2); };
		return std::sqrt(pow_(x) + pow_(y) + pow_(z));
	}

	void Vector3D::Scale(double scalar) {
		x *= scalar; y *= scalar; z *= scalar;
	}

	Vector3D Vector3D::Scale(double scalar) const {
		return Vector3D(x * scalar, y * scalar, z * scalar);
	}

	void Vector3D::Reverse() {
		Scale(-1.);
	}

	Vector3D Vector3D::Reverse() const {
		return Vector3D(-x, -y, -z);
	}

	void Vector3D::Move(const Vector3D& right) {
		x += right.GetX(); y += right.GetY(); z += right.GetZ();
	}

	void Vector3D::Subtract(const Vector3D& right) {
		Vector3D reversed = right.Reverse();
		Move(reversed);
	}

	double Vector3D::GetX() const { return x; }
	double Vector3D::GetY() const { return y; }
	double Vector3D::GetZ() const { return z; }

	double Vector3D::Scalar(const Vector3D& other) const {
		return x * other.GetX() + y * other.GetY() + z * other.GetZ();
	}

	Vector2D::COMMON_DIR Vector3D::DirStatus(const Vector3D& other) const {
		using COMMON_DIR = Vector2D::COMMON_DIR;
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


	double Vector3D::GetBetweenAngle(const Vector3D& other) const {
		double scalar = Scalar(other);
		double total_length = Length() * other.Length();
		if (std::abs(total_length - 0.) <= Dopusk) return 1.;
		double rad_angle = std::acos(scalar / total_length);
		return RadToGrad(rad_angle);
	}

	
	Vector3D Vector3D::Normal(const Vector3D& other) const {
		double new_x = y * other.GetZ() - z * other.GetY();
		double new_y = z * other.GetX() - x * other.GetZ();
		double new_z = x * other.GetY() - y * other.GetX();
		return Vector3D(new_x, new_y, new_z);
	}

	Vector3D::DIR_STATUS_3D Vector3D::Dir3DStatus(const Vector3D& other) const {
		double normal_length = Normal(other).Length();
		double square = Length() * other.Length();
		return std::abs(normal_length - 0.) < Dopusk ?
			DIR_STATUS_3D::PARALLEL :
			std::abs(square - normal_length) < Dopusk ?
			DIR_STATUS_3D::PERPENDICULAR :
			DIR_STATUS_3D::RANDOM;
	}

	double Vector3D::SquareBetween(const Vector3D& other) const {
		double rad_angle = GradToRad(GetBetweenAngle(other));
		double square = Length() * other.Length() * std::sin(rad_angle);
		return square;
	}

	Vector3D Vector3D::GetSingular() const {
		double length = Length();
		if (std::abs(length - 0.) < Dopusk) return Vector3D(0., 0., 0.);
		double e1 = x / length;
		double e2 = y / length;
		double e3 = z / length;
		return Vector3D(e1, e2, e3);
	}

	void Vector3D::TurnAroundX(double angle) {
		PolarVector polar2D(Vector2D(y, z));
		polar2D.Rotate(angle);
		Vector2D new_vec(polar2D);
		y = new_vec.GetX();
		z = new_vec.GetY();
	}

	void Vector3D::TurnAroundY(double angle) {
		PolarVector polar2D(Vector2D(x, z));
		polar2D.Rotate(-angle);
		Vector2D new_vec(polar2D);
		x = new_vec.GetX();
		z = new_vec.GetY();
	}

	void Vector3D::TurnAroundZ(double angle) {
		PolarVector polar2D(Vector2D(x, y));
		polar2D.Rotate(angle);
		Vector2D new_vec(polar2D);
		x = new_vec.GetX();
		y = new_vec.GetY();
	}

	Vector3D Vector3D::GetPointBetween(double part, const Vector3D& other) const {
		assert(part >= 0. && part <= 1.);
		Vector3D start = Scale(part);
		Vector3D finish = other.Scale(1. - part);
		return start + finish;
	}
	

	Vector2D GetReverse(const Vector2D& other) {
		return Vector2D(-other.GetX(), -other.GetY());
	}	

	bool operator==(const Vector2D& left, const Vector2D& right) {
		return std::abs(left.GetX() - right.GetX()) <= Dopusk && std::abs(left.GetY() - right.GetY()) <= Dopusk;
	}

	bool operator==(const Vector3D& left, const Vector3D& right) {
		return std::abs(left.GetX() - right.GetX()) <= Dopusk && std::abs(left.GetY() - right.GetY()) <= Dopusk && std::abs(left.GetZ() - right.GetZ()) <= Dopusk;
	}

	bool operator!=(const Vector2D& left, const Vector2D& right) {
		return !(left == right);
	}

	bool operator!=(const Vector3D& left, const Vector3D& right) {
		return !(left == right);
	}

	Vector2D operator+(const Vector2D& left, const Vector2D& right) {
		return Vector2D(left.GetX() + right.GetX(), left.GetY() + right.GetY());
	}

	Vector3D operator+(const Vector3D& left, const Vector3D& right) {
		return Vector3D(left.GetX() + right.GetX(), left.GetY() + right.GetY(), left.GetZ() + right.GetZ());
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

	double GradToRad(double grad_angle) {
		return grad_angle * (Pi / 180.);
	}
	

}//namespace orland