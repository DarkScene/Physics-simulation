#include "mover.h"



mover::mover()
{
	m_particle.setPosition(10, 50, 0); // �ʱ���ġ
	m_particle.setVelocity(0, 0, 0); // �ʱ� �ӵ�
	m_particle.setMass(10.0f); // ����
	m_particle.setDamping(1.0f); // ����
	m_particle.setAcceleration(cyclone::Vector3(0, 0, 0)); // �ʱ� ���ӵ�
	m_color = cyclone::Vector3(1.0f, 0.0f, 0.0f); // �ʱ� ����
	m_gravity = new cyclone::ParticleGravity(cyclone::Vector3(0, -10, 0));
	m_drag = new cyclone::ParticleDrag(0.1, 0.1);
	m_forces = new cyclone::ParticleForceRegistry();

	m_forces->add(&m_particle, m_gravity);
	m_forces->add(&m_particle, m_drag);
}


mover::~mover()
{
}

void mover::update(float duration) {
	m_forces->updateForces(duration);
	m_particle.integrate(duration);

	checkedge();
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
		glColor3f(1.0f, 0.1f, 0.1f);
	}
	glPushMatrix();
	glTranslatef(position.x, position.y, position.z); // ��ġ ����
	glutSolidSphere(5.0, 30, 30); // �� ����
	glPopMatrix();
}

void mover::checkedge() {
	if (m_particle.getPosition().y < 5) {
		m_particle.setVelocity(m_particle.getVelocity().x, - m_particle.getVelocity().y, m_particle.getVelocity().z);
		m_particle.setPosition(m_particle.getPosition().x, 5, m_particle.getPosition().z);
	}
}