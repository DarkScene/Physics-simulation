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
	cyclone::Vector3 rotation;  //���ӵ�
	cyclone::Quaternion orientation;

	cyclone::Matrix3 inverseInertiaMatrix;  //local Inertia ����� �����
	cyclone::Vector3 torqueAccum;  //Torque ����
	cyclone::Matrix3 inverseInertiaTensorWorld; //local Inertia ������� world��ȯ

	float linearDamping;  //���� � ���� : 0.9
	float angularDamping;  //ȸ�� � ���� : 0.9

	//���� ��� ���� ����
	cyclone::Vector3 position;
	cyclone::Vector3 velocity;
	cyclone::Vector3 acceleration;
	cyclone::Vector3 forceAccum;  //�� (�����)
	float mass;  //���� 
	float inverseMass;  // 1.0/����

	cyclone::Particle * m_particle;
	

	void update(float duration);
	void draw(int shadow);
	void addTorque(cyclone::Vector3 force, cyclone::Vector3 point); //Point�� Force�� ����

	cyclone::Vector3 getPointInWorldSpace(const cyclone::Vector3 &point); //transformMatrix�� point�� ��ȯ 
	void addForceAtBodyPoint(const cyclone::Vector3 &force, const cyclone::Vector3 &point); //body�� point�� force�� ����

	
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
