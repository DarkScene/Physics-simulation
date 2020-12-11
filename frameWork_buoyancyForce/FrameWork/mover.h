#pragma once

#include <GL/glut.h>
#include "core.h"
#include "cyclone.h"
#include "pfgen.h"
#include "MyParticleBuoyancy.h"

class mover
{
public:
	mover();
	~mover();

	MyParticleBuoyancy* m_buoyancy;
	cyclone::Particle m_particle;
	cyclone::Vector3 m_color;
	cyclone::ParticleGravity* m_gravity;
	cyclone::ParticleDrag* m_drag;
	cyclone::ParticleForceRegistry* m_forces;

	void update(float duration);
	void stop();
	void draw(int shadow);
};

