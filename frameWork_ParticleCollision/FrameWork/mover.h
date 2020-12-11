#pragma once

#include <GL/glut.h>
#include "core.h"
#include "cyclone.h"
#include "pfgen.h"
#include "MySpring.h"

class mover
{
public:
	mover(cyclone::Vector3 &p); // p : �ʱ���ġ
	~mover();

	Myspring * m_spring;
	cyclone::Particle m_particle;
	cyclone::Vector3 m_color;
	cyclone::ParticleGravity* m_gravity;
	cyclone::ParticleDrag* m_drag;
	cyclone::ParticleForceRegistry* m_forces;

	void update(float duration);
	void stop();
	void draw(int shadow);
	void setConnection(mover * a); // a : ����Ǵ� ���� mover
};

