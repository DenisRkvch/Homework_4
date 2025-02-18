#ifndef COMMANDEXCEPTION_H
#define COMMANDEXCEPTION_H

#include <stdexcept>

class CommandException : public std::logic_error
{
public:
	CommandException();
	CommandException(const std::string& what_arg);
};

#endif
