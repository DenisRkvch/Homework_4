#ifndef MACROCOMMAND_H
#define MACROCOMMAND_H

#include "ICommand.h"

class MacroCommand : public ICommand
{

public:
	MacroCommand(ICommand** commandsArr, unsigned int count);
	~MacroCommand();

	// Унаследовано через ICommand
	void execute(void) override;

private:
	ICommand** commands;
	unsigned int commands_count = 0;
	
};
#endif
