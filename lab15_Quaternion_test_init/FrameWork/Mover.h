#pragma once

#include "core.h"
#include "particle.h"
#include "pfgen.h"


#include "MySpring.h"



class Mover
{
public:
	Mover(cyclone::Vector3 &p);
	~Mover();
	cyclone::Matrix4 transformMatrix;
	cyclone::Vector3 rotation;  //°¢¼Óµµ
	cyclone::Quaternion orientation;

	cyclone::Particle * m_particle;
	

	void update(float duration);
	void draw(int shadow);
	
	void getGLTransform(float matrix[16]);


};


class MoverConnection
{
public:
	MoverConnection();
	~MoverConnection();

	std::vector<Mover *> m_movers;
	void update(float duration);
	void draw(int shadow);

};
