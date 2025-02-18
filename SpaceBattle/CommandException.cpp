#include "CommandException.h"

CommandException::CommandException() : logic_error("no description")
{
}

CommandException::CommandException(const std::string& what_arg) : logic_error(what_arg)
{
}
