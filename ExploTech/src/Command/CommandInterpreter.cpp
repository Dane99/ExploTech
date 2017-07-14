#include "CommandInterpreter.h"

std::vector<std::function<void(std::string)>*> CommandInterpreter::callBackFunctions;

CommandInterpreter::CommandInterpreter()
{
}

void CommandInterpreter::addReturnCall(std::function<void(std::string)>& func, const std::string& ignition)
{
	callBackFunctions.push_back(&func);
}
