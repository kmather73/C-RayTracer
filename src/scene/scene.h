//
// scene.h
//
// The Scene class and the geometric types that it can contain.
//

#pragma warning (disable: 4786)


#ifndef __SCENE_H__
#define __SCENE_H__

#include <vector>
#include <algorithm>
#include <map>
#include <string>
#include <memory>

#include "ray.h"
#include "material.h"
#include "camera.h"
#include "../vecmath/vec.h"
#include "../vecmath/mat.h"

class Light;
class Scene;


class SceneElement
{
public:
	virtual ~SceneElement() {}

	Scene *getScene() const { return scene; }

	// For debugging purposes, draws using OpenGL
	virtual void glDraw(int quality, bool actualMaterials, bool actualTextures) const  { }

protected:
	SceneElement( Scene *s )
		: scene( s ) {}

    Scene *scene;
};

class BoundingBox
{
public:
	Vec3d min;
	Vec3d max;

	void operator=(const BoundingBox& target);

	// Does this bounding box intersect the target?
	bool intersects(const BoundingBox &target) const;
	
	// does the box contain this point?
	bool intersects(const Vec3d& point) const;

	// if the ray hits the box, put the "t" value of the intersection
	// closest to the origin in tMin and the "t" value of the far intersection
	// in tMax and return true, else return false.
	bool intersect(const ray& r, double& tMin, double& tMax) const;

	void mergeBoxs(BoundingBox const &other);

	int getSplitAxis() const;

	void setMin(Vec3d bMin) {
		min = bMin;
	}
	void setMax(Vec3d bMax) {
		max = bMax;
	}

	void setMin(int i, double val) {
		if (i == 0) { min[0] = val;}
		else if (i == 1) { min[1] = val; }
		else if (i == 2) { min[2] = val; }
	}
	void setMax(int i, double val) {
		if (i == 0) { max[0] = val;}
		else if (i == 1) { max[1] = val; }
		else if (i == 2) { max[2] = val;}
	}

	Vec3d getMin() const { return min; }
	Vec3d getMax() const { return max; }

};

class TransformNode
{
protected:

    // information about this node's transformation
    Mat4d    xform;
	Mat4d    inverse;
	Mat3d    normi;

    // information about parent & children
    TransformNode *parent;
    std::vector<TransformNode*> children;
    
public:
   	typedef std::vector<TransformNode*>::iterator          child_iter;
	typedef std::vector<TransformNode*>::const_iterator    child_citer;

    ~TransformNode()
    {
        for(child_iter c = children.begin(); c != children.end(); ++c )
            delete (*c);
    }

    TransformNode *createChild(const Mat4d& xform)
    {
        TransformNode *child = new TransformNode(this, xform);
        children.push_back(child);
        return child;
    }
    
    // Coordinate-Space transformation
    Vec3d globalToLocalCoords(const Vec3d &v)
    {
        return inverse * v;
    }

    Vec3d localToGlobalCoords(const Vec3d &v)
    {
        return xform * v;
    }

    Vec4d localToGlobalCoords(const Vec4d &v)
    {
        return xform * v;
    }

    Vec3d localToGlobalCoordsNormal(const Vec3d &v)
    {
        Vec3d ret = normi * v;
		ret.normalize();
		return ret;
    }

	const Mat4d& transform() const		{ return xform; }

protected:
    // protected so that users can't directly construct one of these...
    // force them to use the createChild() method.  Note that they CAN
    // directly create a TransformRoot object.
    TransformNode(TransformNode *parent, const Mat4d& xform )
        : children()
    {
        this->parent = parent;
        if (parent == NULL)
            this->xform = xform;
        else
            this->xform = parent->xform * xform;
        
        inverse = this->xform.inverse();
        normi = this->xform.upper33().inverse().transpose();
    }
};

class TransformRoot : public TransformNode
{
public:
    TransformRoot()
        : TransformNode(NULL, Mat4d()) {}
};

