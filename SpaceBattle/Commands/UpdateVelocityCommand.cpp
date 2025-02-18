#include "UpdateVelocityCommand.h"
#include <math.h>
#include <limits>


UpdateVelocityCommand::UpdateVelocityCommand(IMoveWithRotation* mrObj)
	: mrObj(mrObj)
{
}


void UpdateVelocityCommand::execute(void)
{
	double magnitude = Vector::calcMagnitude(*mrObj->getVelocity());
	double dir_rad = mrObj->getDirection()->radians();

	if (magnitude > std::numeric_limits<double>::epsilon())	// если скорость не нулевая (не превышает погрешность)
	{
		mrObj->setVelocity(Vector((int)(magnitude * cos(dir_rad)), (int)(magnitude * sin(dir_rad))));
	}	
}