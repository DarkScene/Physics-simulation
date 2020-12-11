#include "Fire.h"
#include <math.h>



Fire::Fire(int type)
{
	static cyclone::Random crandom;

	m_particle.setPosition(0, 10, 0); // 초기위치
	m_particle.setVelocity(0, 0, 0); // 초기 속도
	m_particle.setMass(1.0f); // 질량
	m_particle.setDamping(0.99f); // 댐핑
	m_particle.setAcceleration(cyclone::Vector3::GRAVITY); // 초기 가속도
	m_color = cyclone::Vector3(1.0f, 0.0f, 0.0f); // 초기 색상
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
	m_particle.getPosition(&position); // 현재 파티클의 위치를 얻음

	if (shadow) {
		glColor4f(0.3f, 0.3f, 0.3f, 0.8f);
	}
	else {
		glColor3f(m_color.x, m_color.y, m_color.z);
	}
	glPushMatrix();
	glTranslatef(position.x, position.y, position.z); // 위치 변경
	glutSolidSphere(m_size, 30, 30); // 구 생성
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
	if (m_history.size() < 10) { //만일 조건에 맞다면..
		m_history.push_back(m_particle.getPosition()); // pos의 정보를 저장
	}
	else {
		m_history.pop_front();  //m_history에서 삭제 함
	}
}