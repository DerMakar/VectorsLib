#pragma once
#include "orland_vect.h"
#include <vector>

namespace orland {
	class Object {
	public:
		Object() = default;
		
		// ������������ ��� ������� �� �������� ���� � ��������
		void RotateAll(double angle);

		// ������� ��� ������� �� �������� ����������
		void MoveAll(const Vector2D& move);
	private:
		std::vector<Vector2D> desk_;
	};
}//namespace orland
