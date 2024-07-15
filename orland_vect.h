#pragma once

/*************************************************************/
/* ГС - Геометрический смысл								 */
/* Линейное преобразование(ЛП) - это векторное преобразование*/
/*   Т, сохраняющее векторную сумму и результат умножения    */
/*   на скаляр. T(u) + T(v) = T(u + v) и T(sv) = s T(v)		 */
/*															 */
/* Линейная комбинация набора векторов это суммма			 */
/*  произвденеий векторов на скаляры. 0.5u+0.5v = 0.5(u + v) */
/*************************************************************/


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

		// --- Умножение на скаляр 
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

		// --- Длина 3D вектора
		// --- ГС: вектор расскладывается на компоненты x, y и z
		// ------- из которых состоит и по т.Пифагора считаем
		double Length() const;

		// --- Умножение на скаляр 
		void Scale(double scalar);
		Vector3D Scale(double scalar) const;

		// --- Получить противоположный вектор
		void Reverse();
		Vector3D Reverse() const;

		// --- Сметисть на вектор
		void Move(const Vector3D& right);

		// --- Вычитание векторов
		void Subtract(const Vector3D& right);


		double GetX() const;
		double GetY() const;
		double GetZ() const;

		// --- Скалярное произведение векторов
		double Scalar(const Vector3D& other) const;
		Vector2D::COMMON_DIR DirStatus(const Vector3D& other) const;

		// --- Определить угол между двумя векторами в градусах
		double GetBetweenAngle(const Vector3D& other) const;

		// --- Произведение векторов
		// --- ГС: возвращает 3D вектор, перпендикулярный обоим
		// ------- подчиняясь правилу правой руки, где указательный(this)
		// ------- согнутый средний (other) и возвращенный - большой
		Vector3D Normal(const Vector3D& other) const;

		// --- Степень перпендикулярности 3D векторов
		// --- ГС: длина векторного произведения (ВП) - это степень перпендикулярности
		// ------- она равна площади параллелограмма, которую образуют два вектора
		// ------- площадь максимальна, когда векторы перпендикулярны
		// ------- если длина ВП нулевая - векторы параллельны
		DIR_STATUS_3D Dir3DStatus(const Vector3D& other) const; // как смотреть случай при нулевых векторах?

		// --- Найти площадь параллелограмма, образованного двумя векторами
		// --- ГС: площадь параллелограмма - произведение основания на высоту
		// ------- высоту находим как гипотенуза (длина this), умноженная на sin угла
		// ------- между векторами
		double SquareBetween(const Vector3D& other) const;

		// --- Получить единичный вектор для исходного
		// --- ГС: масштабируем каждую координату на длину исходного вектора
		// ------- и получаем кооэффициенты для единичных векторов
		// ------- длина такого вектора == 1
		Vector3D GetSingular() const;

		// --- Повернуть 3D вектор вокруг оси Ox (Oy, Oz)
		// --- Угол angle в градусах. >0 - по часовой стрелке, если смотреть
		// --- со стороны положительного направления оси Ox (Oy, Oz)
		// --- ГС: координата х (y,z) 3D вектора остается неизменной
		// ------- поворачиваем полярный 2D вектор с Y Z (X Z, X Y) координатами на angle
		// ------- и по ним меняем 3D координаты повернутого вектора, оставив Х (Y, Z) const
		void TurnAroundX(double angle);
		void TurnAroundY(double angle);
		void TurnAroundZ(double angle);

		// --- Найти точку между двумя векторами на part доле расстояния
		// --- между исходным и other
		// --- ГС: из свойств линейного преобразования можно сложить
		// ------- доли векторов su + (1-s)v
		// ------- part указывается в значении от 0 до 1
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
		double r_ = 0.; // длина вектора
		double fi_ = 0.; // угол в градусах тени вектора на XY плоскость с +0х
		double teta_ = 0.; // угол в градусах вектора с +0z
	};

	// --- Сложение двух 2D векторов --- //
	// --- ГС: из конца left проводится параллельно перенесенный right (пусть right')
	// ------- а итоговый вектор суммы - соединение начала left и конца right'
	// ------- и right' показывает направление и расстояние до конечной точки
	// ------- это правило треугольника
	Vector2D operator+(const Vector2D& left, const Vector2D& right);
	Vector3D operator+(const Vector3D& left, const Vector3D& right);

	// --- Вычитание двух 2D векторов
	// --- Аналог Vector2D::Substratc(right)
	Vector2D operator-(const Vector2D& left, const Vector2D& right);

	// --- Равенство двух 2D векторов --- //
	bool operator==(const Vector2D& left, const Vector2D& right);
	bool operator!=(const Vector2D& left, const Vector2D& right);
	bool operator==(const Vector3D& left, const Vector3D& right);
	bool operator!=(const Vector3D& left, const Vector3D& right);

	// --- Равенство двух полярных векторов --- //
	bool operator==(const PolarVector& left, const PolarVector& right);
	bool operator!=(const PolarVector& left, const PolarVector& right);

	

	// --- Получить противоположный вектор
	Vector2D GetReverse(const Vector2D& other);

	// --- Расстояние между двумя точками
	double Distance(const Vector2D& start, const Vector2D& finish);

	// --- Перевести радианый угол в градусный
	double RadToGrad(double rad_angle);

	// --- Перевести градусный угол в радианы
	double GradToRad(double grad_angle);

}// namespace orland