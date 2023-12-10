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
	if (!serialCommandsList.empty())
	{
		Command* currentCommand = *serialCommandsList.begin();

		if (!currentCommand->IsStarted())
		{
			currentCommand->Start();
			currentCommand->SetStarted(true);
		}
		currentCommand->Update(deltaTime);

		if (currentCommand->IsComplete())
		{
			serialCommandsList.erase(serialCommandsList.begin());
			currentCommand->SetStarted(false);
			delete currentCommand;
		}
	}
}

void CommandGroup::UpdateParallelCommands(float deltaTime)
{

	for (size_t i = 0; i < parallelCommandsList.size(); i++)
	{
		parallelCommandsList[i]->Update(deltaTime);
	}
}

void CommandGroup::Update(float deltaTime)
{
	UpdateSerialCommands(deltaTime);
	UpdateParallelCommands(deltaTime);
}

void CommandGroup::Start()
{
	StartForSerialCommand();
	StartForParallelCommands();
}

void CommandGroup::StartForParallelCommands()
{
	if (parallelCommandsList.size()>0)
	{
		for (size_t i = 0; i < parallelCommandsList.size(); i++)
		{
			if (!parallelCommandsList[i]->IsStarted())
			{
				parallelCommandsList[i]->Start();
				parallelCommandsList[i]->SetStarted(true);
			}
		}
	}
	
}

void CommandGroup::StartForSerialCommand()
{
	if (!serialCommandsList.empty())
	{
		Command* FirstSerialCommand = *this->serialCommandsList.begin();
		if (!FirstSerialCommand->IsStarted())
		{
			FirstSerialCommand->Start();
			FirstSerialCommand->SetStarted(true);
		}

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

bool CommandGroup::isDone()
{
	bool isDone = true;

	if (true)
	{

	}
	return false;
}
