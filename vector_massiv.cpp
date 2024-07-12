#include "vector_massiv.h"

namespace orland {
	
	void Object::RotateAll(double angle) {
		for (Vector2D& vec : desk_) {
			vec.Rotate(angle);
		}
	}

	void Object::MoveAll(const Vector2D& move) {
		for (Vector2D& vec : desk_) {
			vec.Move(move);
		}
	}
} //namespace orland

//�������� ���������� ������������� ����� ��������� ��������� ��������� 
// �������(1, 0) ������ ������� �������, ������� n (����� �����) ��� �� 2*pi*k/n ����

/*
����������� ������� � ��������� � �������� ������� ����� ���������� ��������� � ������������ ������� ��� ����������. 
���� ������� ��������������� � ������� ������� �����������, �� �� �� ����� ������������ ������.
*/