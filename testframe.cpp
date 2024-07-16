#include "orland_vect.h"
#include "orland_matrix.h"
#include "testframe.h"
#include <iostream>
#include <cassert>
#include <cmath>

using namespace std::literals;

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

void TestMatrix() {
	using matrix = std::vector<std::vector<double>>;
	{
		orland::Matrix m1 (2,1);
		m1.AddElement(1, 1, 2.);
		m1.AddElement(2, 1, 3.);
		orland::Matrix vector(1, 2);
		vector.AddElement(1, 1, 3.);
		vector.AddElement(1, 2, 4.);
		matrix check = { {0, 0}, { 0, 18 } };
		orland::Matrix res = orland::Multiply(vector, m1);
		assert(res.GetMatrix() == check);
	}
	{
		std::vector<orland::Vector3D> matrix_a{ { 1, 1, 0 }, { 1, 0, 1 }, { 1, -1, 1 } };
		std::vector<orland::Vector3D> matrix_b{ { 0, 2, 1 }, { 0, 1, 0 }, { 1, 0, -1 } };
		orland::Matrix m_a(matrix_a), m_b(matrix_b);
		orland::Matrix res = orland::Multiply(m_a, m_b);
		matrix check = { {0, 0, 0, 0}, {0, 3, 1, 0 }, {0, -1, 0, 2}, {0, 3, 1, -1} };
		assert(res.GetMatrix() == check);

	}
	{
		std::vector<orland::Vector3D> matrix_a{ { 3, -2, 5 } };
		std::vector<orland::Vector3D> matrix_b{ { 0, 0, 1 }, { 2, 1, 0 }, { 1, 0, -1 } };
		orland::Matrix m_a(matrix_a), m_b(matrix_b);
		orland::Matrix res = orland::Multiply(m_b, m_a);
		matrix check = { {0, 0}, {0, 1}, {0, -2}, {0, -2} };
		assert(res.GetMatrix() == check);

	}
	{
		orland::Matrix standart_bas = orland::GetStandart3D();
		orland::Matrix vector(3, 1);
		vector.AddElement(1, 1, 3.);
		vector.AddElement(2, 1, 4.);
		vector.AddElement(3, 1, 5.);
		orland::Matrix res = orland::Multiply(standart_bas, vector);
		assert(res == vector);
	}
}

void FullTest() {
	RUN_TEST(TestVector2d);
	RUN_TEST(TestVector3d);
	RUN_TEST(TestMatrix);
}