#pragma once

#include <deque>
#include "particle.h"
#include "cyclone.h"

class FireworksRule {
public:
	FireworksRule();
	~FireworksRule();

	unsigned m_type; // Fire의 타입
	cyclone::real m_minAge; // Fire의 최소 수명
	cyclone::real m_maxAge; // Fire의 최대 수명
	cyclone::Vector3 m_minVelocity; // Fire의 최소 속도
	cyclone::Vector3 m_maxVelocity; // Fire의 최대 속도
	cyclone::Vector3 m_Velocity; // 결과적인 Fire의 속도
	cyclone::real m_damping; // Fire의 댐핑

	float m_VelocityScalar; // 결과적인 Fire의 속도의 Scalar 값

	unsigned payloadCount; // child Fire를 생성하는 개수

	float getVelocityScalar(cyclone::Vector3 vector); // 벡터의 스칼라 값을 가져오는 함수
	cyclone::Vector3 getSameScalarVelocity(); // Scalar값이 일정하도록 벡터값을 지정 해주는 함수
	void setParameters(unsigned type, cyclone::real minAge, cyclone::real maxAge, const cyclone::Vector3 &minVelocity, const cyclone::Vector3 &maxVelocity, float VelocityScalar, cyclone::real damping, int count);
	
};