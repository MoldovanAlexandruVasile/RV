#include <cmath>
#include <iostream>
#include <string>

#include "Vector.hpp"
#include "Line.hpp"
#include "Geometry.hpp"
#include "Sphere.hpp"
#include "Image.hpp"
#include "Color.hpp"
#include "Intersection.hpp"
#include "Material.hpp"

#include "Scene.hpp"

using namespace std;
using namespace rt;

float imageToViewPlane(int n, int imgSize, float viewPlaneSize) {
	float u = (float)n*viewPlaneSize / (float)imgSize;
	u -= viewPlaneSize / 2;
	return u;
}

const Intersection findFirstIntersection(const Line& ray,
	float minDist, float maxDist) {
	Intersection intersection;

	for (int i = 0; i < geometryCount; i++) {
		Intersection in = scene[i]->getIntersection(ray, minDist, maxDist);
		if (in.valid()) {
			if (!intersection.valid()) {
				intersection = in;
			}
			else if (in.t() < intersection.t()) {
				intersection = in;
			}
		}
	}

	return intersection;
}

int main() {
	Vector viewPoint(0, 0, 0);
	Vector viewDirection(0, 0, 1);
	Vector viewUp(0, -1, 0);

	float frontPlaneDist = 0;
	float backPlaneDist = 1000;

	float viewPlaneDist = 512;
	float viewPlaneWidth = 1024;
	float viewPlaneHeight = 768;

	int imageWidth = 1024;
	int imageHeight = 768;

	Vector viewParallel = viewUp^viewDirection;

	viewDirection.normalize();
	viewUp.normalize();
	viewParallel.normalize();

	Image image(imageWidth, imageHeight);

	for (int i = 0; i < imageWidth; i++) {
		for (int j = 0; j < imageHeight; j++) {
			float iView = imageToViewPlane(i, imageWidth, viewPlaneWidth);
			float jView = imageToViewPlane(j, imageHeight, viewPlaneHeight);
			Vector pixelPos = viewPoint + viewDirection * viewPlaneDist + viewUp * jView + viewParallel * iView;
			Line line = Line(viewPoint, pixelPos, false);
			Intersection intersection = findFirstIntersection(line, frontPlaneDist, backPlaneDist);
			if (intersection.valid()) {
				Color color = Color(0, 0, 0);
				for (Light *light : lights) {
					Color secondColor = Color(0, 0, 0);
					Vector L = light->position();
					Vector C = viewPoint;
					Vector V = intersection.vec();
					Vector E = C - V;
					Vector N = intersection.geometry()->normal(V);
					Vector T = L - V;
					E.normalize();
					T.normalize();
					Vector R = N * (N * T) * 2 - T;
					R.normalize();
					secondColor += intersection.geometry()->material().ambient() * light->ambient();
					if (N * T > 0)
						secondColor += intersection.geometry()->material().diffuse() * light->diffuse() * (N * T);
					if (E * R > 0)
						secondColor += intersection.geometry()->material().specular() * light->specular() * pow(E * R, intersection.geometry()->material().shininess());
					color += secondColor;
				}	
				color = color / lightCount;
				image.setPixel(i, j, color);
			}
			else image.setPixel(i, j, Color(0,0,0));
		}
	}

	image.store("scene.png");

	for (int i = 0; i < geometryCount; i++) {
		delete scene[i];
	}

	return 0;
}
