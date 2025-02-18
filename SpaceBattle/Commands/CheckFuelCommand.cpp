#include "CheckFuelCommand.h"
#include "../CommandException.h"

CheckFuelCommand::CheckFuelCommand(IFuelUsing* fObj): fObj(fObj)
{
}

void CheckFuelCommand::execute(void)
{
	// ������������ �������
	if (fObj->getFuel() < fObj->getFuelConsumption())
	{
		throw new CommandException("not enough fuel");
	}
}
