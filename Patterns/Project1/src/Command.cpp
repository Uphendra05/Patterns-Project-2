#include "Command.h"

Command::Command()
{
}

Command::~Command()
{
}

void Command::Start()
{
}

void Command::Update(float deltatime)
{
}

bool Command::IsComplete()
{
	return false;
}

std::string Command::GetCommandID()
{
	return commandId;
}
