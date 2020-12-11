#pragma once

#include "cyclone.h"

class  MyAnchoredSpring : public cyclone::ParticleForceGenerator {
protected:
	cyclone::Vector3 *anchor; // 스프링의 고정 위치
	double springConstant; // 스프링 상수
	double restLength; // rest 길이

public:
	MyAnchoredSpring();
	MyAnchoredSpring(cyclone::Vector3 *anchor, double springConstant, double restLength);
	const cyclone::Vector3* getAnchor() const { return anchor; } // 앵커 위치 반환 함수
	void init(cyclone::Vector3 *anchor, double springConstant, double restLength); // 값 설정 함수
	virtual void updateForce(cyclone::Particle *particle, cyclone::real duration);
};