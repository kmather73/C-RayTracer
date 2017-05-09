//
// rayUI.h
//
// The header file for the UI part
//

#ifndef __rayUI_h__
#define __rayUI_h__

// who the hell cares if my identifiers are longer than 255 characters:
#pragma warning(disable : 4786)

#include <math.h>
#include "../vecmath/vec.h"
#include "../vecmath/mat.h"

#include <string>

using std::string;

class RayTracer;

class TraceUI {
public:
	TraceUI()
		: m_nDepth(0), m_nSize(150), 
		m_displayDebuggingInfo( false ),
		raytracer( 0 ),
		m_kd(true),
		m_nAA(1)
	{ }

	virtual int		run() = 0;

	// Send an alert to the user in some manner
	virtual void		alert(const string& msg) = 0;

	// setters
	virtual void		setRayTracer( RayTracer* r )
		{ raytracer = r; }

	virtual void setAA(int a) { m_nAA = a; }
	virtual void setDepth(int d) { m_nDepth = d; }
	virtual void setKD(bool kd) { m_kd = kd; }

	// accessors:
	int		getSize() const { return m_nSize; }
	int		getDepth() const { return m_nDepth; }
	int     getAA() const { return m_nAA; }
	bool    getKD() const { return m_kd; }

protected:
	RayTracer*	raytracer;

	int			m_nSize;				// Size of the traced image
	int			m_nDepth;				// Max depth of recursion
	int         m_nAA;
	bool        m_kd;
	// Determines whether or not to show debugging information
	// for individual rays.  Disabled by default for efficiency
	// reasons.
	bool		m_displayDebuggingInfo;



};

#endif
