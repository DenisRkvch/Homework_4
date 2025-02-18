#include "BurnFuelCommand.h"

BurnFuelCommand::BurnFuelCommand(IFuelUsing* fObj)
	: fObj(fObj)
{
}

void BurnFuelCommand::execute(void)
{
	fObj->setFuel(fObj->getFuel() - fObj->getFuelConsumption());
}