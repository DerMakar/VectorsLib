#include "orland_vect.h"
#include <iostream>
#include <cassert>

void TestVector2d() {
	using Vector2D = orland::Vector2D;
	{
		Vector2D vec1(1., 2.);
		Vector2D vec2(2., 3.);
		assert(vec1 + vec2 == Vector2D(3., 3.));
		assert(vec1 - vec2 == Vector2D(-1., -1.));
		vec1.Subtract(vec2);
		assert(vec1 == Vector2D(-1., -1.));
	}
	{
		orland::Vector2D vec1(2., 2.);
		assert(vec1.Length() == 4.);
		assert(vec1.Sclar(2) == Vector2D(4., 4.));
		assert(vec1.Reverse() == Vector2D(-4., -4.));
		assert(orland::GetReverse(vec1) == Vector2D(4., 4.));
	}
	{
		orland::Vector2D dec_vec (3., 4.);
		orland::PolarVector polar(dec_vec);
		orland::Vector2D new_dec_vec(polar);
		assert(new_dec_vec == dec_vec);
	}
	{
		// Rotate
	}
	std::cout << "TestVector2d is done!" << std::endl;
}

void FullTest() {
	std::cout << "FullTest is done!" << std::endl;
}