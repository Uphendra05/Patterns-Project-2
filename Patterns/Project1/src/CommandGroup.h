#pragma once
#include<vector>
#include "Command.h"

enum CommandGroupType
{
	SERIES=0,
	PARALLEL=1
};
class CommandGroup
{
public:
	CommandGroup();

	CommandGroup(const CommandGroupType& groupType = CommandGroupType::SERIES, const int& groupId =0);
	~CommandGroup();
	
	void AddSerialCommand(Command* command);
	void AddParallelCommand(Command* command);
	void AddCommandGroup(const CommandGroup& commandGroup);

	void UpdateSerialCommands(float deltaTime);
	void UpdateParallelCommands(float deltaTime);

	void SetGroupID(const int& groupID);

	CommandGroupType groupType = SERIES;

	int GetGroupID() const;

	
private:

	std::vector<Command*> serialCommandsList;
	std::vector<Command*> parallelCommandsList;
	std::vector<CommandGroup> commandGroupsList;

	int groupId;
};


