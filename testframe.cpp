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

void FullTest() {
	TestVector2d();
	std::cout << "FullTest is done!" << std::endl;
}