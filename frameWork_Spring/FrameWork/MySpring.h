#pragma once

#include "cyclone.h"

class Myspring : public cyclone::ParticleForceGenerator
{
	cyclone::Particle *other; // �������� ����� ��ƼŬ
	double springConstan; // ������ ���
	double restLength; // lest ����
public:
	Myspring(cyclone::Particle * p, double springConstant, double restLenght);
	virtual void updateForce(cyclone::Particle * p, double duration);
};