// A Geometry object is anything that has extent in three dimensions.
// It may not be an actual visible scene object.  For example, hierarchical
// spatial subdivision could be expressed in terms of Geometry instances.
class Geometry
	: public SceneElement
{
public:
    // intersections performed in the global coordinate space.
    bool intersect(const ray&r, isect&i) const;
    
protected:
    // intersections performed in the object's local coordinate space
    // do not call directly - this should only be called by intersect()
	virtual bool intersectLocal( const ray& r, isect& i ) const = 0;

public:
	virtual bool hasBoundingBoxCapability() const;
	const BoundingBox& getBoundingBox() const { return bounds; }

	virtual bool isTrimesh() const { return false; }
	virtual void buildKdTree() {}

	virtual void ComputeBoundingBox() {
        // take the object's local bounding box, transform all 8 points on it,
        // and use those to find a new bounding box.

        BoundingBox localBounds = ComputeLocalBoundingBox();
        
        Vec3d min = localBounds.min;
		Vec3d max = localBounds.max;

		Vec4d v, newMax, newMin;

		v = transform->localToGlobalCoords( Vec4d(min[0], min[1], min[2], 1) );
		newMax = v;
		newMin = v;
		v = transform->localToGlobalCoords( Vec4d(max[0], min[1], min[2], 1) );
		newMax = maximum(newMax, v);
		newMin = minimum(newMin, v);
		v = transform->localToGlobalCoords( Vec4d(min[0], max[1], min[2], 1) );
		newMax = maximum(newMax, v);
		newMin = minimum(newMin, v);
		v = transform->localToGlobalCoords( Vec4d(max[0], max[1], min[2], 1) );
		newMax = maximum(newMax, v);
		newMin = minimum(newMin, v);
		v = transform->localToGlobalCoords( Vec4d(min[0], min[1], max[2], 1) );
		newMax = maximum(newMax, v);
		newMin = minimum(newMin, v);
		v = transform->localToGlobalCoords( Vec4d(max[0], min[1], max[2], 1) );
		newMax = maximum(newMax, v);
		newMin = minimum(newMin, v);
		v = transform->localToGlobalCoords( Vec4d(min[0], max[1], max[2], 1) );
		newMax = maximum(newMax, v);
		newMin = minimum(newMin, v);
		v = transform->localToGlobalCoords( Vec4d(max[0], max[1], max[2], 1) );
		newMax = maximum(newMax, v);
		newMin = minimum(newMin, v);
		
		bounds.max = Vec3d(newMax);
		bounds.min = Vec3d(newMin);
    }

    // default method for ComputeLocalBoundingBox returns a bogus bounding box;
    // this should be overridden if hasBoundingBoxCapability() is true.
    virtual BoundingBox ComputeLocalBoundingBox() { return BoundingBox(); }

    void setTransform(TransformNode *transform) { this->transform = transform; };
    
	Geometry( Scene *scene ) 
		: SceneElement( scene ) {}

	// For debugging purposes, draws using OpenGL
	void glDraw(int quality, bool actualMaterials, bool actualTextures) const;

	// The defult does nothing; this is here because it is not required
	// that you implement this function if you create your own scene objects.
	virtual void glDrawLocal(int quality, bool actualMaterials, bool actualTextures) const { }

protected:
	BoundingBox bounds;
    TransformNode *transform;
};

// A SceneObject is a real actual thing that we want to model in the 
// world.  It has extent (its Geometry heritage) and surface properties
// (its material binding).  The decision of how to store that material
// is left up to the subclass.
class SceneObject
	: public Geometry
{
public:
	virtual const Material& getMaterial() const = 0;
	virtual void setMaterial( Material *m ) = 0;

	void glDraw(int quality, bool actualMaterials, bool actualTextures) const;

protected:
	SceneObject( Scene *scene )
		: Geometry( scene ) {}
};

// A simple extension of SceneObject that adds an instance of Material
// for simple material bindings.
class MaterialSceneObject
	: public SceneObject
{
public:
	virtual ~MaterialSceneObject() { delete material; }

	virtual const Material& getMaterial() const { return *material; }
	virtual void setMaterial( Material* m )	{ delete material; material = m; }

protected:
	MaterialSceneObject( Scene *scene, Material *mat ) 
		: SceneObject( scene ), material( mat ) {}

	Material* material;
};

template <class T>
class KDNode {
public:
	BoundingBox bb;
	std::unique_ptr<KDNode<T>> left;
	std::unique_ptr<KDNode<T>> right;
	int axis;
	double splitVal;
	bool leaf;
	std::vector<T*> objects;


