#pragma once

/*************************************************/
/* ГС - Геометрический смысл                     */
/*************************************************/

namespace orland {

	class Vector2D {
	public:
		Vector2D() = default;
		Vector2D(double x, double y);

		// --- Длина 2D вектора
		// --- ГС: вектор расскладывается на компоненты x и y
		// ------- из которых состоит и по т.Пифагора считаем
		double Length() const;

		// --- Скалярное произведение
		// --- ГС: каждая коорд. умножается на скаляр - мастштабирование вектора
		// ------- сохраняя соотношение сторон
		void Sclar(double scalar);
		Vector2D Sclar(double scalar) const;

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


	private:
		double x = 0.;
		double y = 0.;
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

}// namespace orland