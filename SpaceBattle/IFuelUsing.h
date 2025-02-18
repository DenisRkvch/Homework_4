#ifndef IFUELUSING_H
#define IFUELUSING_H

class IFuelUsing
{
public:
	virtual unsigned int getFuel(void) = 0;
	virtual void setFuel(unsigned int) = 0;
	virtual unsigned int getFuelConsumption(void) = 0;
};

#endif
