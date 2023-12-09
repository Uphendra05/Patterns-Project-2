#include "CommandManager.h"


CommandManager::CommandManager()
{
	currentCommandGroup = new CommandGroup(SERIES,1);
}

CommandManager::~CommandManager()
{
	
}

CommandManager& CommandManager::GetInstance()
{
	static CommandManager instance;
	return instance;
}





void CommandManager::AddCommands(bool isSerialType, Command* command)
{
	if (isSerialType)
	{
		currentCommandGroup->AddSerialCommand(command);
	}
	else
	{
		currentCommandGroup->AddParallelCommand(command);
	}
}

void CommandManager::BeginCommandGroup()
{
	currentCommandGroup = new CommandGroup(SERIES, 1);
}

void CommandManager::BeginCommandGroup( const CommandGroupType& type,  const int& groupId)
{
	
	currentCommandGroup = new CommandGroup(type, groupId);
}

void CommandManager::EndCommandGroup(const int& groupId)
{
	commandGroupList.push_back(currentCommandGroup);
	currentCommandGroup = nullptr;
}

bool CommandManager::isCommandExists(Command* command)
{

	/*for (std::vector<CommandGroup*>::const_iterator groupIter = commandGroupList.begin(); groupIter != commandGroupList.end(); ++groupIter)
	{
		
		if ((*groupIter)->isCommandExists(command))
		{
			return true;
		}
	}*/

	
	return false;
}