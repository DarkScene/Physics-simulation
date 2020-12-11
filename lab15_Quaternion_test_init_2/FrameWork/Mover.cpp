
#include <iostream>
#include "Mover.h"
#include "gl/glut.h"
#include "timing.h"


float size = 1.0f;


///////////////////////////////////////////////////////////////////
Mover::Mover(cyclone::Vector3 & p)
{
	m_particle = new cyclone::Particle();

	cyclone::Matrix3 inertiaMatrix;
	inertiaMatrix.setBlockInertiaTensor(cyclone::Vector3(1, 1, 1), 3.0);

	//Local Inertia Matrix의 역행렬 
	inverseInertiaMatrix = inertiaMatrix.inverse();

	//mover의 quaternion인 orientation을 입력받아 3x3 행렬로 변환
	cyclone::Matrix3 orintationMatrix;
	orintationMatrix.setOrientation(orientation);
	cyclone::Matrix3 TransposeorintationMatrix;
	TransposeorintationMatrix = orintationMatrix.transpose();

	inverseInertiaTensorWorld = orintationMatrix * inverseInertiaMatrix * TransposeorintationMatrix;
}



Mover::~Mover()
{
}

void Mover::update(float duration)
{
	cyclone::Vector3 angularAcceleration = inverseInertiaTensorWorld.transform(torqueAccum);
	rotation.addScaledVector(angularAcceleration, duration);  //𝛚= 𝛚 + 𝜶∙∆t (각 가속도를 이용한 각속도 업데이트)

	double angularDamping = 0.8;

	rotation *= real_pow(angularDamping, duration);  //𝛚=𝛚∙𝒅𝒂𝒎𝒑𝒊𝒏𝒈 (댐핑 곱함)

	orientation.addScaledVector(rotation, duration); //𝒒′=𝒒+𝟏/𝟐 𝒒(𝛚)∗𝒒 (𝛚를 quaternion으로 변경 후 quaternion곱 수행)

	orientation.normalise();  //quaternion의 normalize 

	transformMatrix.setOrientationAndPos(orientation, cyclone::Vector3(0, 6, 0)); //위치(0,6,0)와 q를 이용한 변환 행렬

	torqueAccum.clear(); //torque를 사용후에 clear
}

void Mover::getGLTransform(float matrix[16])
{
	
	
	matrix[0] = (float)transformMatrix.data[0];
	matrix[1] = (float)transformMatrix.data[4];
	matrix[2] = (float)transformMatrix.data[8];
	matrix[3] = 0;

	matrix[4] = (float)transformMatrix.data[1];
	matrix[5] = (float)transformMatrix.data[5];
	matrix[6] = (float)transformMatrix.data[9];
	matrix[7] = 0;

	matrix[8] = (float)transformMatrix.data[2];
	matrix[9] = (float)transformMatrix.data[6];
	matrix[10] = (float)transformMatrix.data[10];
	matrix[11] = 0;

	matrix[12] = (float)transformMatrix.data[3];
	matrix[13] = (float)transformMatrix.data[7];
	matrix[14] = (float)transformMatrix.data[11];
	matrix[15] = 1;
}


/** Draws the bone. */
void draw(int shadow)
{
	
}

void Mover::draw(int shadow)
{
	// Get the OpenGL transformation
	GLfloat mat[16];
	getGLTransform(mat);


	if (!shadow) {
		glPushMatrix();
		glMultMatrixf(mat);

		glLineWidth(3.0f);
		glBegin(GL_LINES);
		glColor3f(1, 0, 0);

		glVertex3f(0, 0.1, 0);
		glVertex3f(0, 10, 0);

		glColor3f(0, 1, 0);

		glVertex3f(0, 0.1, 0);
		glVertex3f(10, 0.1, 0);

		glColor3f(0, 0, 1);

		glVertex3f(0, 0.1, 0);
		glVertex3f(0, 0.1, 10);
		glEnd();
		glPopMatrix();
		glLineWidth(1.0f);
	}
	

	

	if (shadow) {
		glColor3f(0.2f, 0.2f, 0.2f);
	}
	else {

		glColor3f(1, 0., 0);
	}


	glPushMatrix();
	glMultMatrixf(mat);

	glutSolidCube(1.0f); // 박스를 그리는 함수(박스의 크기를 변경 가능)
	glPopMatrix();



	

}

void Mover::addTorque(cyclone::Vector3 force, cyclone::Vector3 point) {
	cyclone::Vector3 d = point - cyclone::Vector3(0, 6, 0);
	torqueAccum = d.cross(force);
}


//////////////////////////////

MoverConnection::MoverConnection()
{
	Mover * a = new Mover(cyclone::Vector3(3, size, 3));

	const float degrees2Radians = 3.141592f / 180;

	cyclone::Quaternion q1;

	//q1.r = cos(degrees2Radians * 45.0f * 0.5);
	//cyclone::Vector3 v = cyclone::Vector3(0, 1, 0) * sin(degrees2Radians * 45.0f * 0.5);
	//q1.i = v.x;
	//q1.j = v.y;
	//q1.k = v.z;

	//q1.normalise();

	//cyclone::Quaternion q2;

	//q2.r = cos(degrees2Radians * 90.0f * 0.5);
	//v = cyclone::Vector3(1, 0, 0) * sin(degrees2Radians * 90.0f * 0.5);
	//q2.i = v.x;
	//q2.j = v.y;
	//q2.k = v.z;

	//q2.normalise();

	//q2 *= q1;

	//사원수에 q의 오리엔테이션과 vector3의 위치이동으로 통해 mat4를 구성
	a->transformMatrix.setOrientationAndPos(q1, cyclone::Vector3(0, 6, 0));
	m_movers.push_back(a);	
}

MoverConnection::~MoverConnection()
{


}


void MoverConnection::update(float duration)
{
	for (unsigned int i = 0; i < m_movers.size(); i++) {
		m_movers[i]->update(duration);
	}
}


void MoverConnection::draw(int shadow)
{

	for (unsigned int i = 0; i < m_movers.size(); i++) {
		if (!shadow)
			glLoadName(i + 1);
		m_movers[i]->draw(shadow);

	}

	
}