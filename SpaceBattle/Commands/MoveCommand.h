#ifndef MOVECOMMAND_H
#define MOVECOMMAND_H

#include "../IMovable.h"
#include "ICommand.h"

class MoveCommand : public ICommand
{
private:

	IMovable* mObj;

public:

	MoveCommand(IMovable* movable);
	~MoveCommand();

	void execute() override;
};


#endif
