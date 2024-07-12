#pragma once

/*************************************************/
/* �� - �������������� �����                     */
/*************************************************/

namespace orland {

	const double RAD = 57.295779; // ������ - ���������� ��������, ������� �������� ����� ����������, �������� �����
	const double Pi = 3.1415926535;
	const double twoPi = 2 * Pi;
	const double Dopusk = 0.0001;

	class PolarVector;

	class Vector2D {
	public:
		enum class COMMON_DIR {
			NEGATIVE_ON_LINE = -2
			, NEGATIVE = -1
			, PERPENDICULAR = 0
			, POSITIVE = 1
			, POSITIVE_ON_LINE = 2
		};

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
		void Scale(double scalar);
		Vector2D Scale(double scalar) const;

		// --- �������� ��������������� ������
		// --- ��: ������, ��������������� ��������, � ��� �� ������
		// ------- �� ���������������� �����.
		void Reverse();
		Vector2D Reverse() const;

		// --- �������� �� ������
		// --- ��: � ����� ��������� ������� ������������ right
		// ------- � ����� ���������� ������������ ����� ��������
		void Move(const Vector2D& right);
		
		// --- ��������� ��������
		// --- ��: ������� �� left ������ right, ��� �� �� �����
		// ------- ��� � left ��������� -right. ����� �������� ������
		// ------- ���� �� ������ -right (����� right) � ����� left
		// ------- � ���������� ����������� � �������� �������� ��
		// ------- right � left
		void Subtract(const Vector2D& right);
		

		// --- ������� ������� �� ���� � ��������
		// --- ��: ��������� � �������� ���, �������� �� ����
		// ------- ����������� �������
		void Rotate(double angle);

		// --- ������� ������� �� ���� � ��������
		void RadRotate(double rad_angle);

		double GetX() const;
		double GetY() const;

		// --- ��������� ������������ ��������
		// --- ��: ���������� ������, ������� ��������� ����������������
		// ------- ��������� ������� � other
		// ------- ���� +, �� ������������
		// ------- ���� -, �� ������������������������
		// ------- ���� 0, �� ���������������
		double Scalar(const Vector2D& other) const;
		COMMON_DIR DirStatuc(const Vector2D& other) const;

		// --- ���������� ���� ����� ����� ��������� � ��������
		// --- ��: ������� ���� ������������ ��� ��������� ���������� ������������
		// ------- � ������������ ���� �������� 
		double GetBetweenAngle(const Vector2D& other) const;


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

		// --- ��������� ������� � �������
		// --- ������ * Pi / 180
		double GetRadianAngle() const;

		void Rotate(double angle);

		double GetLength() const;
		double GetAngle() const;
				
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
	bool operator!=(const Vector2D& left, const Vector2D& right);

	// --- ��������� ���� �������� �������� --- //
	bool operator==(const PolarVector& left, const PolarVector& right);
	bool operator!=(const PolarVector& left, const PolarVector& right);

	

	// --- �������� ��������������� ������
	Vector2D GetReverse(const Vector2D& other);

	// --- ���������� ����� ����� �������
	double Distance(const Vector2D& start, const Vector2D& finish);

	// --- ��������� �������� ���� � ���������
	double RadToGrad(double rad_angle);

}// namespace orland