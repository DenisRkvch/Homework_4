#ifndef CHECKFUELCOMMAND_H
#define CHECKFUELCOMMAND_H

#include "ICommand.h"
#include "../IFuelUsing.h"


class CheckFuelCommand : public ICommand
{
public:
	CheckFuelCommand(IFuelUsing* fObj);
	// Унаследовано через ICommand
	void execute(void) override;

private:
	IFuelUsing* fObj;

};

#endif // !CHECKFUELCOMMAND_H

