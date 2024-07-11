#pragma once
#include "orland_vect.h"
#include <vector>

namespace orland {
	class Desk2D {
	public:
		Desk2D() = default;
		
		// Поворачивает все векторы на заданный угол в градусах
		void RotateAll(double angle);
	private:
		std::vector<Vector2D> desk_;
	};
}//namespace orland
