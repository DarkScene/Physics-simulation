#include "MyContact.h"

MyGroundContact::MyGroundContact()
{
}
MyGroundContact::~MyGroundContact()
{
}
void MyGroundContact::init(cyclone::Particle * p, double size) {
	if (p)
		particles.push_back(p);
	this->size = size;
}

unsigned MyGroundContact::addContact(cyclone::ParticleContact *contact, unsigned limit) const {
	unsigned count = 0;
	for (int i = 0; i < particles.size(); i++) {
		cyclone::Particle * p = particles[i];
		cyclone::real y = p->getPosition().y;

		//언제 충돌이 일어나나? (particle의 크기를 고려)
		//만일 충돌이 일어났다면
		//contact->contctNormal = ?
		//충돌의 대상이 되는 두 파티클 설정
		//contact->particles[0] = p;
		//contact->particles[1] = NULL; //왜? 바닥은 고정물체이므로
		//얼마나 침투 했나?
		//contact->penetration = ?
		//contact->restitution = 1.0
		//만일 충돌이 일어났다면 count를 증가시키고 contact++를 수행
		if (y < size) {
			contact->contactNormal = p->getVelocity().unit() * -1;
			contact->particle[0] = p;
			contact->particle[1] = NULL;
			contact->penetration = 0 - p->getPosition().y + size;
			contact->restitution = 1.0;
			count++;
		}
		if (count >= limit) return count;
	}
	return count;
}