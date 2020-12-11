


#include <iostream>

#define _USE_MATH_DEFINES
#include <cmath> 

#include "core.h"


int main()
{
	cyclone::Vector3 A(1, 2, -1);
	cyclone::Vector3 B(3, 0, 2);

	cyclone::Vector3 C = A.cross(B);

	A.normalise();
	C.normalise();

	if (C.magnitude() != 0) {
		B = C.cross(A);
	}
	else {
		std::cout << "Can not Cross!!" << std::endl;
	}

	std::cout << A.toString() << std::endl;
	std::cout << B.toString() << std::endl;
	std::cout << C.toString() << std::endl;
}