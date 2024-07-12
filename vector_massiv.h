#pragma once
#include "orland_vect.h"
#include <vector>

namespace orland {
	class Object {
	public:
		Object() = default;
		
		// ѕоворачивает все векторы на заданный угол в градусах
		void RotateAll(double angle);

		// —мещает все векторы на заданное рассто€ние
		void MoveAll(const Vector2D& move);
	private:
		std::vector<Vector2D> desk_;
	};
}//namespace orland
