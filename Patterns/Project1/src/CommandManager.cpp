#include "CommandManager.h"


CommandManager::CommandManager()
{
	//currentCommandGroup = new CommandGroup(SERIES,1);
}

CommandManager::~CommandManager()
{
	
}

CommandManager& CommandManager::GetInstance()
{
	static CommandManager instance;
	return instance;
}





void CommandManager::AddCommands( Command* command)
{
	if (currentCommandGroup->groupType == SERIES)
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
	CommandGroup* group = new CommandGroup(type, groupId);
	if (currentCommandGroup != nullptr)
	{
		
		group->parentCommandGroup = currentCommandGroup;
	}
	
		currentCommandGroup = group;
}

void CommandManager::EndCommandGroup(const int& groupId)
{
	commandGroupList.push_back(currentCommandGroup);
	currentCommandGroup = currentCommandGroup->parentCommandGroup;;

}

void CommandManager::Start()
{
	if (!commandGroupList.empty())
	{
		for (size_t i = 0; i < commandGroupList.size(); i++)
		{
			commandGroupList[i]->Start();  // Start for firstSerial command and All the parallel commands list.
		}
	}	
}

void CommandManager::Update(float deltatime)
{
	if (!commandGroupList.empty())
	{
		for (size_t i = 0; i < commandGroupList.size(); i++)
		{

			commandGroupList[i]->Update(deltatime);

			if (commandGroupList[i]->isDone())
			{
				 // Remove commandGroup from list after done
			}
		}
	}
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