#ifndef ROTATECOMMAND_H
#define ROTATECOMMAND_H

#include "../IRotatable.h"
#include "ICommand.h"

class RotateCommand : public ICommand
{

public:
	RotateCommand(IRotatable* rotatable);
	~RotateCommand();

	void execute() override;

private:
	IRotatable* rObj;
	
};

#endif
