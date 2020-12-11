#pragma once

#include "Fire.h"

class Fireworks
{
public:
	Fireworks();
	~Fireworks();

	void update(float duration); // Fire의 생성,소멸,업데이트
	void create(); // init Fire 생성
	void create(Fire * parent); // Child Fire 생성
	void draw(int shadow); // 그리기

	FireworksRule m_rule[3]; // 룰
	std::vector<Fire*> fireworks; // Fire 저장
	std::vector<Fire*> remove; // child Fire에게 속성값을 전달해 주기위해 init Fire가 삭제되기전 정보 저장
};