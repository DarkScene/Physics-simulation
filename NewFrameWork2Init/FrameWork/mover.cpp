#include "mover.h"



mover::mover()
{
	m_position = cyclone::Vector3(0, 5.0f, 0);
}


mover::~mover()
{
}

void mover::update() {

}

void mover::stop() {

}

void mover::draw(int shadow) {
	if (shadow) {
		glTranslatef(0, 0, 0); // 위치 변경
		glutSolidSphere(3, 30, 30); // 구 생성
		glColor3f(0.3f, 0.3f, 0.3f);
	}
	else {
		glTranslatef(0, 5.0f, 0); // 위치 변경
		glutSolidSphere(3, 30, 30); // 구 생성
		glColor3f(1.0f, 0.1f, 0.1f);
	}
}