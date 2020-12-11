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
	cyclone::Vector3 rotation;  //각속도
	cyclone::Quaternion orientation;

	cyclone::Matrix3 inverseInertiaMatrix;  //local Inertia 행렬의 역행렬
	cyclone::Vector3 torqueAccum;  //Torque 저장
	cyclone::Matrix3 inverseInertiaTensorWorld; //local Inertia 역행렬의 world변환

	cyclone::Particle * m_particle;
	

	void update(float duration);
	void draw(int shadow);
	void addTorque(cyclone::Vector3 force, cyclone::Vector3 point); //Point에 Force를 적용
	
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
