#ifndef  BURNFUELCOMMAND_H
#define BURNFUELCOMMAND_H

#include "../IFuelUsing.h" 
#include "ICommand.h"

class BurnFuelCommand : public ICommand
{
public:
	BurnFuelCommand(IFuelUsing* fObj);

	// Унаследовано через ICommand
	void execute(void) override;

private:
	IFuelUsing* fObj;
};
#endif
