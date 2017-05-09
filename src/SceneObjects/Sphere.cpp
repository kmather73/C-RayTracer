#include <cmath>

#include "Sphere.h"

using namespace std;


bool Sphere::intersectLocal( const ray& r, isect& i ) const
{
    // YOUR CODE HERE:
    // Add sphere intersection code here.
    // it currently ignores all spheres and just return false.
	i.obj = this;
	Vec3d pos = r.getPosition();
	Vec3d dir = r.getDirection();

	double c = -1;
	double b = 0;
	double a = 0;// will endup being 1 for unit vectors

	for (int i = 0; i < 3; ++i) {
		c += pos[i] * pos[i];
		b += 2 * pos[i] * dir[i];
		a += dir[i] * dir[i];
	}

	double discriminant = b*b - 4 * a*c;

	if (discriminant < 0) return false;

	discriminant = sqrt(discriminant);

	double t2 = (-b + discriminant) / (2.0 * a);

	if (t2 <= RAY_EPSILON) {
		return false;
	}

	double t1 = (-b - discriminant) / (2.0 * a);

	if (t1 > RAY_EPSILON) {
		// Two intersections.
		Vec3d P = r.at(t1);
		double z = P[2];
		if (z >= -1.0 && z <= 1.0) {
			// It's okay.
			i.t = t1;
			i.N = Vec3d(P[0], P[1], P[2]);
			i.N.normalize();
			return true;
		}
	}

	Vec3d P = r.at(t2);
	double z = P[2];
	if (z >= -1.0 && z <= 1.0) {
		i.t = t2;

		Vec3d normal(P[0], P[1], 0.0);
		// In case we are _inside_ the sphere, we need to flip the normal.
		// Essentially, the shpere in this case is a double-sided surface
		// and has _2_ normals
		if ((normal * r.getDirection()) > 0)
			normal = -normal;

		i.N = normal;
		i.N.normalize();
		return true;
	}
	return false;
    return false;
}

