#pragma once

#include "cyclone.h"

class Myspring : public cyclone::ParticleForceGenerator
{
	cyclone::Particle *other; // 스프링이 적용될 파티클
	double springConstan; // 스프링 상수
	double restLength; // lest 길이
public:
	Myspring(cyclone::Particle * p, double springConstant, double restLenght);
	virtual void updateForce(cyclone::Particle * p, double duration);
};