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

	float linearDamping;  //선형 운동 댐핑 : 0.9
	float angularDamping;  //회전 운동 댐핑 : 0.9

	//선형 운동을 위한 변수
	cyclone::Vector3 position;
	cyclone::Vector3 velocity;
	cyclone::Vector3 acceleration;
	cyclone::Vector3 forceAccum;  //힘 (선형운동)
	float mass;  //질량 
	float inverseMass;  // 1.0/질량

	cyclone::Particle * m_particle;
	

	void update(float duration);
	void draw(int shadow);
	void addTorque(cyclone::Vector3 force, cyclone::Vector3 point); //Point에 Force를 적용

	cyclone::Vector3 getPointInWorldSpace(const cyclone::Vector3 &point); //transformMatrix로 point를 변환 
	void addForceAtBodyPoint(const cyclone::Vector3 &force, const cyclone::Vector3 &point); //body의 point에 force를 적용

	
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
