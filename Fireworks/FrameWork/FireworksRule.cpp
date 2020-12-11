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

cyclone::Vector3 FireworksRule::getSameScalarVelocity() { // ���� �ٸ� ������ ���͵��� Scalar ���� �����ϰ� ���� ���� �������ִ� �Լ�
	static cyclone::Random crandom;

	m_Velocity = crandom.randomVector(m_minVelocity, m_maxVelocity); // ������ ���Ⱚ�� ����
	m_Velocity = cyclone::Vector3(m_Velocity.x / getVelocityScalar(m_Velocity), m_Velocity.y / getVelocityScalar(m_Velocity), m_Velocity.z / getVelocityScalar(m_Velocity)); // Vector�� Scalar������ ������ �������ͷ� ����
	m_Velocity = m_Velocity * m_VelocityScalar; // �������Ϳ� ��Į�� ���� ����

	return m_Velocity;
}