#pragma once

#include "Fire.h"

class Fireworks
{
public:
	Fireworks();
	~Fireworks();

	void update(float duration); // Fire�� ����,�Ҹ�,������Ʈ
	void create(); // init Fire ����
	void create(Fire * parent); // Child Fire ����
	void draw(int shadow); // �׸���

	FireworksRule m_rule[3]; // ��
	std::vector<Fire*> fireworks; // Fire ����
	std::vector<Fire*> remove; // child Fire���� �Ӽ����� ������ �ֱ����� init Fire�� �����Ǳ��� ���� ����
};