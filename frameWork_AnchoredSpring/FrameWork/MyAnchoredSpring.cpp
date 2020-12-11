#include "MyAnchoredSpring.h"

MyAnchoredSpring::MyAnchoredSpring() {

}

MyAnchoredSpring::MyAnchoredSpring(cyclone::Vector3 *anchor, double springConstant, double restLenght) {
	this->anchor = anchor;
	this->springConstant = springConstant;
	this->restLength = restLenght;
}

void MyAnchoredSpring::init(cyclone::Vector3 *anchor, double springConstant, double restLength) {
	this->anchor = anchor;
	this->springConstant = springConstant;
	this->restLength = restLength;
}

void MyAnchoredSpring::updateForce(cyclone::Particle *particle, cyclone::real duration) {
	cyclone::Vector3 force;

	cyclone::Vector3 d;
	double dmagni;

	d = particle->getPosition() - *getAnchor();
	dmagni = d.magnitude();
	d.normalise();

	force = d * ((-1)*springConstant*(dmagni - restLength));

	particle->addForce(force);
}