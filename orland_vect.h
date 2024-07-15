#pragma once

/*************************************************************/
/* �� - �������������� �����								 */
/* �������� ��������������(��) - ��� ��������� ��������������*/
/*   �, ����������� ��������� ����� � ��������� ���������    */
/*   �� ������. T(u) + T(v) = T(u + v) � T(sv) = s T(v)		 */
/*															 */
/* �������� ���������� ������ �������� ��� ������			 */
/*  ������������ �������� �� �������. 0.5u+0.5v = 0.5(u + v) */
/*************************************************************/


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

		// --- ��������� �� ������ 
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

	class Vector3D {
	public:
		enum class DIR_STATUS_3D {
			  RANDOM = 0
			, PARALLEL = 1
			, PERPENDICULAR = 2
		};

	public:
		Vector3D() = default;
		Vector3D(double x, double y, double z);

		void operator=(const Vector3D& other);

		// --- ����� 3D �������
		// --- ��: ������ ��������������� �� ���������� x, y � z
		// ------- �� ������� ������� � �� �.�������� �������
		double Length() const;

		// --- ��������� �� ������ 
		void Scale(double scalar);
		Vector3D Scale(double scalar) const;

		// --- �������� ��������������� ������
		void Reverse();
		Vector3D Reverse() const;

		// --- �������� �� ������
		void Move(const Vector3D& right);

		// --- ��������� ��������
		void Subtract(const Vector3D& right);


		double GetX() const;
		double GetY() const;
		double GetZ() const;

		// --- ��������� ������������ ��������
		double Scalar(const Vector3D& other) const;
		Vector2D::COMMON_DIR DirStatus(const Vector3D& other) const;

		// --- ���������� ���� ����� ����� ��������� � ��������
		double GetBetweenAngle(const Vector3D& other) const;

		// --- ������������ ��������
		// --- ��: ���������� 3D ������, ���������������� �����
		// ------- ���������� ������� ������ ����, ��� ������������(this)
		// ------- �������� ������� (other) � ������������ - �������
		Vector3D Normal(const Vector3D& other) const;

		// --- ������� ������������������ 3D ��������
		// --- ��: ����� ���������� ������������ (��) - ��� ������� ������������������
		// ------- ��� ����� ������� ���������������, ������� �������� ��� �������
		// ------- ������� �����������, ����� ������� ���������������
		// ------- ���� ����� �� ������� - ������� �����������
		DIR_STATUS_3D Dir3DStatus(const Vector3D& other) const; // ��� �������� ������ ��� ������� ��������?

		// --- ����� ������� ���������������, ������������� ����� ���������
		// --- ��: ������� ��������������� - ������������ ��������� �� ������
		// ------- ������ ������� ��� ���������� (����� this), ���������� �� sin ����
		// ------- ����� ���������
		double SquareBetween(const Vector3D& other) const;

		// --- �������� ��������� ������ ��� ���������
		// --- ��: ������������ ������ ���������� �� ����� ��������� �������
		// ------- � �������� ������������� ��� ��������� ��������
		// ------- ����� ������ ������� == 1
		Vector3D GetSingular() const;

		// --- ��������� 3D ������ ������ ��� Ox (Oy, Oz)
		// --- ���� angle � ��������. >0 - �� ������� �������, ���� ��������
		// --- �� ������� �������������� ����������� ��� Ox (Oy, Oz)
		// --- ��: ���������� � (y,z) 3D ������� �������� ����������
		// ------- ������������ �������� 2D ������ � Y Z (X Z, X Y) ������������ �� angle
		// ------- � �� ��� ������ 3D ���������� ����������� �������, ������� � (Y, Z) const
		void TurnAroundX(double angle);
		void TurnAroundY(double angle);
		void TurnAroundZ(double angle);

		// --- ����� ����� ����� ����� ��������� �� part ���� ����������
		// --- ����� �������� � other
		// --- ��: �� ������� ��������� �������������� ����� �������
		// ------- ���� �������� su + (1-s)v
		// ------- part ����������� � �������� �� 0 �� 1
		Vector3D GetPointBetween(double part, const Vector3D& other) const;

	private:
		double x = 0.;
		double y = 0.;
		double z = 0.;
	};

	class SpheericVector3D {
	public:
			SpheericVector3D() = default;
			SpheericVector3D(double r, double fi, double teta)
				: r_(r), fi_(fi), teta_(teta) {
			}
	private:
		double r_ = 0.; // ����� �������
		double fi_ = 0.; // ���� � �������� ���� ������� �� XY ��������� � +0�
		double teta_ = 0.; // ���� � �������� ������� � +0z
	};

	// --- �������� ���� 2D �������� --- //
	// --- ��: �� ����� left ���������� ����������� ������������ right (����� right')
	// ------- � �������� ������ ����� - ���������� ������ left � ����� right'
	// ------- � right' ���������� ����������� � ���������� �� �������� �����
	// ------- ��� ������� ������������
	Vector2D operator+(const Vector2D& left, const Vector2D& right);
	Vector3D operator+(const Vector3D& left, const Vector3D& right);

	// --- ��������� ���� 2D ��������
	// --- ������ Vector2D::Substratc(right)
	Vector2D operator-(const Vector2D& left, const Vector2D& right);

	// --- ��������� ���� 2D �������� --- //
	bool operator==(const Vector2D& left, const Vector2D& right);
	bool operator!=(const Vector2D& left, const Vector2D& right);
	bool operator==(const Vector3D& left, const Vector3D& right);
	bool operator!=(const Vector3D& left, const Vector3D& right);

	// --- ��������� ���� �������� �������� --- //
	bool operator==(const PolarVector& left, const PolarVector& right);
	bool operator!=(const PolarVector& left, const PolarVector& right);

	

	// --- �������� ��������������� ������
	Vector2D GetReverse(const Vector2D& other);

	// --- ���������� ����� ����� �������
	double Distance(const Vector2D& start, const Vector2D& finish);

	// --- ��������� �������� ���� � ���������
	double RadToGrad(double rad_angle);

	// --- ��������� ��������� ���� � �������
	double GradToRad(double grad_angle);

}// namespace orland