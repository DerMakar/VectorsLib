#include "vector_massiv.h"

namespace orland {
	
	void Object::RotateAll(double angle) {
		for (Vector2D& vec : desk_) {
			vec.Rotate(angle);
		}
	}

	void Object::MoveAll(const Vector2D& move) {
		for (Vector2D& vec : desk_) {
			vec.Move(move);
		}
	}
} //namespace orland

//Например правильный многоугольник можно построить поворотов исходного 
// вектора(1, 0) против часовой стрелки, сдвигая n (число углов) раз на 2*pi*k/n угол

/*
Рассчитывая нормаль и сравнивая с вектором взгляда можно определять видимость и освещенность объекта для смотрящего. 
Если нормаль перпендикулярна к вектору взгляда наблюдателя, то он не видит образованную фигуру.
*/