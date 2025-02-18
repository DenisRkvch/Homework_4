#ifndef IMOVABLE_H
#define IMOVABLE_H

#include "Vector.h"

class IMovable
{

protected:
	virtual ~IMovable() = default; // защищенный деструктор

public:
	virtual const Vector* getPosition() = 0;
	virtual const Vector* getVelocity() = 0;
	virtual void setPosition(const Vector &pos) = 0;

};

#endif
