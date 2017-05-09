#include <cmath>
#include <float.h>
#include "trimesh.h"

using namespace std;

Trimesh::~Trimesh()
{
	for( Materials::iterator i = materials.begin(); i != materials.end(); ++i )
		delete *i;
}

// must add vertices, normals, and materials IN ORDER
void Trimesh::addVertex( const Vec3d &v )
{
    vertices.push_back( v );
}

void Trimesh::addMaterial( Material *m )
{
    materials.push_back( m );
}

void Trimesh::addNormal( const Vec3d &n )
{
    normals.push_back( n );
}

// Returns false if the vertices a,b,c don't all exist
bool Trimesh::addFace( int a, int b, int c )
{
    int vcnt = vertices.size();

    if( a >= vcnt || b >= vcnt || c >= vcnt )
        return false;

    TrimeshFace *newFace = new TrimeshFace( scene, new Material(*this->material), this, a, b, c );
    newFace->setTransform(this->transform);
    faces.push_back( newFace );
    //scene->add(newFace);
    return true;
}

char *
Trimesh::doubleCheck()
// Check to make sure that if we have per-vertex materials or normals
// they are the right number.
{
    if( !materials.empty() && materials.size() != vertices.size() )
        return "Bad Trimesh: Wrong number of materials.";
    if( !normals.empty() && normals.size() != vertices.size() )
        return "Bad Trimesh: Wrong number of normals.";

    return 0;
}

bool Trimesh::intersectLocal(const ray&r, isect&i) const {
	bool hitAnyThing = false;

	if (kdtree != nullptr) {
		hitAnyThing = kdtree->intersect(r, i);
	} else {
		for (size_t j = 0; j < faces.size(); ++j) {
			isect cur;
			if (faces[j]->intersectLocal(r, cur)) {
				if (!hitAnyThing || cur.t < i.t) {
					i = cur;
					hitAnyThing = true;
				}
			}
		}
	}
	return hitAnyThing;
}

Vec3d crossProd(const Vec3d a, const Vec3d b) {
	double nx = a[1] * b[2] - a[2] * b[1];
	double ny = -(a[0] * b[2] - a[2] * b[0]);
	double nz = a[0] * b[1] - a[1] * b[0];
	return Vec3d(nx, ny, nz);
}

// Calculates and returns the normal of the triangle too.
bool TrimeshFace::intersectLocal( const ray& r, isect& i ) const
{
    // YOUR CODE HERE:
    // Add triangle intersection code here.
    // it currently ignores all triangles and just return false.
    //
    // Note that you are only intersecting a single triangle, and the vertices
    // of the triangle are supplied to you by the trimesh class.
    //
    // You should retrieve the vertices using code like this:
    //
    // const Vec3d& a = parent->vertices[ids[0]];
    // const Vec3d& b = parent->vertices[ids[1]];
    // const Vec3d& c = parent->vertices[ids[2]];
	
	const Vec3d& a = parent->vertices[ids[0]];
	const Vec3d& b = parent->vertices[ids[1]];
	const Vec3d& c = parent->vertices[ids[2]];
	Vec3d p = r.getPosition();
	Vec3d d = r.getDirection();


	Vec3d normal = crossProd(b - a, c - a);
	normal.normalize();

	double t = (a - p) * normal / (d*normal);
	Vec3d x = p + t*d;

	i.t = t;
	i.N = normal;
	i.N.normalize();
	i.obj = this;
	bool inside = true;
	for (int i = 0; i < 3; ++i) {
		Vec3d vx = x - parent->vertices[ids[i]];
		Vec3d vd = parent->vertices[ids[(i + 1) % 3]] - parent->vertices[ids[i]];

		inside = inside && crossProd(vd, vx) * normal > 0;
	}


	return inside;
}


void
Trimesh::generateNormals()
// Once you've loaded all the verts and faces, we can generate per
// vertex normals by averaging the normals of the neighboring faces.
{
    int cnt = vertices.size();
    normals.resize( cnt );
    int *numFaces = new int[ cnt ]; // the number of faces assoc. with each vertex
    memset( numFaces, 0, sizeof(int)*cnt );
    
    for( Faces::iterator fi = faces.begin(); fi != faces.end(); ++fi )
    {
        Vec3d a = vertices[(**fi)[0]];
        Vec3d b = vertices[(**fi)[1]];
        Vec3d c = vertices[(**fi)[2]];
        
        Vec3d faceNormal = ((b-a) ^ (c-a));
		faceNormal.normalize();
        
        for( int i = 0; i < 3; ++i )
        {
            normals[(**fi)[i]] += faceNormal;
            ++numFaces[(**fi)[i]];
        }
    }

    for( int i = 0; i < cnt; ++i )
    {
        if( numFaces[i] )
            normals[i]  /= numFaces[i];
    }

    delete [] numFaces;
}

