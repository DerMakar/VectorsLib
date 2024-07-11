#pragma once

/*************************************************/
/* ГС - Геометрический смысл                     */
/*************************************************/

namespace orland {

	const double RAD = 57.295779; // радиан - количество радиусов, которое пройдешь вдоль окружности, заданной углом
	const double Pi = 3.1415926535;
	const double twoPi = 2 * Pi;
	const double Dopusk = 0.001;

	class PolarVector;

	class Vector2D {
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
		void Sclar(double scalar);
		Vector2D Sclar(double scalar) const;

		// --- Перевести градусы в радианы
		// --- Градус * Pi / 180
		double GetRadianAngle() const;

		// --- Получить противоположный вектор
		// --- ГС: Вектор, противоположный текущему, с той же длиной
		// ------- но противоположными коорд.
		void Reverse();
		Vector2D Reverse() const;

		// --- Вычитание векторов
		// --- ГС: вычесть из left вектор right, это то же самое
		// ------- что к left прибавить -right. Тогда итоговый вектор
		// ------- идет из начала -right (конца right) к концу left
		// ------- и показывает направление и величину смещения из
		// ------- right в left
		void Subtract(const Vector2d& left);

		// --- Поворот вектора на угол в градусах
		// --- ГС: переводим в радианый тип, сдвигаем на угол
		// ------- преобразуем обратно
		void Rotate(double angle);

		// --- Поворот вектора на угол в радианах
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

	// --- Равенство двух полярных векторов --- //
	bool operator==(const PolarVector& left, const PolarVector& right);

	// --- Получить противоположный вектор
	Vector2D GetReverse(const Vector2D& other);

}// namespace orland