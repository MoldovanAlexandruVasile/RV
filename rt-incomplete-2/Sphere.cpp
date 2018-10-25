#include "Sphere.hpp"

using namespace rt;

Intersection Sphere::getIntersection(const Line& line, float minDist, float maxDist) {
	Intersection in;

	Vector v = line.x0() - _center;
	float f1 = v * line.dx();
	float f2 = v * v - _radius * _radius;
	if (f1 > 0.0f && f2 > 0.0f) {
		in = Intersection(false, this, &line, 0);
	}
	float discr = f1 * f1 - f2;
	if (discr < 0.0f)
		in = Intersection(false, this, &line, 0);
	float t = - f1 - sqrt(discr);
	if (t < 0.0f)
		in = Intersection(false, this, &line, t);
	return in;
}


const Vector Sphere::normal(const Vector& vec) const {
	Vector n = vec - _center;
	n.normalize();
	return n;
}
