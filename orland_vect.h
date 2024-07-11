#pragma once

/*************************************************/
/* �� - �������������� �����                     */
/*************************************************/

namespace orland {

	const double RAD = 57.295779; // ������ - ���������� ��������, ������� �������� ����� ����������, �������� �����
	const double Pi = 3.1415926535;
	const double twoPi = 2 * Pi;
	const double Dopusk = 0.001;

	class PolarVector;

	class Vector2D {
	public:
		Vector2D() = default;
		Vector2D(double x, double y);

		void operator=(const Vector2D& other);

		// --- �������� ���������� ������ �� ���������
		// --- ��: ����� ������� - ���������� ������������� � ����� ������������
		// ------- �����. x - ��� �����, ���. ����� ����� ����� ������� ���� �������
		// ------- �����. y - ����� ����� �����
		Vector2D(const PolarVector& polar_vec);

		// --- ����� 2D �������
		// --- ��: ������ ��������������� �� ���������� x � y
		// ------- �� ������� ������� � �� �.�������� �������
		double Length() const;

		// --- ��������� ������������
		// --- ��: ������ �����. ���������� �� ������ - ���������������� �������
		// ------- �������� ����������� ������
		void Sclar(double scalar);
		Vector2D Sclar(double scalar) const;

		// --- ��������� ������� � �������
		// --- ������ * Pi / 180
		double GetRadianAngle() const;

		// --- �������� ��������������� ������
		// --- ��: ������, ��������������� ��������, � ��� �� ������
		// ------- �� ���������������� �����.
		void Reverse();
		Vector2D Reverse() const;

		// --- ��������� ��������
		// --- ��: ������� �� left ������ right, ��� �� �� �����
		// ------- ��� � left ��������� -right. ����� �������� ������
		// ------- ���� �� ������ -right (����� right) � ����� left
		// ------- � ���������� ����������� � �������� �������� ��
		// ------- right � left
		void Subtract(const Vector2d& left);

		// --- ������� ������� �� ���� � ��������
		// --- ��: ��������� � �������� ���, �������� �� ����
		// ------- ����������� �������
		void Rotate(double angle);

		// --- ������� ������� �� ���� � ��������
		void RadRotate(double angle);


	private:
		double x = 0.;
		double y = 0.;
	};

	class PolarVector {
	public:
				
		PolarVector() = default;
		PolarVector(double length, double angle = 0.);
		PolarVector(const Vector2D& dec_vector);

		double GetCommonAngle() const;

		void Rotate(double angle);
				
	private:
		double length_ = 0.;
		double angle_ = 0.;
		
	};

	// --- �������� ���� 2D �������� --- //
	// --- ��: �� ����� left ���������� ����������� ������������ right (����� right')
	// ------- � �������� ������ ����� - ���������� ������ left � ����� right'
	// ------- � right' ���������� ����������� � ���������� �� �������� �����
	// ------- ��� ������� ������������
	Vector2D operator+(const Vector2D& left, const Vector2D& right);

	// --- ��������� ���� 2D ��������
	// --- ������ Vector2D::Substratc(right)
	Vector2D operator-(const Vector2D& left, const Vector2D& right);

	// --- ��������� ���� 2D �������� --- //
	bool operator==(const Vector2D& left, const Vector2D& right);

	// --- ��������� ���� �������� �������� --- //
	bool operator==(const PolarVector& left, const PolarVector& right);

	// --- �������� ��������������� ������
	Vector2D GetReverse(const Vector2D& other);

}// namespace orland