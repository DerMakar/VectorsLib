#pragma once

/*************************************************/
/* �� - �������������� �����                     */
/*************************************************/

namespace orland {

	class Vector2D {
	public:
		Vector2D() = default;
		Vector2D(double x, double y);

		// --- ����� 2D �������
		// --- ��: ������ ��������������� �� ���������� x � y
		// ------- �� ������� ������� � �� �.�������� �������
		double Length() const;

		// --- ��������� ������������
		// --- ��: ������ �����. ���������� �� ������ - ���������������� �������
		// ------- �������� ����������� ������
		void Sclar(double scalar);
		Vector2D Sclar(double scalar) const;

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


	private:
		double x = 0.;
		double y = 0.;
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

}// namespace orland