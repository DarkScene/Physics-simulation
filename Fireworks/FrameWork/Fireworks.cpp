#include "Fireworks.h"

Fireworks::Fireworks() {
	m_rule[0].setParameters(1, 3.0, 6.0, cyclone::Vector3(-1, -1, -1), cyclone::Vector3(1, 1, 1), 50.0f, 0.3f, 80); // ū ���� ����
	m_rule[1].setParameters(1, 2.0, 5.0, cyclone::Vector3(-1, -1, -1), cyclone::Vector3(1, 1, 1), 15.0f, 0.55f, 50); // ���� ���� ����
	m_rule[2].setParameters(1, 1.0, 4.0, cyclone::Vector3(-1, -1, -1), cyclone::Vector3(1, 1, 1), 15.0f, 0.22f, 10); // �а� ������ ��¦�̴� ����
}

Fireworks::~Fireworks() {

}

void Fireworks::update(float duration) {
	for (auto iter = fireworks.begin(); iter != fireworks.end(); iter++) {
		(*iter)->update(duration);
	}

	for (auto iter = fireworks.begin(); iter != fireworks.end();) {  //fireworks���� ��� fire�� ����  
		Fire * m = *iter;  //�ϳ� �ϳ��� ����
		if (m->update(duration)) { //���� ���ǿ� �´ٸ�..
			if (m->m_type == 0) { // init Fire �̸�
				remove.push_back(m); // ������ init Fire�� ������ ����
			}
			iter = fireworks.erase(iter);  //fireworks���� ���� ��
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

void Fireworks::create() { // init Fire ����
	static cyclone::Random crandom;
	int initType = rand() % 6; // Ȯ���� �ٸ��� �ϱ� ���� (1�� rule 2/5, 2�� rule 3/5, 3�� rule 1/5)

	if (initType == 0 || initType == 3) {
		for (int i = 0; i < 3; i++) {
			Fire* tmp = new Fire(0);

			tmp->setRule(&m_rule[0]);

			// �����Ǵ� ������ �������� ���� �۶߸��� ���� ���� �߰�
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
			tmp->m_size = 0.7f; // �Ҳ��� ũ�Ⱑ ũ�Ƿ� ���� ũ�⸦ ���� �� ũ��
			tmp->m_age = crandom.randomReal(4.0, 5.0);
			tmp->m_color = crandom.randomVector(cyclone::Vector3(0.1, 0.1, 0.1), cyclone::Vector3(1, 1, 1));
			fireworks.push_back(tmp);
		}
	}

	else if (initType == 1 || initType == 4 || initType == 5) {
		for (int i = 0; i < 6; i++) {
			Fire* tmp = new Fire(0);

			tmp->setRule(&m_rule[1]);

			// �����Ǵ� ������ �������� ���� �۶߸��� ���� ���� �߰�
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

			// �����Ǵ� ������ �������� ���� �۶߸��� ���� ���� �߰�
			if (i % 2 == 0) {
				tmp->m_particle.setPosition(crandom.randomReal(-70, -10), 10, crandom.randomReal(-5, 5));				
			}
			else if (i % 2 == 1) {
				tmp->m_particle.setPosition(crandom.randomReal(10, 70), 10, crandom.randomReal(-5, 5));
			}

			tmp->m_particle.setVelocity(crandom.randomReal(-3, 3), crandom.randomReal(5, 10), crandom.randomReal(-3, 3));
			tmp->m_particle.setAcceleration(0, -1.0f, 0); // õõ�� �ö󰡴� ���� �����ϱ� ���� �߷°��� �ӵ����� ���Ƿ� ����
			tmp->m_particle.setMass(1.0f);
			tmp->m_particle.setDamping(0.99f);
			tmp->m_size = 0.4f; // �Ҳ��� ũ�Ⱑ �����Ƿ� ���� ũ�⸦ ���� �� �۰�
			tmp->m_age = crandom.randomReal(3.0, 10.0);
			tmp->m_color = cyclone::Vector3(1.0, 1.0, crandom.randomReal(0.2, 1.0)); // ������ ������� ��� �迭�� �������� ����
			fireworks.push_back(tmp);
		}
	}
}

void Fireworks::create(Fire* parent) { // child Fire ����
	static cyclone::Random crandom;
	cyclone::Vector3 velocity;
	float age = crandom.randomReal(0.5, 12.0);

	for (int i = 0; i < parent->m_rule->payloadCount; i++) {
		Fire* tmp = new Fire(1);

		velocity = parent->m_particle.getVelocity() + parent->m_rule->getSameScalarVelocity(); // ������ ���Ͱ��� m_rule���� ������ Scalar�� ���� ������ ���͸� ����

		tmp->m_particle.setPosition(parent->m_particle.getPosition().x, parent->m_particle.getPosition().y, parent->m_particle.getPosition().z);
		tmp->m_particle.setVelocity(velocity.x, velocity.y, velocity.z);
		tmp->m_age = crandom.randomReal(parent->m_rule->m_minAge, parent->m_rule->m_maxAge);
		tmp->m_particle.setDamping(parent->m_rule->m_damping);
		tmp->m_particle.setAcceleration(cyclone::Vector3(0, -3.0f, 0)); // child Fire�� �� �� �ڿ������� ���� �� �ְ� �߷°��� ����(������ �۾��� ���ڵ��� ���������� �޾� ���ݴ� ���� ���ִ� ������ �����ϱ� ����)
		tmp->m_color = parent->m_color; // init Fire�� �÷����� child Fire�� �״�� ������ ������ ����
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