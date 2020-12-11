#include "mover.h"



mover::mover()
{
	m_particle.setPosition(5, 5, 5); // �ʱ���ġ
	m_particle.setVelocity(0, 0, 0); // �ʱ� �ӵ�
	m_particle.setMass(5.0f); // ����
	m_particle.setDamping(0.7f); // ����
	m_particle.setAcceleration(cyclone::Vector3(0, 0, 0)); // �ʱ� ���ӵ�
	m_color = cyclone::Vector3(1.0f, 0.0f, 0.0f); // �ʱ� ����
	m_gravity = new cyclone::ParticleGravity(cyclone::Vector3(0, -10, 0));
	m_drag = new cyclone::ParticleDrag(0.1, 0.1);
	m_forces = new cyclone::ParticleForceRegistry();
	m_buoyancy = new MyParticleBuoyancy(1, 1, 10, 2);

	//m_forces->add(&m_particle, m_gravity);
	m_forces->add(&m_particle, m_buoyancy);
}


mover::~mover()
{
}

void mover::update(float duration) {
	m_buoyancy->updateForce(&m_particle, duration);
	m_forces->updateForces(duration);
	m_particle.integrate(duration);
}

void mover::stop() {

}

void mover::draw(int shadow) {
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
	glutSolidSphere(3.0, 30, 30); // �� ����
	glPopMatrix();
}
