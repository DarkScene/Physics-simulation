#include "MySpring.h"

Myspring::Myspring(cyclone::Particle * p, double springConstant, double restLenght)
{
	other = p;
	this->springConstant = springConstant;
	this->restLength = restLenght;
}

void Myspring::updateForce(cyclone::Particle * p, double duration)
{
	cyclone::Vector3 force; // ���� ���ؼ� particle�� ������ ��
	// �� ��ƼŬ�� Particle * p �� Particle * other
	
	cyclone::Vector3 d;
	double dmagni;

	d = p->getPosition() - other->getPosition();
	dmagni = d.magnitude();
	d.normalise();

	force = d * ((-1)*springConstant*(dmagni - restLength));

	p->addForce(force);
}
