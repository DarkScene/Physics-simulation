#pragma once

#include <GL/glut.h>
#include "core.h"

class mover
{
public:
	mover();
	~mover();

	cyclone::Vector3 m_position;

	void update();
	void stop();
	void draw(int shadow);
};

