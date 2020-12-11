#include "Fire.h"
#include <math.h>



Fire::Fire(int type)
{
	static cyclone::Random crandom;

	m_particle.setPosition(0, 10, 0); // �ʱ���ġ
	m_particle.setVelocity(0, 0, 0); // �ʱ� �ӵ�
	m_particle.setMass(1.0f); // ����
	m_particle.setDamping(0.99f); // ����
	m_particle.setAcceleration(cyclone::Vector3::GRAVITY); // �ʱ� ���ӵ�
	m_color = cyclone::Vector3(1.0f, 0.0f, 0.0f); // �ʱ� ����
	m_size = 0.5;
	m_type = type;
}


Fire::~Fire()
{
}

bool Fire::update(float duration) {
	m_particle.integrate(duration);
	m_age -= duration;

	if (m_particle.getPosition().y + m_size <= 0 || m_age <= 0) {
		return true;
	}
	else {
		return false;
	}
}

void Fire::draw(int shadow) {
	cyclone::Vector3 position;
	m_particle.getPosition(&position); // ���� ��ƼŬ�� ��ġ�� ����

	if (shadow) {
		glColor4f(0.3f, 0.3f, 0.3f, 0.8f);
	}
	else {
		glColor3f(m_color.x, m_color.y, m_color.z);
	}
	glPushMatrix();
	glTranslatef(position.x, position.y, position.z); // ��ġ ����
	glutSolidSphere(m_size, 30, 30); // �� ����
	glPopMatrix();

	drawHistory();
}

void Fire::drawHistory() {
	glLineWidth(1.0f);
	glPushMatrix();

	glBegin(GL_LINE_STRIP);
	for (unsigned int i = 0; i < m_history.size(); i += 1) {
		cyclone::Vector3 pos = m_history[i];
		glVertex3f(pos.x, pos.y, pos.z);
	}
	glEnd();
	glPopMatrix();
	glLineWidth(1.0f);

	putHistory();
}

void Fire::setRule(FireworksRule* r) {
	m_rule = r;
}

void Fire::putHistory() {
	if (m_history.size() < 10) { //���� ���ǿ� �´ٸ�..
		m_history.push_back(m_particle.getPosition()); // pos�� ������ ����
	}
	else {
		m_history.pop_front();  //m_history���� ���� ��
	}
}