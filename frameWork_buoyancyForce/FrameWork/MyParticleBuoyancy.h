#pragma once

#include "cyclone.h"

class MyParticleBuoyancy : public cyclone::ParticleForceGenerator {
	cyclone::real maxDepth;
	cyclone::real volume;
	cyclone::real waterHeight;
	cyclone::real liquidDensity;
public:
	MyParticleBuoyancy(cyclone::real maxDepth, cyclone::real volume, cyclone::real waterHeight, cyclone::real liquidDensity);
	virtual void updateForce(cyclone::Particle * particle, cyclone::real duration);
};