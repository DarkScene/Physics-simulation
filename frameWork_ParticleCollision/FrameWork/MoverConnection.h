#pragma once

#include "cyclone.h"
#include "mover.h"

class MoverConnection
{
public:
	MoverConnection();
	~MoverConnection();
	cyclone::ParticleGravity * m_gravity;
	cyclone::ParticleForceRegistry * m_force;
	std::vector<mover *>m_movers;
	void update(float duration);
	void draw(int shadow);
};