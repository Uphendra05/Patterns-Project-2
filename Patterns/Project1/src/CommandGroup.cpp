#include "CommandGroup.h"

CommandGroup::CommandGroup() : groupType(SERIES), groupId(0)
{
	
}

CommandGroup::CommandGroup(const CommandGroupType& groupType, const int& groupId) /*: groupType(groupType), groupId(groupId)*/
{
	this->groupType = groupType;
	this->groupId = groupId;
}

CommandGroup::~CommandGroup()
{
}

void CommandGroup::AddSerialCommand(Command* command)
{
	serialCommandsList.push_back(command);
}

void CommandGroup::AddParallelCommand(Command* command)
{
	parallelCommandsList.push_back(command);
}

void CommandGroup::AddCommandGroup(const CommandGroup& commandGroup)
{
	commandGroupsList.push_back(commandGroup);
}

void CommandGroup::UpdateSerialCommands(float deltaTime)
{
	for (size_t i = 0; i < serialCommandsList.size(); i++)
	{
		serialCommandsList[i]->Update(deltaTime);

	}
}

void CommandGroup::UpdateParallelCommands(float deltaTime)
{
	for (size_t i = 0; i < parallelCommandsList.size(); i++)
	{
		parallelCommandsList[i]->Update(deltaTime);

	}
}

void CommandGroup::SetGroupID(const int& groupID)
{
	this->groupId = groupID;
}

int CommandGroup::GetGroupID() const
{
	return groupId;
}
