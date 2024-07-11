#include "vector_massiv.h"

namespace orland {
	
	Desk2D::Rotate(double angle) {
		for (Vector2D& vec : desk_) {
			vec.RotateAll(angle);
		}
	}
} //namespace orland