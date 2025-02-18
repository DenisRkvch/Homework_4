#ifndef UPDATEVELOCITYCOMMAND_H
#define UPDATEVELOCITYCOMMAND_H

#include "ICommand.h"
#include "../IMoveWithRotation.h"

class UpdateVelocityCommand : public ICommand
{
public:
	UpdateVelocityCommand(IMoveWithRotation* mrObj);

	// Унаследовано через ICommand
	void execute(void) override;
private:
	IMoveWithRotation* mrObj;
	
};

#endif 