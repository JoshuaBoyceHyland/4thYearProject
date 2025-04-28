#pragma once
#include "Behaviour.h"
class Attack : public Behaviour
{
	// Inherited via Behaviour
	void update(float t_deltaTime) override;
	void reachedTarget() override;
};

