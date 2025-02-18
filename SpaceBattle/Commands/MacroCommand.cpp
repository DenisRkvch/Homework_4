#include "MacroCommand.h"


MacroCommand::MacroCommand(ICommand** commandsArr, unsigned int count)
	: commands(commandsArr), commands_count(count)
{
}

MacroCommand::~MacroCommand()
{
	for (unsigned int i = 0; i < commands_count;i++)
	{
		delete commands[i];
	}
}

void MacroCommand::execute(void)
{
	for (unsigned int i = 0; i < commands_count;i++)
	{
		commands[i]->execute();
	}
}
