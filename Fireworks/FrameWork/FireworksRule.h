#pragma once

#include <deque>
#include "particle.h"
#include "cyclone.h"

class FireworksRule {
public:
	FireworksRule();
	~FireworksRule();

	unsigned m_type; // Fire�� Ÿ��
	cyclone::real m_minAge; // Fire�� �ּ� ����
	cyclone::real m_maxAge; // Fire�� �ִ� ����
	cyclone::Vector3 m_minVelocity; // Fire�� �ּ� �ӵ�
	cyclone::Vector3 m_maxVelocity; // Fire�� �ִ� �ӵ�
	cyclone::Vector3 m_Velocity; // ������� Fire�� �ӵ�
	cyclone::real m_damping; // Fire�� ����

	float m_VelocityScalar; // ������� Fire�� �ӵ��� Scalar ��

	unsigned payloadCount; // child Fire�� �����ϴ� ����

	float getVelocityScalar(cyclone::Vector3 vector); // ������ ��Į�� ���� �������� �Լ�
	cyclone::Vector3 getSameScalarVelocity(); // Scalar���� �����ϵ��� ���Ͱ��� ���� ���ִ� �Լ�
	void setParameters(unsigned type, cyclone::real minAge, cyclone::real maxAge, const cyclone::Vector3 &minVelocity, const cyclone::Vector3 &maxVelocity, float VelocityScalar, cyclone::real damping, int count);
	
};