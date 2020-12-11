#pragma once

#include "cyclone.h"

class  MyAnchoredSpring : public cyclone::ParticleForceGenerator {
protected:
	cyclone::Vector3 *anchor; // �������� ���� ��ġ
	double springConstant; // ������ ���
	double restLength; // rest ����

public:
	MyAnchoredSpring();
	MyAnchoredSpring(cyclone::Vector3 *anchor, double springConstant, double restLength);
	const cyclone::Vector3* getAnchor() const { return anchor; } // ��Ŀ ��ġ ��ȯ �Լ�
	void init(cyclone::Vector3 *anchor, double springConstant, double restLength); // �� ���� �Լ�
	virtual void updateForce(cyclone::Particle *particle, cyclone::real duration);
};