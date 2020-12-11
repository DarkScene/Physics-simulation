#include "Fireworks.h"

Fireworks::Fireworks() {
	m_rule[0].setParameters(1, 3.0, 6.0, cyclone::Vector3(-1, -1, -1), cyclone::Vector3(1, 1, 1), 50.0f, 0.3f, 80); // 큰 원형 폭죽
	m_rule[1].setParameters(1, 2.0, 5.0, cyclone::Vector3(-1, -1, -1), cyclone::Vector3(1, 1, 1), 15.0f, 0.55f, 50); // 작은 원형 폭죽
	m_rule[2].setParameters(1, 1.0, 4.0, cyclone::Vector3(-1, -1, -1), cyclone::Vector3(1, 1, 1), 15.0f, 0.22f, 10); // 넓게 퍼져서 반짝이는 폭죽
}

Fireworks::~Fireworks() {

}

void Fireworks::update(float duration) {
	for (auto iter = fireworks.begin(); iter != fireworks.end(); iter++) {
		(*iter)->update(duration);
	}

	for (auto iter = fireworks.begin(); iter != fireworks.end();) {  //fireworks안의 모든 fire에 대해  
		Fire * m = *iter;  //하나 하나씩 꺼내
		if (m->update(duration)) { //만일 조건에 맞다면..
			if (m->m_type == 0) { // init Fire 이면
				remove.push_back(m); // 삭제전 init Fire의 정보를 저장
			}
			iter = fireworks.erase(iter);  //fireworks에서 삭제 함
		}
		else {
			++iter;
		}
	}

	for (auto iter = remove.begin(); iter != remove.end();) {
		create(*iter);
		iter = remove.erase(iter);
	}
}

void Fireworks::create() { // init Fire 생성
	static cyclone::Random crandom;
	int initType = rand() % 6; // 확률을 다르게 하기 위해 (1번 rule 2/5, 2번 rule 3/5, 3번 rule 1/5)

	if (initType == 0 || initType == 3) {
		for (int i = 0; i < 3; i++) {
			Fire* tmp = new Fire(0);

			tmp->setRule(&m_rule[0]);

			// 생성되는 폭죽의 포지션을 좀더 퍼뜨리기 위한 조건 추가
			if (i % 3 == 0) {
				tmp->m_particle.setPosition(crandom.randomReal(-70, -30), 10, crandom.randomReal(-5, 5));
			}
			else if (i % 3 == 1) {
				tmp->m_particle.setPosition(crandom.randomReal(-20, 20), 10, crandom.randomReal(-5, 5));
			}

			else {
				tmp->m_particle.setPosition(crandom.randomReal(30, 70), 10, crandom.randomReal(-5, 5));
			}
			
			tmp->m_particle.setVelocity(crandom.randomReal(-2, 2), crandom.randomReal(40, 50), crandom.randomReal(-2, 2));
			tmp->m_particle.setMass(1.0f);
			tmp->m_particle.setDamping(0.99f);
			tmp->m_size = 0.7f; // 불꽃의 크기가 크므로 구의 크기를 조금 더 크게
			tmp->m_age = crandom.randomReal(4.0, 5.0);
			tmp->m_color = crandom.randomVector(cyclone::Vector3(0.1, 0.1, 0.1), cyclone::Vector3(1, 1, 1));
			fireworks.push_back(tmp);
		}
	}

	else if (initType == 1 || initType == 4 || initType == 5) {
		for (int i = 0; i < 6; i++) {
			Fire* tmp = new Fire(0);

			tmp->setRule(&m_rule[1]);

			// 생성되는 폭죽의 포지션을 좀더 퍼뜨리기 위한 조건 추가
			if (i % 2 == 0) {
				tmp->m_particle.setPosition(crandom.randomReal(-70, -10), 10, crandom.randomReal(-5, 5));
			}
			else if (i % 2 == 1) {
				tmp->m_particle.setPosition(crandom.randomReal(10, 70), 10, crandom.randomReal(-5, 5));
			}

			tmp->m_particle.setVelocity(crandom.randomReal(-5, 5), crandom.randomReal(30, 40), crandom.randomReal(-5, 5));
			tmp->m_particle.setMass(1.0f);
			tmp->m_particle.setDamping(0.99f);
			tmp->m_age = crandom.randomReal(2.0, 3.0);
			tmp->m_color = crandom.randomVector(cyclone::Vector3(0.1, 0.1, 0.1), cyclone::Vector3(1, 1, 1));
			fireworks.push_back(tmp);
		}
	}

	else if (initType == 2) {
		for (int i = 0; i < 30; i++) {
			Fire* tmp = new Fire(0);

			tmp->setRule(&m_rule[2]);

			// 생성되는 폭죽의 포지션을 좀더 퍼뜨리기 위한 조건 추가
			if (i % 2 == 0) {
				tmp->m_particle.setPosition(crandom.randomReal(-70, -10), 10, crandom.randomReal(-5, 5));				
			}
			else if (i % 2 == 1) {
				tmp->m_particle.setPosition(crandom.randomReal(10, 70), 10, crandom.randomReal(-5, 5));
			}

			tmp->m_particle.setVelocity(crandom.randomReal(-3, 3), crandom.randomReal(5, 10), crandom.randomReal(-3, 3));
			tmp->m_particle.setAcceleration(0, -1.0f, 0); // 천천히 올라가는 것을 구현하기 위해 중력값과 속도값을 임의로 낮춤
			tmp->m_particle.setMass(1.0f);
			tmp->m_particle.setDamping(0.99f);
			tmp->m_size = 0.4f; // 불꽃의 크기가 작으므로 구의 크기를 조금 더 작게
			tmp->m_age = crandom.randomReal(3.0, 10.0);
			tmp->m_color = cyclone::Vector3(1.0, 1.0, crandom.randomReal(0.2, 1.0)); // 색상을 노란색과 흰색 계열만 나오도록 설정
			fireworks.push_back(tmp);
		}
	}
}

