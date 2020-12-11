#pragma once

#include <GL/glut.h>
#include "core.h"
#include "particle.h"
#include "FireworksRule.h"

class Fire
{
public:
	Fire(int type); // type을 가진 Fire 생성 (0 = Init Fire, 1 = Child Fire)
	~Fire();

	float m_size;
	int m_type;
	float m_age;

	cyclone::Particle m_particle;
	cyclone::Vector3 m_color;
	FireworksRule* m_rule;

	std::deque <cyclone::Vector3> m_history; // 위치 history 저장
	bool update(float duration);
	void draw(int shadow);
	void drawHistory();
	void setRule(FireworksRule* r);
	void putHistory(); // 현재 위치를 m_history에 저장
};

