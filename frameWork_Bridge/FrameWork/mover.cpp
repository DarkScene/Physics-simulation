#include "mover.h"



mover::mover(cyclone::Vector3 &p)
{
	m_particle.setPosition(p.x, p.y, p.z); // 초기위치
	m_particle.setVelocity(0, 0, 0); // 초기 속도
	m_particle.setMass(5.0f); // 질량
	m_particle.setDamping(0.8f); // 댐핑
	m_particle.setAcceleration(cyclone::Vector3::GRAVITY); // 초기 가속도
	m_color = cyclone::Vector3(1.0f, 0.0f, 0.0f); // 초기 색상
	
	//m_gravity = new cyclone::ParticleGravity(cyclone::Vector3(0, -10, 0));
	//m_drag = new cyclone::ParticleDrag(0.1, 0.1);
	//m_forces = new cyclone::ParticleForceRegistry();

	//m_forces->add(&m_particle, m_gravity);
	//m_forces->add(&m_particle, m_drag);
}


mover::~mover()
{
}

void mover::update(float duration) {
	//m_spring->updateForce(&m_particle, duration);
	//m_forces->updateForces(duration);
	m_particle.integrate(duration);
}

void mover::stop() {

}

void mover::draw(int shadow) {
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
	glutSolidSphere(0.3, 30, 30); // 구 생성
	glPopMatrix();
}