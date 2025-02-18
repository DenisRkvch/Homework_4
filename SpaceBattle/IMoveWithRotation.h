#ifndef IMOVEWITHROTATION_H
#define IMOVEWITHROTATION_H

#include "IMovable.h"
#include "IRotatable.h"
#include "Vector.h"//

class IMoveWithRotation : public IMovable, public IRotatable
{
protected:
	virtual ~IMoveWithRotation() = default; // защищенный деструктор

public:
	virtual void setVelocity(const Vector& vel) = 0;
};

#endif