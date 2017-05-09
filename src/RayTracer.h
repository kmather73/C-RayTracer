#ifndef __RAYTRACER_H__
#define __RAYTRACER_H__

// The main ray tracer.
#include <random>
#include "scene/ray.h"

class Scene;

class RayTracer
{
public:
    RayTracer();
    ~RayTracer();

    Vec3d trace( double x, double y );
	Vec3d traceRay( const ray& r, const Vec3d& thresh, int depth );


	void getBuffer( unsigned char *&buf, int &w, int &h );
	double aspectRatio();
	void traceSetup(int w, int h, int a, int d, bool kd);
	void tracePixel( int i, int j );

	bool loadScene( char* fn );

	bool sceneLoaded() { return scene != 0; }

	
	void setAA(int i) { aa = max(1, i); }
	void setKD(bool kd);
	
	void setDepth(int d) { depth = d; }

    void setReady( bool ready )
      { m_bBufferReady = ready; }
    bool isReady() const
      { return m_bBufferReady; }

	const Scene& getScene() { return *scene; }

private:
	unsigned char *buffer;
	int buffer_width, buffer_height;
	int depth;
	int aa;
	bool useKDT;
	int bufferSize;
	Scene* scene;
	std::default_random_engine generator;
	std::normal_distribution<double> distribution;
    bool m_bBufferReady;

};

#endif // __RAYTRACER_H__
