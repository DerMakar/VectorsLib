#include "orland_vect.h"
#include "testframe.h"
#include <iostream>
#include <cassert>
#include <cmath>

void TestVector2d() {
	using Vector2D = orland::Vector2D;
	{
		Vector2D vec1(1., 2.);
		Vector2D vec2(2., 3.);
		assert(vec1 + vec2 == Vector2D(3., 5.));
		assert(vec1 - vec2 == Vector2D(-1., -1.));
		vec1.Subtract(vec2);
		assert(vec1 == Vector2D(-1., -1.));
	}
	{
		orland::Vector2D vec1(2., 2.);
		assert(vec1.Length() == std::sqrt(8.));
		vec1.Scale(2);
		assert(vec1 == Vector2D(4., 4.));
		vec1.Reverse();
		assert(vec1 == Vector2D(-4., -4.));
		assert(orland::GetReverse(vec1) == Vector2D(4., 4.));
	}
	{
		orland::Vector2D dec_vec (3., 4.);
		orland::PolarVector polar(dec_vec);
		orland::Vector2D new_dec_vec(polar);
		assert(new_dec_vec == dec_vec);
	}
	{
		orland::Vector2D vec1(1., 0.);
		orland::Vector2D vec2(0., 1.);
		assert(vec1.DirStatuc(vec2) == orland::Vector2D::COMMON_DIR::PERPENDICULAR);
		assert(std::abs(vec1.GetBetweenAngle(vec2) - 90.) <= orland::Dopusk);
	}
	{
		orland::Vector2D vec1(1., 0.);
		orland::Vector2D vec2(5., 0.);
		assert(vec1.DirStatuc(vec2) == orland::Vector2D::COMMON_DIR::POSITIVE_ON_LINE);
	}
	{
		orland::Vector2D vec1(1., 0.);
		orland::Vector2D vec2(-5., 0.);
		assert(vec1.DirStatuc(vec2) == orland::Vector2D::COMMON_DIR::NEGATIVE_ON_LINE);
	}
	{
		orland::Vector2D vec1(1., 0.);
		orland::Vector2D vec2(-5., 1.);
		assert(vec1.DirStatuc(vec2) == orland::Vector2D::COMMON_DIR::NEGATIVE);
	}
	{
		orland::Vector2D vec1(1., 0.);
		orland::Vector2D vec2(5., 1.);
		assert(vec1.DirStatuc(vec2) == orland::Vector2D::COMMON_DIR::POSITIVE);
	}
	{
		orland::Vector2D vec1(1., 0.);
		orland::Vector2D vec2(5.4, 1.7);
		double angle = vec1.GetBetweenAngle(vec2);
		vec1.Rotate(angle);
		assert(vec1.DirStatuc(vec2) == orland::Vector2D::COMMON_DIR::POSITIVE_ON_LINE);
	}
	{
		// Rotate
	}
	std::cout << "TestVector2d is done!" << std::endl;
}

void TestVector3d() {
	{
		orland::Vector3D vec1(1., 0., 0.);
		orland::Vector3D vec2(0., 1., 0.);
		assert(std::abs(vec1.GetBetweenAngle(vec2) - 90.) <= orland::Dopusk);
	}
	{
		orland::Vector3D vec1(1., 1., 0.);
		orland::Vector3D vec2(0., 0., 1.);
		assert(std::abs(vec1.GetBetweenAngle(vec2) - 90.) <= orland::Dopusk);
	}
	{
		orland::Vector3D vec1(1., 0., 0.);
		orland::Vector3D vec2(0., 0., 1.);
		orland::Vector3D test_per(0., -1., 0.);
		assert(vec1.Normal(vec2) == test_per);
	}
	{
		orland::Vector3D vec1(1., 0., 0.);
		orland::Vector3D vec2(0., 0., 1.);
		assert(vec1.Dir3DStatus(vec2) == orland::Vector3D::DIR_STATUS_3D::PERPENDICULAR);
		assert(std::abs(vec1.SquareBetween(vec2) - 1.) < orland::Dopusk);
	}
	{
		orland::Vector3D vec1(1., 0., 0.);
		orland::Vector3D vec2(3., 0., 0.);
		assert(vec1.Dir3DStatus(vec2) == orland::Vector3D::DIR_STATUS_3D::PARALLEL);
		assert(std::abs(vec1.SquareBetween(vec2) - 0.) < orland::Dopusk);
	}
	{
		orland::Vector3D vec1(1., 0., 0.);
		orland::Vector3D vec2(-3., 2., 0.);
		assert(vec1.Dir3DStatus(vec2) == orland::Vector3D::DIR_STATUS_3D::RANDOM);
	}
	{
		orland::Vector3D vec1(4., 4., 4.);
		orland::Vector3D singular = vec1.GetSingular();
		assert(std::abs(singular.Length() - 1.) < orland::Dopusk);
	}
	{
		orland::Vector3D vec1(1., 1., 1.);
		vec1.TurnAroundX(90.);
		assert(vec1 == orland::Vector3D(1., -1., 1.));
		vec1.TurnAroundX(-180.);
		assert(vec1 == orland::Vector3D(1., 1., -1.));
		vec1.TurnAroundY(-90.);
		assert(vec1 == orland::Vector3D(1., 1., 1.));
		vec1.TurnAroundZ(90.);
		assert(vec1 == orland::Vector3D(-1., 1., 1.));
	}
	{
		orland::Vector3D vec1(1., 1., 1.);
		orland::Vector3D vec2(1., -1., 1.);
		assert(vec1.GetPointBetween(0.5, vec2) == orland::Vector3D(1., 0., 1.));
	}
}

void FullTest() {
	TestVector2d();
	TestVector3d();
	std::cout << "FullTest is done!" << std::endl;
}