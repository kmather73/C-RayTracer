#include <cmath>

#include "light.h"


using namespace std;

double DirectionalLight::distanceAttenuation( const Vec3d& P ) const
{
	//  distance to light is infinite, so f(di) goes to 0.  Return 1.
	return 1.0;
}


Vec3d DirectionalLight::shadowAttenuation(const ray &r, const Vec3d& p ) const
{
    //  YOUR CODE HERE:
    //  You should implement shadow-handling code here.
	ray point_to_light(p, -orientation, ray::SHADOW);
	isect i;

	if (scene->intersect(point_to_light, i)) {
		Vec3d q = point_to_light.at(i.t);

		Vec3d kt;
		Vec3d intensity_at_q = Vec3d(1,1,1);
		if (i.material != nullptr) {
			kt = i.material->kt(i);
			intensity_at_q = shadowAttenuation(r, q);
		}
		return prod(intensity_at_q, kt);
	}
	return color;
}

Vec3d DirectionalLight::getColor( const Vec3d& P ) const
{
	//  Color doesn't depend on P 
	return color;
}

Vec3d DirectionalLight::getDirection( const Vec3d& P ) const
{
	return -orientation;
}

double PointLight::distanceAttenuation( const Vec3d& P ) const
{
	//  YOUR CODE HERE

	//  You'll need to modify this method to attenuate the intensity 
	//  of the light based on the distance between the source and the 
	//  point P.  For now, we assume no attenuation and just return 1.0
	Vec3d dp = P - position;
	double dist = dp.length();

	double f = 1 / (constantTerm + linearTerm*dist + quadraticTerm * dist * dist);
	return min(1.0, f);
}

Vec3d PointLight::getColor( const Vec3d& P ) const
{
	//  Color doesn't depend on P 
	return color;
}

Vec3d PointLight::getDirection( const Vec3d& P ) const
{
	Vec3d ret = position - P;
	ret.normalize();
	return ret;
}


Vec3d PointLight::shadowAttenuation(const ray &r,  const Vec3d& p) const
{
    //  YOUR CODE HERE:
    //  You should implement shadow-handling code here.

	try {
		ray point_to_light(p, getDirection(p), ray::SHADOW);
		isect i;
		bool intersection = scene->intersect(point_to_light, i);
		Vec3d q = point_to_light.at(i.t);

		double distance_pq = (p - q).length();
		bool before_light = distance_pq < (position - p).length();

		if (intersection && before_light) {
			Vec3d kt;
			Vec3d intensity_at_q;
			if (i.material != nullptr) {
				kt = i.material->kt(i);

				
				try {
					intensity_at_q = shadowAttenuation(r, q);
				} catch (std::exception &e) {
					cerr << "ERROR in recursive shadow call\n" << e.what() << endl;
					return Vec3d(0, 0, 0);
				}
			}
			return prod(intensity_at_q, kt);
		}

		
	}
	catch (std::exception e) {
		cerr << "ERROR in PointLight::shadowAttenuation \n" << e.what() << endl;
	}
	return color;
}
