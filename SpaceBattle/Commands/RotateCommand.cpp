#include "RotateCommand.h"

RotateCommand::RotateCommand(IRotatable* rotatable) : rObj(rotatable)
{
}

RotateCommand::~RotateCommand()
{
}

void RotateCommand::execute()
{
	Angle* result = Angle::plus(*rObj->getDirection(), rObj->getAngularVelocity());
	rObj->setDirection(*result);
	delete result;
}

