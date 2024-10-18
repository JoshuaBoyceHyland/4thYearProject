#pragma once

#include "raylib.h"
#include "raymath.h"  
#include "Dimesnions.h"

class CollisionChecker
{
	public:

		Vector3 m_position;
		float m_rotation;


		bool haveCollided(Vector3 t_position1, Dimensions t_dimension1, Vector3 t_position2, Dimensions t_dimension2);

};

