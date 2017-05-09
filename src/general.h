#ifndef __GENERAL_H__
#define __GENERAL_H__

#include <string>
#include <iostream>

class Exception
{
public:
	Exception( const std::string& m ) 
		: msg( m ) {}
	
	std::string getMsg() const { return msg; }

private:
	std::string msg;
};

inline std::ostream& operator <<(std::ostream& os, const Exception& x )
{
	return os << x.getMsg();
}

#endif // __GENERAL_H__
