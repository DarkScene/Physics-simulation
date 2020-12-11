#include "FireworksRule.h"

FireworksRule::FireworksRule() {
}

FireworksRule::~FireworksRule() {

}

void FireworksRule::setParameters(unsigned type, cyclone::real minAge, cyclone::real maxAge, const cyclone::Vector3 &minVelocity, const cyclone::Vector3 &maxVelocity, float VelocityScalar, cyclone::real damping, int count) {
	m_type = type;
	m_minAge = minAge;
	m_maxAge = maxAge;
	m_minVelocity = minVelocity;
	m_maxVelocity = maxVelocity;
	m_VelocityScalar = VelocityScalar;
	m_damping = damping;
	payloadCount = count;
}

float FireworksRule::getVelocityScalar(cyclone::Vector3 vector) {
	float result;

	result = sqrt(pow(vector.x, 2) + pow(vector.y, 2) + pow(vector.z, 2));

	return result;
}

cyclone::Vector3 FireworksRule::getSameScalarVelocity() { // 서로 다른 방향의 벡터들의 Scalar 값을 일정하게 통일 시켜 지정해주는 함수
	static cyclone::Random crandom;

	m_Velocity = crandom.randomVector(m_minVelocity, m_maxVelocity); // 랜덤한 방향값을 구함
	m_Velocity = cyclone::Vector3(m_Velocity.x / getVelocityScalar(m_Velocity), m_Velocity.y / getVelocityScalar(m_Velocity), m_Velocity.z / getVelocityScalar(m_Velocity)); // Vector를 Scalar값으로 나누어 단위벡터로 만듬
	m_Velocity = m_Velocity * m_VelocityScalar; // 단위벡터에 스칼라 값을 곱함

	return m_Velocity;
}