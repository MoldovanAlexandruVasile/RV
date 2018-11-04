#include "Sphere.hpp"

using namespace rt;

Intersection Sphere::getIntersection(const Line &line, float minDist, float maxDist) {
	/*
	* S <=> (Xs - Xc)^2 + (Ys - Yc)^2 + (Zs - Zc)^2 = R^2
	* We can substitute Xs, Ys, Zs as such:
	* Xs = X0 + Xd*t
	* Ys = Y0 + Yd*t
	* Zs = Z0 + Zd*t
	*
	* Replace these in S (for unknown t!!!) and obtain coefficients and delta
	* S becomes A*t^2 + B*t + C = 0
	* Where:
	* A = Xd^2 + Yd^2 + Zd^2
	* B = 2*(Xd * (X0 - Xc) + Yd * (Y0 - Yc) + Zd * (Z0 - Zc))
	* C = (X0 - Xc) + (Y0 - Yc) + (Z0 - Zc) - R^2
	*
	* delta = -B^2 + 4AC
	* delta < 0 <=> no intersection
	* delta == 0 <=> one solution (-b/2a)
	* delta > 0 <=> overlap, two solutions (-b+/-sqrt(delta)/2a), choose the smaller one (closest intersection point)
	*/

	Intersection in;
	double A = (line.dx().x() * line.dx().x()) +
		(line.dx().y() * line.dx().y()) +
		(line.dx().z() * line.dx().z());

	double B = 2 * (line.dx().x() * (line.x0().x() - center().x()) +
		line.dx().y() * (line.x0().y() - center().y()) +
		line.dx().z() * (line.x0().z() - center().z()));

	double C = (line.x0().x() - center().x()) * (line.x0().x() - center().x()) +
		(line.x0().y() - center().y()) * (line.x0().y() - center().y()) +
		(line.x0().z() - center().z()) * (line.x0().z() - center().z()) -
		radius() * radius();

	double delta = B * B - 4 * A * C;
	double t0, t1, t;

	if (delta < 0)
		in = Intersection(false, this, &line, 0);
	else if (delta == 0) {
		t = (-1 * B) / (2 * A);
		if (t >= minDist && t <= maxDist)
			in = Intersection(true, this, &line, t);
		else in = Intersection(false, this, &line, 0);
	}
	else {
		t0 = (-1 * B + sqrt(delta)) / (2 * A);
		t1 = (-1 * B - sqrt(delta)) / (2 * A);
		if (t0 < t1) {
			if (t0 >= minDist && t0 <= maxDist)
				in = Intersection(true, this, &line, t0);
			else in = Intersection(false, this, &line, 0);
		}
		else {
			if (t1 >= minDist && t1 <= maxDist)
				in = Intersection(true, this, &line, t1);
			else in = Intersection(false, this, &line, 0);
		}
	}

	return in;
}

const Vector Sphere::normal(const Vector& vec) const {
	Vector n = vec - _center;
	n.normalize();
	return n;
}
