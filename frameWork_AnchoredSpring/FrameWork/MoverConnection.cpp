#include "MoverConnection.h"

MoverConnection::MoverConnection() {
	mover* Mover = new mover(cyclone::Vector3 (0, 4, 0));

	Mover->setConnection();

	m_force = new cyclone::ParticleForceRegistry();
	m_force->add(&Mover->m_particle, m_gravity);
	m_force->add(&Mover->m_particle, Mover->m_anchoredspring);

	m_movers.push_back(Mover);
}

MoverConnection::~MoverConnection() {

}

void MoverConnection::update(float duration) {
	m_movers[0]->update(duration);

	//collisioncheck(m_movers);
}

void MoverConnection::draw(int shadow) {
	for (unsigned int i = 0; i < m_movers.size(); i++) {
		if (!shadow)
			glLoadName(i + 1);
		m_movers[i]->draw(shadow);
	}

	// 두 개의 mover 사이를 선으로 연결하기
	cyclone::Vector3 spr = *(m_movers[0]->m_anchoredspring->getAnchor());
	cyclone::Vector3 position = m_movers[0]->m_particle.getPosition();

	glColor3f(0, 0, 0);  //선 색상
	if (shadow) {
		glColor4f(0.3f, 0.3f, 0.3f, 0.8f);
	}
	glLineWidth(1.0f);  //선 굵기
	glPushMatrix();
	glBegin(GL_LINES);
	glVertex3f(spr.x, spr.y, spr.z);  //시작점
	glVertex3f(position.x, position.y, position.z); //끝점
	glEnd();
	glPopMatrix();
}

void MoverConnection::collisioncheck(std::vector<mover*>m_movers) {
	cyclone::Vector3 position;

	position = cyclone::Vector3(m_movers[0]->m_particle.getPosition().x, 0, m_movers[0]->m_particle.getPosition().z) - cyclone::Vector3(m_movers[0]->m_anchoredspring->getAnchor()->x, 0, m_movers[0]->m_anchoredspring->getAnchor()->z);
	if (m_movers[0]->m_particle.getPosition().y < 15 && position.magnitude() < 1.0) {
		m_movers[0]->m_particle.setVelocity(m_movers[0]->m_particle.getVelocity() * (-1));
	}
}