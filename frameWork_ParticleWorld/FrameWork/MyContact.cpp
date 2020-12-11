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
			contact->contactNormal = cyclone::Vector3(0, 1, 0); // p->getVelocity().unit() * -1;
			contact->particle[0] = p;
			contact->particle[1] = NULL;
			contact->penetration = 0 - (p->getPosition().y - size);
			contact->restitution = 1.0;
			count++;
			contact++;
		}
		if (count >= limit) return count;
	}
	return count;
}

unsigned ParticleCollision::addContact(cyclone::ParticleContact *contact, unsigned limit) const {
	//두 파티클이 충돌 했는지를 확인 한 후, 만일 충돌했다면 아래 정보를 입력 한 후 1을 반환
	// 충돌이 발생하지 않았다면 0을 반환 (즉, contact에 정보를 넣는 것은 충돌 했을 경우에만..)
	//contact->contactNormal =
	//contact->penetration =
	//contact->restitution =
	contact->particle[0] = particle[0];
	contact->particle[1] = particle[1];

	if (currentLength() < size * 2) {
		contact->contactNormal = (particle[0]->getPosition() - particle[1]->getPosition()).unit();
		contact->penetration = (size * 2) - currentLength();
		contact->restitution = 1.0;

		return 1;
	}
	return 0;
}