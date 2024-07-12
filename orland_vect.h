#pragma once

/*************************************************/
/* ГС - Геометрический смысл                     */
/*************************************************/

namespace orland {

	const double RAD = 57.295779; // радиан - количество радиусов, которое пройдешь вдоль окружности, заданной углом
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

		// --- Получить декартовый вектор из полярного
		// --- ГС: длина вектора - гипотинуза образованного с осями треугольника
		// ------- коорд. x - это катет, кот. можно найти через косинус угла вектора
		// ------- коорд. y - катет через синус
		Vector2D(const PolarVector& polar_vec);

		// --- Длина 2D вектора
		// --- ГС: вектор расскладывается на компоненты x и y
		// ------- из которых состоит и по т.Пифагора считаем
		double Length() const;

		// --- Скалярное произведение
		// --- ГС: каждая коорд. умножается на скаляр - мастштабирование вектора
		// ------- сохраняя соотношение сторон
		void Scale(double scalar);
		Vector2D Scale(double scalar) const;

		// --- Получить противоположный вектор
		// --- ГС: Вектор, противоположный текущему, с той же длиной
		// ------- но противоположными коорд.
		void Reverse();
		Vector2D Reverse() const;

		// --- Сметисть на вектор
		// --- ГС: к концу исходного вектора прибавляется right
		// ------- и новые координаты представляют собой смещение
		void Move(const Vector2D& right);
		
		// --- Вычитание векторов
		// --- ГС: вычесть из left вектор right, это то же самое
		// ------- что к left прибавить -right. Тогда итоговый вектор
		// ------- идет из начала -right (конца right) к концу left
		// ------- и показывает направление и величину смещения из
		// ------- right в left
		void Subtract(const Vector2D& right);
		

		// --- Поворот вектора на угол в градусах
		// --- ГС: переводим в радианый тип, сдвигаем на угол
		// ------- преобразуем обратно
		void Rotate(double angle);

		// --- Поворот вектора на угол в радианах
		void RadRotate(double rad_angle);

		double GetX() const;
		double GetY() const;

		// --- Скалярное произведение векторов
		// --- ГС: возвращает скаляр, который оценивает сонаправленность
		// ------- исходного вектора и other
		// ------- если +, то сонаправлены
		// ------- если -, то противоположнонаправлены
		// ------- если 0, то перпендикулярны
		double Scalar(const Vector2D& other) const;
		COMMON_DIR DirStatuc(const Vector2D& other) const;

		// --- Определить угол между двумя векторами в градусах
		// --- ГС: косинус угла определяется как отношение скалярного произведения
		// ------- к произведению длин векторов 
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

		// --- Перевести градусы в радианы
		// --- Градус * Pi / 180
		double GetRadianAngle() const;

		void Rotate(double angle);

		double GetLength() const;
		double GetAngle() const;
				
	private:
		double length_ = 0.;
		double angle_ = 0.;
		
	};

	// --- Сложение двух 2D векторов --- //
	// --- ГС: из конца left проводится параллельно перенесенный right (пусть right')
	// ------- а итоговый вектор суммы - соединение начала left и конца right'
	// ------- и right' показывает направление и расстояние до конечной точки
	// ------- это правило треугольника
	Vector2D operator+(const Vector2D& left, const Vector2D& right);

	// --- Вычитание двух 2D векторов
	// --- Аналог Vector2D::Substratc(right)
	Vector2D operator-(const Vector2D& left, const Vector2D& right);

	// --- Равенство двух 2D векторов --- //
	bool operator==(const Vector2D& left, const Vector2D& right);
	bool operator!=(const Vector2D& left, const Vector2D& right);

	// --- Равенство двух полярных векторов --- //
	bool operator==(const PolarVector& left, const PolarVector& right);
	bool operator!=(const PolarVector& left, const PolarVector& right);

	

	// --- Получить противоположный вектор
	Vector2D GetReverse(const Vector2D& other);

	// --- Расстояние между двумя точками
	double Distance(const Vector2D& start, const Vector2D& finish);

	// --- Перевести радианый угол в градусный
	double RadToGrad(double rad_angle);

}// namespace orland