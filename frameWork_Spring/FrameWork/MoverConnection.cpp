#include "MoverConnection.h"

MoverConnection::MoverConnection() {
	mover* MoverA = new mover(cyclone::Vector3 (0, 5, 0));
	mover* MoverB = new mover(cyclone::Vector3 (20, 5, 20));
	MoverA->m_color = cyclone::Vector3(0.0f, 1.0f, 0.0f);

	MoverA->setConnection(MoverB);
	MoverB->setConnection(MoverA);

	m_force = new cyclone::ParticleForceRegistry();
	m_force->add(&MoverA->m_particle, m_gravity);
	m_force->add(&MoverB->m_particle, m_gravity);
	m_force->add(&MoverA->m_particle, MoverA->m_spring);
	m_force->add(&MoverB->m_particle, MoverB->m_spring);

	m_movers.push_back(MoverA);
	m_movers.push_back(MoverB);
}

MoverConnection::~MoverConnection() {

}

void MoverConnection::update(float duration) {
	m_movers[0]->update(duration);
	m_movers[1]->update(duration);

	collisioncheck(m_movers);
}

void MoverConnection::draw(int shadow) {
	for (unsigned int i = 0; i < m_movers.size(); i++) {
		if (!shadow)
			glLoadName(i + 1);
		m_movers[i]->draw(shadow);
	}

	// 두 개의 mover 사이를 선으로 연결하기
	glBegin(GL_LINE_STRIP);
	for (unsigned int i = 0; i < m_movers.size(); i++) {
		cyclone::Vector3 p = m_movers[i]->m_particle.getPosition();
		glVertex3f(p.x, p.y, p.z);
	}
	glEnd();
}

void MoverConnection::collisioncheck(std::vector<mover*>m_movers) {
	cyclone::Vector3 position;

	position = m_movers[0]->m_particle.getPosition() - m_movers[1]->m_particle.getPosition();
	if (position.magnitude() < 10.0) {
		m_movers[0]->m_particle.setVelocity(m_movers[0]->m_particle.getVelocity() * (-1));
		m_movers[1]->m_particle.setVelocity(m_movers[1]->m_particle.getVelocity() * (-1));
	}


}