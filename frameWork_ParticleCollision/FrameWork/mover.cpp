#include "mover.h"



mover::mover(cyclone::Vector3 &p)
{
	m_particle.setPosition(p.x, p.y, p.z); // �ʱ���ġ
	m_particle.setVelocity(0, 0, 0); // �ʱ� �ӵ�
	m_particle.setMass(5.0f); // ����
	m_particle.setDamping(0.7f); // ����
	m_particle.setAcceleration(cyclone::Vector3(0, 0, 0)); // �ʱ� ���ӵ�
	m_color = cyclone::Vector3(1.0f, 0.0f, 0.0f); // �ʱ� ����
	
	m_gravity = new cyclone::ParticleGravity(cyclone::Vector3(0, -10, 0));
	m_drag = new cyclone::ParticleDrag(0.1, 0.1);
	m_forces = new cyclone::ParticleForceRegistry();

	m_forces->add(&m_particle, m_gravity);
	//m_forces->add(&m_particle, m_drag);
}


mover::~mover()
{
}

void mover::update(float duration) {
	//m_spring->updateForce(&m_particle, duration);
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
	glutSolidSphere(2.0, 30, 30); // �� ����
	glPopMatrix();
}

void mover::setConnection(mover * a) {
	m_spring = new Myspring(&a->m_particle, 20.0f, 3);
}