#include "MoveCommand.h"
#include <exception>
MoveCommand::MoveCommand(IMovable* movable) : mObj(movable)
{
}
MoveCommand::~MoveCommand()
{
}

void MoveCommand::execute()
{
	Vector* result = Vector::plus(*mObj->getPosition(), *mObj->getVelocity());
	mObj->setPosition(*result);
	delete result;
}