void Fireworks::create(Fire* parent) { // child Fire 생성
	static cyclone::Random crandom;
	cyclone::Vector3 velocity;
	float age = crandom.randomReal(0.5, 12.0);

	for (int i = 0; i < parent->m_rule->payloadCount; i++) {
		Fire* tmp = new Fire(1);

		velocity = parent->m_particle.getVelocity() + parent->m_rule->getSameScalarVelocity(); // 원래의 벡터값에 m_rule에서 지정된 Scalar의 값이 일정한 벡터를 더함

		tmp->m_particle.setPosition(parent->m_particle.getPosition().x, parent->m_particle.getPosition().y, parent->m_particle.getPosition().z);
		tmp->m_particle.setVelocity(velocity.x, velocity.y, velocity.z);
		tmp->m_age = crandom.randomReal(parent->m_rule->m_minAge, parent->m_rule->m_maxAge);
		tmp->m_particle.setDamping(parent->m_rule->m_damping);
		tmp->m_particle.setAcceleration(cyclone::Vector3(0, -3.0f, 0)); // child Fire가 좀 더 자연스럽게 퍼질 수 있게 중력값을 줄임(질량이 작아진 입자들이 공기저항을 받아 조금더 위에 떠있는 느낌을 구현하기 위해)
		tmp->m_color = parent->m_color; // init Fire의 컬러값을 child Fire가 그대로 가지고 가도록 설정
		tmp->m_size = parent->m_size;
		fireworks.push_back(tmp);
	}
}

void Fireworks::draw(int shadow) {
	for (auto iter = fireworks.begin(); iter != fireworks.end(); iter++) {
		if (shadow == 1) {
			(*(*iter)).draw(1);
		}
		else if (shadow == 0) {
			(*iter)->draw(0);
		}
	}
}