#pragma once
#include <functional>
#include <vector>

class CommandInterpreter
{
public:
	CommandInterpreter();

	static void addReturnCall(std::function<void(std::string)>& func, const std::string& ignition);

private:
	static std::vector<std::function<void(std::string)>*> callBackFunctions;

};