	KDNode(std::vector<T*> &objs, size_t minSplit = 15, int depth = 20) {
		bb = BoundingBox();
		bb.max = Vec3d(0.0, 0.0, 0.0);
		bb.min = Vec3d(0.0, 0.0, 0.0);
		leaf = false;

		for (size_t i = 0; i < objs.size(); ++i) {
			bb.mergeBoxs(objs[i]->getBoundingBox());
		}


		if (depth <= 0 || objs.size() <= minSplit) {
			objects = std::vector<T*>(objs);
			leaf = true;
			return;
		}

		int splitAxis = bb.getSplitAxis();
		double max = bb.min[splitAxis];
		double min = bb.max[splitAxis];
		double maxAvg = 0.0, minAvg = 0.0;

		for (size_t i = 0; i < objs.size(); ++i) {
			maxAvg += (objs[i]->getBoundingBox().max[splitAxis])* (1.0 / objs.size());
			minAvg += (objs[i]->getBoundingBox().min[splitAxis])* (1.0 / objs.size());
		}

		splitVal = (minAvg + maxAvg) / 2.0;

		std::vector<T*> inLeft;
		std::vector<T*> inRight;
		

		for (size_t i = 0; i < objs.size(); ++i) {
			BoundingBox currBB = objs[i]->getBoundingBox();
			double mid = (currBB.max[splitAxis] + currBB.min[splitAxis]) / 2.0;
			if (mid < splitVal) {
				inLeft.push_back(objs[i]);
			}
			else {
				inRight.push_back(objs[i]);
			}
		}


		left = std::unique_ptr<KDNode<T>>(new KDNode<T>(inLeft, minSplit, depth - 1));
		right = std::unique_ptr<KDNode<T>>(new KDNode<T>(inRight, minSplit, depth - 1));
	}

	~KDNode() {
		
	}

	bool intersect(const ray& r, isect& i) {
		double tmin = -1.0e308, tmax = 1.0e308;
		bool hitAnyThing = false;
		if (bb.intersect(r, tmin, tmax)) {
			if (leaf) {
				isect ipoint;
				for (size_t j = 0; j < objects.size(); ++j) {
					if (objects[j]->intersect(r, ipoint)) {
						if (!hitAnyThing || ipoint.t < i.t) {
							i = ipoint;
							hitAnyThing = true;
						}
					}
				}
			}
			else {
				bool hitsLeft = left->intersect(r, i);
				bool hitsRight = right->intersect(r, i);
				return hitsLeft || hitsRight;
			}
		}
		return hitAnyThing;
	}
};

class Scene
{
public:
	typedef std::vector<Light*>::iterator 			liter;
	typedef std::vector<Light*>::const_iterator 	cliter;

	typedef std::vector<Geometry*>::iterator 		giter;
	typedef std::vector<Geometry*>::const_iterator cgiter;

    TransformRoot transformRoot;

public:
	Scene() 
		: transformRoot(), objects(), lights()
		{}
	virtual ~Scene();

	void add( Geometry* obj )
	{
		obj->ComputeBoundingBox();
		objects.push_back( obj );
	}
	void add( Light* light )
	{ lights.push_back( light ); }

	void buildKdTree();
	void setKDtree(bool kd) { usingKDTree = kd; }
	bool intersect( const ray& r, isect& i ) const;

	std::vector<Light*>::const_iterator beginLights() const { return lights.begin(); }
	std::vector<Light*>::const_iterator endLights() const { return lights.end(); }
        
	const Camera& getCamera() const		{ return camera; }
	Camera& getCamera()					{ return camera; }

	// For efficiency reasons, we'll store texture maps in a cache
	// in the Scene.  This makes sure they get deleted when the scene
	// is destroyed.
	TextureMap* getTexture( string name );

	// These two functions are for handling ambient light; in the Phong model,
	// the "ambient" light is considered a property of the _scene_ as a whole
	// and hence should be set here.
	Vec3d ambient() const	{ return ambientIntensity; }
	void addAmbient( const Vec3d& ambient ) { ambientIntensity += ambient; }

	void glDraw(int quality, bool actualMaterials, bool actualTextures) const;

	const BoundingBox& bounds() const		{ return sceneBounds; }

private:
    std::vector<Geometry*> objects;
	std::vector<Geometry*> nonboundedobjects;
	std::vector<Geometry*> boundedobjects;
    std::vector<Light*> lights;
    Camera camera;
	std::unique_ptr<KDNode<Geometry>> kdtree;
	bool usingKDTree;
	// This is the total amount of ambient light in the scene
	// (used as the I_a in the Phong shading model)
	Vec3d ambientIntensity;

	typedef std::map< std::string, TextureMap* > tmap;
	tmap textureCache;
	
	// Each object in the scene, provided that it has hasBoundingBoxCapability(),
	// must fall within this bounding box.  Objects that don't have hasBoundingBoxCapability()
	// are exempt from this requirement.
	BoundingBox sceneBounds;


public:
	// This is used for debugging purposes only.
	mutable std::vector< std::pair<ray, isect> > intersectCache;
};

#endif // __SCENE_H__
