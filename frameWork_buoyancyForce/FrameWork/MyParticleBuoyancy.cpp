#include "MyParticleBuoyancy.h"

MyParticleBuoyancy::MyParticleBuoyancy(cyclone::real maxDepth, cyclone::real volume, cyclone::real waterHeight, cyclone::real liquidDensity) :
	maxDepth(maxDepth), volume(volume), waterHeight(waterHeight), liquidDensity(liquidDensity) {}

void MyParticleBuoyancy::updateForce(cyclone::Particle* particle, cyclone::real duration) {
	cyclone::Vector3 force;
	cyclone::Vector3 pos = particle->getPosition();

	double h = pos.y;

	if (h - maxDepth > waterHeight)
		force = cyclone::Vector3(0, -10, 0);
	else if (h + maxDepth < waterHeight)
		force = cyclone::Vector3(0, volume * liquidDensity, 0);
	else {
		cyclone::real d = 0;
		d = (h - waterHeight - maxDepth) / (2 * maxDepth);
		force = cyclone::Vector3(0, d * volume * liquidDensity, 0);
	}

	particle->addForce(force);
}