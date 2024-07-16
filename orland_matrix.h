#pragma once
#include <vector>
#include <utility>
#include "orland_vect.h"

namespace orland {
	class Matrix {
	public:
		Matrix() = default;
		
		// --- ������� ������� � raws ����� � columns ��������
		// --- ��� �������� ��������, ��������� ������� �������� +1 ������
		// --- � +1 �������
		Matrix(int raws, int columns);

		// --- �������� ������� �� ������ ������� 3D ��������
		Matrix(const std::vector<Vector3D>& vectors3d);

		// --- ��������� ������� � �������� ������ � �������
		void AddElement(int raw, int column, double value);

		std::pair<int, int> GetDimension() const;

		double GetElement(int raw, int column) const;

		const std::vector<std::vector<double>>& GetMatrix() const;

	private:
		std::vector<std::vector<double>> matrix_;

		bool ValidAdr(int raw, int column) const;
	};

	Matrix GetStandart3D();

	// --- ��������� ������
	// --- ��: �������� ����� ������ ���� colums � left ���� ����� raws � right
	// ------- � ������� ������� c raws ��� � ������ � columns ��� � �������
	// ------- � ��������� ������������� 3�3 ����������� �����, ���������� �� 
	// ------- 3�1 3D ������ ������ 3�1 3D ������ - �������� ������� ���� ��������
	// ------- ������������ ������� ������� ��������� �� ������
	Matrix Multiply(const Matrix& left, const Matrix& right);
	bool Multiplyable(const Matrix& left, const Matrix& right);
	double GetMultiplyElement(const Matrix& left, const Matrix& right, int r, int c);

	bool operator==(const Matrix& left, const Matrix& right);
}// namespace orland