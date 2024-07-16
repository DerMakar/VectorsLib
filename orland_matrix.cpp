#include "orland_matrix.h"
#include <cassert>
#include <cmath>
namespace orland {
	Matrix::Matrix(int raws, int columns) {
		std::vector<std::vector<double>> tmp(raws + 1, std::vector<double>(columns + 1, 0.));
		matrix_ = std::move(tmp);
	}

	Matrix::Matrix(const std::vector<Vector3D>& vectors3d) {
		size_t size_ = vectors3d.size();
		if (size_ > 0) {
			std::vector<std::vector<double>> tmp(4, std::vector<double>(size_ + 1, 0.));
			for (int col = 1; col <= size_; col++) {
				tmp[1][col] = vectors3d[col-1].GetX();
				tmp[2][col] = vectors3d[col-1].GetY();
				tmp[3][col] = vectors3d[col-1].GetZ();
			}
			matrix_ = std::move(tmp);
		}
	}

	void Matrix::AddElement(int raw, int column, double value) {
		assert(ValidAdr(raw, column));
		matrix_[raw][column] = value;
	}

	std::pair<int, int> Matrix::GetDimension() const {
		int columns = 0;
		int raws = matrix_.size();
		if (raws > 0) {
			raws--;
			columns = matrix_[0].size();
			if(columns > 0) columns--;
		}
		return std::make_pair(raws, columns);
	}

	bool Matrix::ValidAdr(int raw, int column) const {
		return (raw > 0 && (raw < matrix_.size())) && (column > 0 && (column < matrix_[0].size()));
	}

	Matrix GetStandart3D() {
		Matrix matrix(3, 3);
		for (int i = 1, j = 1; i < 4; i++, j++) {
			matrix.AddElement(i, j, 1.);
		}
		return matrix;
	}

	double Matrix::GetElement(int raw, int column) const {
		assert(ValidAdr(raw, column));
		return matrix_[raw][column];
	}

	const std::vector<std::vector<double>>& Matrix::GetMatrix() const {
		return matrix_;
	}

	Matrix Multiply(const Matrix& left, const Matrix& right) {
		const auto [lr, lc] = left.GetDimension();
		const auto [rr, rc] = right.GetDimension();
		if (lc == rr) {
			Matrix result(lr, rc);
			for (int r = 1; r <= lr; r++) {
				for (int c = 1; c <= rc; c++) {
					double res = GetMultiplyElement(left, right, r, c);
					result.AddElement(r, c,res);
				}
			}
			return result;
		}
		return {};
	}

	double GetMultiplyElement(const Matrix& left, const Matrix& right, int r, int c) {
		double res = 0.;
		const auto [raws, columns] = left.GetDimension();
		for (int c_i = 1, r_i = 1; c_i <= columns; c_i++, r_i++) {
			res += left.GetElement(r, c_i) * right.GetElement(r_i, c);
		}
		return res;
	}

	bool Multiplyable(const Matrix& left, const Matrix& right) {
		const auto [lr, lc] = left.GetDimension();
		const auto [rr, rc] = right.GetDimension();
		return lc == rr;
	}

	bool operator==(const Matrix& left, const Matrix& right) {
		const auto [lr, lc] = left.GetDimension();
		const auto [rr, rc] = right.GetDimension();
		if (lr == rr && lc == rc) {
			for (int r = 1; r <= lr; r++) {
				for (int c = 1; c <= lc; c++) {
					if (std::abs(left.GetElement(r, c) - right.GetElement(r, c)) > 0.0001) return false;
				}
			}
			return true;
		}
		return false;
	}
}// namespace orland