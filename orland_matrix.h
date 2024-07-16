#pragma once
#include <vector>
#include <utility>
#include "orland_vect.h"

namespace orland {
	class Matrix {
	public:
		Matrix() = default;
		
		// --- Создать матрицу в raws строк и columns столбцов
		// --- Для удобства индексов, создается матрица размером +1 строка
		// --- и +1 столбец
		Matrix(int raws, int columns);

		// --- Создрать матрицу на основе массива 3D векторов
		Matrix(const std::vector<Vector3D>& vectors3d);

		// --- Добавляет элемент в указнную строку и столбец
		void AddElement(int raw, int column, double value);

		std::pair<int, int> GetDimension() const;

		double GetElement(int raw, int column) const;

		const std::vector<std::vector<double>>& GetMatrix() const;

	private:
		std::vector<std::vector<double>> matrix_;

		bool ValidAdr(int raw, int column) const;
	};

	Matrix GetStandart3D();

	// --- Умножение матриц
	// --- ГС: умножить можно только если colums у left было равно raws у right
	// ------- и получим матрицу c raws как у левого и columns как у правого
	// ------- в векторном представлении 3х3 стандартный базис, умноженный на 
	// ------- 3х1 3D вектор вернет 3х1 3D вектор - линейную функцию этих векторов
	// ------- произведение каждого вектора стандарта на скалар
	Matrix Multiply(const Matrix& left, const Matrix& right);
	bool Multiplyable(const Matrix& left, const Matrix& right);
	double GetMultiplyElement(const Matrix& left, const Matrix& right, int r, int c);

	bool operator==(const Matrix& left, const Matrix& right);
}// namespace orland