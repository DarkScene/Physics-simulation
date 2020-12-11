#include "MySpring.h"

Myspring::Myspring(cyclone::Particle * p, double springConstant, double restLenght)
{
	other = p;
	this->springConstant = springConstant;
	this->restLength = restLenght;
}

void Myspring::updateForce(cyclone::Particle * p, double duration)
{
	cyclone::Vector3 force; // 힘을 구해서 particle에 적용할 것
	// 두 파티클은 Particle * p 와 Particle * other
	
	cyclone::Vector3 d;
	double dmagni;

	d = p->getPosition() - other->getPosition();
	dmagni = d.magnitude();
	d.normalise();

	force = d * ((-1)*springConstant*(dmagni - restLength));

	p->addForce(force);
}
